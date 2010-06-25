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
#include <iostream>
#include <string>

#include "EditorArea.h"
#include "Editor.h"

EditorArea::EditorArea() {
	_notebook = new Gtk::Notebook();
}

void EditorArea::openFile(std::string& filename) {
	// check preconditions

	// create an editor
	armstrong::IEditor *editor = new armstrong::Editor(filename);
	Gtk::Widget * editor_ui = editor->getUi();

	// add it to notebook
	Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(filename);
	int page_number = _notebook->append_page(*editor_ui, file->get_basename());
	_notebook->set_current_page(page_number);

	std::cerr << "EditorArea: Opened file: " << filename << std::endl;
}

Gtk::Widget * EditorArea::getUi() {
	return _notebook;
}

EditorArea::~EditorArea() {
	delete _notebook;
}
