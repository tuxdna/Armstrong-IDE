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

#ifndef _UI_SHELL_H_
#define _UI_SHELL_H_

#include <gtkmm.h>
#include "IEditorArea.h"
/*
 UI Shell is a container which holds all of the User Interface components.
 This is used by IDE framework to display various widgets.
 */

class UiShell
{
public:
	static UiShell * getInstance();
	void addWidget(Gtk::Widget*);
	Gtk::Widget *getShellUi();
	void openFile();
	void newFile();
	void saveFile();
	void initialize();
	void addEditorArea(IEditorArea *);
	void addProjectManager();
	void addProperties();

private:
	static UiShell *singleton_instance;
	// hidden constructor
	UiShell();
	Gtk::Widget *shell_ui_widget;
	GtkWidget *dock;
	IEditorArea *editor_area;
	void initializeUiInternals(Glib::RefPtr<Gtk::Builder>&);
	void showAboutDialog();
};

#endif // _UI_SHELL_H_
