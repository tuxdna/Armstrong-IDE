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
#include <sstream>
#include <list>

#include "EditorFactory.h"
#include "EditorArea.h"
#include "Editor.h"

namespace armstrong {

EditorArea::EditorArea() {
	_notebook = new Gtk::Notebook();
	_notebook->set_scrollable(true);
	_notebook->popup_enable();

}

void EditorArea::openFile(std::string& filename) {
	// check preconditions

	// create an editor
	Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(filename);
	std::string tablabel = file->get_basename();
	armstrong::IEditor *editor = EditorFactory::create(filename, tablabel);
	Gtk::Widget * editor_ui = editor->getUi();

	// add editor created to the list of editors

	// add it to notebook
	int page_number = addEditor(dynamic_cast<Editor*>(editor));
	std::cerr << "EditorArea: Opened file: " << filename << std::endl;
}

void EditorArea::newFile() {
	// create an editor
	// add it to notebook
	int n_pages = _notebook->get_n_pages();
	std::ostringstream outs;
	outs << "Untitled " << n_pages;
	std::string pagetitle = outs.str();

	armstrong::IEditor *editor = EditorFactory::create("", pagetitle);
	Gtk::Widget * editor_ui = editor->getUi();

	int page_number = addEditor(dynamic_cast<Editor*>(editor));
	std::cerr << "EditorArea: New file: " << pagetitle << std::endl;
}

void EditorArea::saveFile() {
	// If there is a file associated with current editor, just save it
	// else show a dialog box to choose a filename


	// save the file in currently opened editor
	// find currently opened editor
	int current_page = _notebook->get_current_page();

	if(-1 == current_page) {
		// there is no current editor
		std::cerr << "No file opened yet!" << std::endl;
		return;
	}


	IEditor *current_editor = editors[current_page];

	if( ! current_editor) {
		std::cerr << "Editor not found!" << std::endl;
		return;
	}

	// if this is a new file, ask for a file name
	std::string filename = current_editor->getFilename();
	std::cout << "filename: ["<< filename << "]" << std::endl;
	bool should_save = false;

	if( ! filename.length()) {
		Gtk::FileChooserAction action = Gtk::FILE_CHOOSER_ACTION_SAVE;
		Gtk::FileChooserDialog dialog("Save file", action, "");

		dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
		dialog.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);

		// d->set_transient_for(*this);
		int result = dialog.run();

		switch (result) {
		case (Gtk::RESPONSE_OK): {
			std::cout << "Save clicked." << std::endl;

			//Notice that this is a std::string, not a Glib::ustring.
			filename = dialog.get_filename();
			std::cout << "File selected: " << filename << std::endl;
			should_save = true;
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

	if(should_save) {
		// save it
	  current_editor->setFilename(filename);
		std::cerr << "EditorArea: Save file: " <<
		  current_page << ":" << current_editor->getFilename() << std::endl;
	}
}

int EditorArea::addEditor(Editor *editor) {

  int page_number = _notebook->append_page(*(editor->getUi()));

/*
	Gtk::HBox *hbox = new Gtk::HBox();
	Gtk::Label *label = new Gtk::Label(pagetitle);
	Gtk::Button *button = new Gtk::Button();
	Gtk::Image *i = new Gtk::Image(Gtk::Stock::CLOSE, Gtk::ICON_SIZE_MENU);
	button->set_image(*i);
	hbox->add(*label);
	hbox->add(*button);
	hbox->set_homogeneous(false);
	hbox->show_all(); */
  _notebook->set_tab_label(*(editor->getUi()), editor->get_editor_tab()->getUi());

	_notebook->set_current_page(page_number);

	//std::cerr << "EditorArea: page added: " << pagetitle << std::endl;

	return page_number;
}

void EditorArea::removeEditor() {
	throw "not implemented";
}

Gtk::Widget * EditorArea::getUi() {
	return _notebook;
}

EditorArea::~EditorArea() {
	delete _notebook;
}

}
