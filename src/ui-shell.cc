/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * armstrong-ide
 * Copyright (C)  2010 Saleem Anari <tuxdna@gmail.com>
 * 
 * armstrong-ide is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * armstrong-ide is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtksourceviewmm.h>
#include <gdl/gdl.h>

#include "ui-shell.h"

#define MAIN_UI_FILE "src/armstrong_ide2.ui"
#define ABOUT_UI_FILE "src/about.ui"
#include <iostream>

static Gtk::Widget * getScrolledEditor(std::string filename)
{
	Gtk::ScrolledWindow *scrolled_window = new Gtk::ScrolledWindow();

	gtksourceview::init();
	gtksourceview::SourceView *svptr = new gtksourceview::SourceView();
	Glib::RefPtr<gtksourceview::SourceView> sv(svptr);
	Glib::RefPtr<gtksourceview::SourceBuffer> buffer = sv->get_source_buffer();

	if (!buffer)
	{
		std::cerr << "creating a new buffer\n";
		buffer = gtksourceview::SourceBuffer::create();
		sv->set_buffer(buffer);
	}

	if(filename.length() > 0) {
		std::string file_contents = Glib::file_get_contents(filename);
		buffer->set_text(file_contents);
	} else {
		// empty buffer
	}

	Glib::RefPtr<gtksourceview::SourceLanguageManager> lm =
			gtksourceview::SourceLanguageManager::get_default();
	Glib::RefPtr<gtksourceview::SourceLanguage> lang;

	bool result_uncertain = FALSE;
	Glib::ustring content_type;

	content_type = Gio::content_type_guess(filename, 0, 0, result_uncertain);
	if (result_uncertain)
	{
		content_type.clear();
	}

	lang = lm->guess_language(filename, content_type);

	buffer->set_language(lang);

	svptr->set_show_line_numbers(true);
	svptr->set_show_right_margin(true);
	scrolled_window->add(*svptr);
	return scrolled_window;

}

static Gtk::Widget * getEditorUi()
{
	Gtk::Notebook * notebook = new Gtk::Notebook();
	Gtk::Widget * scrolled_editor = 0;
	std::string filename;

	filename = "/usr/include/stdlib.h";
	Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(filename);

	scrolled_editor = getScrolledEditor(file->get_path());
	notebook->append_page(*scrolled_editor, file->get_basename());

	filename = "/usr/bin/yum";
	file = Gio::File::create_for_path(filename);

	scrolled_editor = getScrolledEditor(file->get_path());
	notebook->append_page(*scrolled_editor, file->get_basename());

	scrolled_editor = getScrolledEditor("");
	notebook->append_page(*scrolled_editor, "Untitled 1");

	return notebook;
}

static Gtk::Widget * getShellUi(Glib::RefPtr<Gtk::Builder> &mainRefBuilder)
{


	Gtk::VBox *vbox = 0;
	mainRefBuilder->get_widget("vbox_main_outer", vbox);

	if (!vbox)
	{
		std::cerr << "main widget initialization failed!" << std::endl;
		return 0;
	}

	Gtk::Widget *editor_widget = getEditorUi();

	GtkWidget *dock = gdl_dock_new();
	GdlDockLayout *layout = gdl_dock_layout_new(GDL_DOCK (dock));
	GtkWidget *dockbar = gdl_dock_bar_new(GDL_DOCK (dock));
	gdl_dock_bar_set_style(GDL_DOCK_BAR(dockbar), GDL_DOCK_BAR_TEXT);

	/*
	 * Create an editor dock on the right side
	 */
	GtkWidget *editor_dock_item = gdl_dock_item_new("editor_dock_item",
			"Editor", GDL_DOCK_ITEM_BEH_NORMAL);

	gtk_container_add(GTK_CONTAINER(editor_dock_item), GTK_WIDGET(
			editor_widget->gobj()));
	gdl_dock_add_item(GDL_DOCK (dock), GDL_DOCK_ITEM (editor_dock_item),
			GDL_DOCK_RIGHT);

	gtk_widget_show(editor_dock_item);

	Gtk::ScrolledWindow *scrolled_window = 0;

	/*
	 * Create a project manager dock on the left side
	 */
	GtkWidget *projects_dock_item = gdl_dock_item_new("projects_dock_item",
			"Projects", GDL_DOCK_ITEM_BEH_NORMAL);

	scrolled_window = new Gtk::ScrolledWindow();
	gtk_container_add(GTK_CONTAINER(projects_dock_item), GTK_WIDGET(
			scrolled_window->gobj()));
	gdl_dock_add_item(GDL_DOCK (dock), GDL_DOCK_ITEM (projects_dock_item),
			GDL_DOCK_LEFT);

	gtk_widget_show(projects_dock_item);

	/*
	 * Create a properties dock on the left side
	 */
	GtkWidget *properties_dock_item = gdl_dock_item_new("properties_dock_item",
			"Properties", GDL_DOCK_ITEM_BEH_NORMAL);

	scrolled_window = new Gtk::ScrolledWindow();
	gtk_container_add(GTK_CONTAINER(properties_dock_item), GTK_WIDGET(
			scrolled_window->gobj()));

	gdl_dock_add_item(GDL_DOCK (dock), GDL_DOCK_ITEM (properties_dock_item),
			GDL_DOCK_BOTTOM);

	gtk_widget_show(properties_dock_item);

	vbox->pack_start(*Glib::wrap(dock));

	return vbox;
}

UiShell * UiShell::getInstance()
{
	if (!singleton_instance)
	{
		singleton_instance = new UiShell;
	}
	return singleton_instance;
}

UiShell::UiShell()
{

}

void UiShell::openFile() {
	std::cout << "open file" << std::endl;
	Gtk::FileChooserAction action = Gtk::FILE_CHOOSER_ACTION_OPEN;
	Gtk::FileChooserDialog *d =
			new Gtk::FileChooserDialog("Open file", action, "");
	d->show_all();
}

Gtk::Widget *UiShell::getShellUi()
{
	Glib::RefPtr<Gtk::Builder> mainRefBuilder =
			Gtk::Builder::create_from_file(MAIN_UI_FILE);

	Gtk::Widget *ui_widget = ::getShellUi(mainRefBuilder);

	std::cout << mainRefBuilder << std::endl;

	Gtk::ImageMenuItem *image_menu_item_open;
	mainRefBuilder->get_widget("imagemenuitem_open", image_menu_item_open);

    image_menu_item_open ->signal_activate()
      .connect( sigc::mem_fun(*this, &UiShell::openFile) );


	Gtk::ImageMenuItem *image_menu_item_quit;
	mainRefBuilder->get_widget("imagemenuitem_quit", image_menu_item_quit);

    image_menu_item_quit ->signal_activate()
		.connect( sigc::ptr_fun(&Gtk::Main::quit ) );
	return ui_widget;
}

UiShell *UiShell::singleton_instance = 0;

