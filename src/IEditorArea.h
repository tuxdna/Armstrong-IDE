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

#ifndef IEDITORAREA_H_
#define IEDITORAREA_H_

#include <gtkmm.h>
#include <string>

class IEditorArea {
public:
	IEditorArea() {} ;
	virtual ~IEditorArea() {};

	virtual void openFile(std::string&) = 0;
	virtual Gtk::Widget *getUi() = 0;

};

#endif /* IEDITORAREA_H_ */
