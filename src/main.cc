#include <gtkmm.h>
#include <iostream>
#include "ui-shell.h"

#include "EditorArea.h"
#include <gtksourceviewmm.h>

using namespace armstrong;

int main (int argc, char **argv)
{
  Gtk::Main kit(argc, argv);
  Gtk::Main::init_gtkmm_internals();
  Gtk::Window window;
  Gtk::VBox vbox;
  gtksourceview::init();


  UiShell *uishell = UiShell::getInstance();
  // TODO: move initialization to object construction part
  uishell->initialize();

  EditorArea *editor_area = new EditorArea();
  // add editor
  uishell->addEditorArea(editor_area);

  // add project manager
  uishell->addProjectManager();

  // add properties
  uishell->addProperties();

  vbox.pack_start(*uishell->getShellUi());

  window.add(vbox);
  window.show_all();
  Gtk::Main::run();

  return 0;

}
