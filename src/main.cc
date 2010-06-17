#include <gtkmm.h>
#include <iostream>
#include "ui-shell.h"

int main (int argc, char **argv)
{
  Gtk::Main kit(argc, argv);
  Gtk::Main::init_gtkmm_internals();
  Gtk::Window window;
  Gtk::VBox vbox;
  UiShell *uishell = UiShell::getInstance();
  vbox.pack_start(*uishell->getShellUi());

  window.add(vbox);
  window.show_all();
  Gtk::Main::run();

  return 0;

}
