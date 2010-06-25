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

#include "Editor.h"

#include <iostream>

namespace armstrong {

static void modified_callback() {
	std::cerr << "buffer modified" << std::endl;

}

Gtk::Widget* Editor::getUi() {
	return scrolled_window;
}

void Editor::createScrolledEditor(std::string& filename) {
	this->filename = filename;
	this->scrolled_window = new Gtk::ScrolledWindow();

	this->svptr = new gtksourceview::SourceView();
	this->sv = Glib::RefPtr<gtksourceview::SourceView>(svptr);
	this->buffer = sv->get_source_buffer();

	if (!buffer) {
		std::cerr << "creating a new buffer\n";
		buffer = gtksourceview::SourceBuffer::create();
		sv->set_buffer(buffer);
	}

	if (filename.length() > 0) {
		std::string file_contents = Glib::file_get_contents(filename);
		buffer->set_text(file_contents);
	} else {
		// empty buffer
	}

	lm = gtksourceview::SourceLanguageManager::get_default();
	bool result_uncertain = FALSE;

	content_type = Gio::content_type_guess(filename, 0, 0, result_uncertain);
	if (result_uncertain) {
		content_type.clear();
	}

	lang = lm->guess_language(filename, content_type);

	buffer->set_language(lang);

	svptr->set_show_line_numbers(true);
	svptr->set_show_right_margin(true);
	scrolled_window->add(*svptr);

	scrolled_window->show_all();

	buffer->signal_changed().connect(sigc::ptr_fun(&modified_callback));
}

std::string Editor::getFilename() {
	return this->filename;
}

/* Editor::Editor() {
 // TODO Auto-generated constructor stub

 }
 */

Editor::Editor(std::string& filename) {
	createScrolledEditor(filename);
}

Editor::~Editor() {
	// TODO Auto-generated destructor stub
}

///////////////////////////////////////////////////////////////
// methods begin
///////////////////////////////////////////////////////////////
gint Editor::get_tabsize() {
	throw "not implemented";
}

void Editor::set_tabsize(gint tabsize) {
	throw "not implemented";
}

gboolean Editor::get_use_spaces() {
	throw "not implemented";
}

void Editor::set_use_spaces(gboolean use_spaces) {
	throw "not implemented";
}

void Editor::set_auto_indent(gboolean auto_indent) {
	throw "not implemented";
}

void Editor::erase(Iterable *position_start, Iterable *position_end) {
	throw "not implemented";
}

void Editor::erase_all() {
	throw "not implemented";
}

void Editor::insert(Iterable *position, const gchar *text, gint length) {
	throw "not implemented";
}

void Editor::append(const gchar *text, gint length) {
	throw "not implemented";
}

void Editor::goto_line(gint lineno) {
	throw "not implemented";
}

void Editor::goto_start() {
	throw "not implemented";
}

void Editor::goto_end() {
	throw "not implemented";
}

void Editor::goto_position(Iterable *position) {
	throw "not implemented";
}

gchar* Editor::get_text(Iterable *begin, Iterable *end) {
	throw "not implemented";
}

gchar* Editor::get_text_all() {
	throw "not implemented";
}

int Editor::get_line_from_position(Iterable *position) {
	throw "not implemented";
}

gint Editor::get_lineno() {
	throw "not implemented";
}

gint Editor::get_length() {
	throw "not implemented";
}

gchar* Editor::get_current_word() {
	throw "not implemented";
}

gint Editor::get_column() {
	throw "not implemented";
}

Iterable* Editor::get_line_begin_position(gint line) {
	throw "not implemented";
}

Iterable *Editor::get_line_end_position(gint line) {
	throw "not implemented";
}

gboolean Editor::get_overwrite() {
	throw "not implemented";
}

void Editor::set_popup_menu(GtkWidget *menu) {
	throw "not implemented";
}

gint Editor::get_offset() {
	throw "not implemented";
}

Iterable* Editor::get_position() {
	throw "not implemented";
}

Iterable* Editor::get_position_from_offset(gint offset) {
	throw "not implemented";
}

Iterable* Editor::get_start_position() {
	throw "not implemented";
}

Iterable* Editor::get_end_position() {
	throw "not implemented";
}

}
