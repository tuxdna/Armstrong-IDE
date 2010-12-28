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
#include <vector>

#include "ui-shell.h"

#define MAIN_UI_FILE "src/armstrong_ide2.ui"
#define MAIN_LOGO_FILE "src/main-logo.gif"
#include <iostream>

UiShell *UiShell::singleton_instance = 0;

UiShell * UiShell::getInstance() {
	if (!singleton_instance) {
		singleton_instance = new UiShell;
	}
	return singleton_instance;
}

UiShell::UiShell() {
	shell_ui_widget = 0;
	dock = 0;
	editor_area = 0;
}

Gtk::Widget *UiShell::getShellUi() {
	return shell_ui_widget;
}

void UiShell::initialize() {

	Glib::RefPtr<Gtk::Builder> mainRefBuilder = Gtk::Builder::create_from_file(
			MAIN_UI_FILE);

	// std::cout << mainRefBuilder << std::endl;

	initializeUiInternals(mainRefBuilder);

	// connect menu item signals
	Gtk::ImageMenuItem *image_menu_item_open;
	mainRefBuilder->get_widget("imagemenuitem_open", image_menu_item_open);

	image_menu_item_open ->signal_activate() .connect(sigc::mem_fun(*this,
			&UiShell::openFile));

	Gtk::ImageMenuItem *image_menu_item_new;
	mainRefBuilder->get_widget("imagemenuitem_new", image_menu_item_new);

	image_menu_item_new ->signal_activate() .connect(sigc::mem_fun(*this,
			&UiShell::newFile));

	Gtk::ImageMenuItem *image_menu_item_save;
	mainRefBuilder->get_widget("imagemenuitem_save", image_menu_item_save);

	image_menu_item_save ->signal_activate() .connect(sigc::mem_fun(*this,
			&UiShell::saveFile));


	Gtk::ImageMenuItem *image_menu_item_quit;
	mainRefBuilder->get_widget("imagemenuitem_quit", image_menu_item_quit);

	image_menu_item_quit ->signal_activate() .connect(sigc::ptr_fun(
			&Gtk::Main::quit));

	Gtk::ImageMenuItem *image_menu_item_about;
	mainRefBuilder->get_widget("imagemenuitem_about", image_menu_item_about);

	image_menu_item_about ->signal_activate() .connect(sigc::mem_fun(*this,
			&UiShell::showAboutDialog));
}

void UiShell::initializeUiInternals(Glib::RefPtr<Gtk::Builder> &mainRefBuilder) {
	Gtk::VBox *vbox = 0;
	mainRefBuilder->get_widget("vbox_main_outer", vbox);

	if (!vbox) {
		std::cerr << "main widget initialization failed!" << std::endl;
		return;
	}

	shell_ui_widget = vbox;

	dock = gdl_dock_new();
	GdlDockLayout *layout = gdl_dock_layout_new(GDL_DOCK (dock));
	GtkWidget *dockbar = gdl_dock_bar_new(GDL_DOCK (dock));
	gdl_dock_bar_set_style(GDL_DOCK_BAR(dockbar), GDL_DOCK_BAR_TEXT);

	vbox->pack_start(*Glib::wrap(dock));
}

void UiShell::addEditorArea(IEditorArea *editor_area) {

	this->editor_area = editor_area;
	/*
	 * Create an editor dock on the right side
	 */
	GtkWidget *editor_dock_item = gdl_dock_item_new("editor_dock_item",
			"Editor", GDL_DOCK_ITEM_BEH_NORMAL);

	// Gtk::Widget *editor_widget = getEditorUi();
	Gtk::Widget *editor_widget = this->editor_area->getUi();

	gtk_container_add(GTK_CONTAINER(editor_dock_item), GTK_WIDGET(
			editor_widget->gobj()));
	gdl_dock_add_item(GDL_DOCK (dock), GDL_DOCK_ITEM (editor_dock_item),
			GDL_DOCK_RIGHT);

	gtk_widget_show(editor_dock_item);

}

void UiShell::addProjectManager() {
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

}

void UiShell::addProperties() {
	Gtk::ScrolledWindow *scrolled_window = 0;

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

}

////////////////////////////////////////////////////////////////////////////////
// Define callbacks here
////////////////////////////////////////////////////////////////////////////////


void UiShell::openFile() {
	std::cout << "open file" << std::endl;
	Gtk::FileChooserAction action = Gtk::FILE_CHOOSER_ACTION_OPEN;
	Gtk::FileChooserDialog dialog("Open file", action, "");

	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

	// d->set_transient_for(*this);
	int result = dialog.run();
	switch (result) {
	case (Gtk::RESPONSE_OK): {
		std::cout << "Open clicked." << std::endl;

		//Notice that this is a std::string, not a Glib::ustring.
		std::string filename = dialog.get_filename();
		std::cout << "File selected: " << filename << std::endl;
		editor_area->openFile(filename);
		break;
	}
	case (Gtk::RESPONSE_CANCEL): {
		std::cout << "Cancel clicked." << std::endl;
		break;
	}
	default: {
		std::cout << "Unexpected button clicked." << std::endl;
		break;
	}
	}
}

void UiShell::newFile() {
	std::cout << "new file" << std::endl;
	editor_area->newFile();
}

void UiShell::saveFile() {
	std::cout << "save file" << std::endl;
	editor_area->saveFile();
}

void UiShell::showAboutDialog() {
	std::cout << "about button clicked" << std::endl;
	Gtk::AboutDialog ad;

	std::vector<Glib::ustring> authors;
	authors.push_back("Saleem Ansari <tuxdna@gmail.com>");
	ad.set_name("Armstrong IDE");
	ad.set_version("0.1");
	ad.set_comments("Comments line.");
	ad.set_copyright("See COPYING file in the source distribution.");
	ad.set_website("http://github.com/tuxdna/Armstrong-IDE");
	ad.set_authors(authors);
	ad.set_translator_credits("N/A");

	Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file(
			MAIN_LOGO_FILE);
	ad.set_logo(pixbuf);

	ad.run();
}

