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

#ifndef __IEDITOR_FACTORY_H_
#define __IEDITOR_FACTORY_H_

#include <gtkmm.h>
#include <string>
#include "IEditor.h"
class IEditorFactory {
public:
	IEditorFactory() {} ;
	virtual ~IEditorFactory() {};
	virtual IEditor* create() = 0;
};

#endif /* IEDITORAREA_H_ */
