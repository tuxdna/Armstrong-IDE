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

#include <gtkmm.h>
#include <string>
#include "IEditor.h"
#include "Editor.h"
#include "EditorFactory.h"
namespace armstrong {

EditorFactory::EditorFactory() {
	// default constructor
}

EditorFactory::~EditorFactory() {
	// default destructor
}

IEditor* EditorFactory::create(std::string filename, std::string tablabel) {
	// std::string filename = "";
	return new Editor(filename, tablabel);
}

}
