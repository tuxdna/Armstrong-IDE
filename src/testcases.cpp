#include <iostream>
#include <gtkmm.h>
#include <iostream>
#include <gtksourceviewmm.h>

#include "EditorFactory.h"
#include "IEditor.h"

using namespace std;
using namespace armstrong;

int main(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);
	Gtk::Main::init_gtkmm_internals();
	gtksourceview::init();
	IEditor *editor = EditorFactory::create();

	cout << editor << endl;

}

