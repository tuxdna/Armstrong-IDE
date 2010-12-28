/*
 * armstrong-ide
 * Copyright (C) 2010 Saleem Ansari <tuxdna@gmail.com>
 * 
 * Armstrong-IDE is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Armstrong-IDE is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __EDITOR_H__
#define __EDITOR_H__

#include <string>

#include "IEditor.h"
#include <gtksourceviewmm.h>

namespace armstrong {

class EditorTab {
private:
	Gtk::HBox *hbox;
	Gtk::Label *label;
	Gtk::Button *button;
	Gtk::Image *i;

public:
	EditorTab(std::string tabtitle) {
		hbox = new Gtk::HBox();
		label = new Gtk::Label(tabtitle);
		button = new Gtk::Button();
		i = new Gtk::Image(Gtk::Stock::CLOSE, Gtk::ICON_SIZE_MENU);
		button->set_image(*i);
		hbox->add(*label);
		hbox->add(*button);
		hbox->set_homogeneous(false);
		hbox->show_all();
	}

	Gtk::Widget & getUi() {
		return *hbox;
	}

	~EditorTab() {
		delete hbox;
		delete label;
		delete button;
		delete i;
	}

	void setLabel(std::string new_label) {
		label->set_text(new_label);
	}

	std::string getLabel() {
		return label->get_text();
	}
};

class Editor: public IEditor {
public:
	// Editor();
	Editor(std::string filename, std::string tablabel);
	virtual ~Editor();


	///////////////////////////////////////////////////////////////
	// IEditor methods begin
	///////////////////////////////////////////////////////////////
	Gtk::Widget * getUi();
	std::string getFilename();
	void setFilename(std::string);
	gint get_tabsize();
	void set_tabsize(gint tabsize);
	gboolean get_use_spaces();
	void set_use_spaces(gboolean use_spaces);
	void set_auto_indent(gboolean auto_indent);
	void erase(Iterable *position_start, Iterable *position_end);
	void erase_all();
	void insert(Iterable *position, const gchar *text, gint length);
	void append(const gchar *text, gint length);
	void goto_line(gint lineno);
	void goto_start();
	void goto_end();
	void goto_position(Iterable *position);
	gchar* get_text(Iterable *begin, Iterable *end);
	gchar* get_text_all();
	int get_line_from_position(Iterable *position);
	gint get_lineno();
	gint get_length();
	gchar* get_current_word();
	gint get_column();
	Iterable* get_line_begin_position(gint line);
	Iterable *get_line_end_position(gint line);
	gboolean get_overwrite();
	void set_popup_menu(GtkWidget *menu);
	gint get_offset();
	Iterable* get_position();
	Iterable* get_position_from_offset(gint offset);
	Iterable* get_start_position();
	Iterable* get_end_position();

	bool is_buffer_dirty();
	void set_buffer_dirty(bool);
	void modified_callback();
	EditorTab *get_editor_tab();
private:
	Gtk::ScrolledWindow *scrolled_window;
	gtksourceview::SourceView *svptr;
	Glib::RefPtr<gtksourceview::SourceBuffer> buffer;
	Glib::RefPtr<gtksourceview::SourceView> sv;
	Glib::RefPtr<gtksourceview::SourceLanguageManager> lm;
	Glib::RefPtr<gtksourceview::SourceLanguage> lang;
	Glib::ustring content_type;
	std::string filename;
	bool buffer_dirty;
	EditorTab *editor_tab;

	void createScrolledEditor(std::string& filename);
};

}
#endif
