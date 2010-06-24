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

#include "EditorArea.h"

#include <gtksourceviewmm.h>
#include <iostream>
#include <string>

static Gtk::Widget * getScrolledEditor(std::string filename) {
	Gtk::ScrolledWindow *scrolled_window = new Gtk::ScrolledWindow();

	gtksourceview::init();
	gtksourceview::SourceView *svptr = new gtksourceview::SourceView();
	Glib::RefPtr<gtksourceview::SourceView> sv(svptr);
	Glib::RefPtr<gtksourceview::SourceBuffer> buffer = sv->get_source_buffer();

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

	Glib::RefPtr<gtksourceview::SourceLanguageManager> lm =
			gtksourceview::SourceLanguageManager::get_default();
	Glib::RefPtr<gtksourceview::SourceLanguage> lang;

	bool result_uncertain = FALSE;
	Glib::ustring content_type;

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
	return scrolled_window;

}

EditorArea::EditorArea() {
	_notebook = new Gtk::Notebook();
}

void EditorArea::openFile(std::string& filename) {
	Gtk::Widget * scrolled_editor = 0;

	Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(filename);

	scrolled_editor = getScrolledEditor(file->get_path());
	_notebook->append_page(*scrolled_editor, file->get_basename());

	std::cerr << "EditorArea: Opened file: " << filename << std::endl;
}

Gtk::Widget * EditorArea::getUi() {
	return _notebook;
}

EditorArea::~EditorArea() {
	delete _notebook;
}
