
/*
    Copyright 2008, Romain Behar <romainbehar@users.sourceforge.net>

    This file is part of Shrimp 2.

    Shrimp 2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Shrimp 2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Shrimp 2.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef _ui_add_input_h_
#define _ui_add_input_h_

#include "../miscellaneous/misc_xml.h"
#include "../miscellaneous/misc_string_functions.h"

#include <fltk/CheckButton.h>
#include <fltk/Choice.h>
#include <fltk/Input.h>
#include <fltk/Item.h>
#include <fltk/ReturnButton.h>
#include <fltk/TextEditor.h>
#include <fltk/Window.h>

#include <string>

namespace add_input
{

static fltk::Input* s_name = 0;
static fltk::Choice* s_type = 0;
static fltk::Input* s_default_value = 0;
static fltk::CheckButton* s_shader_parameter = 0;
static fltk::TextEditor* s_description = 0;

typedef std::string type_t;
typedef std::vector<type_t> types_t;
static types_t s_types;

// trick for FLTK's callback
class dialog;
dialog* dialog_instance;

class dialog {

private:
	fltk::Window* w;
	shader_block* m_block;

public:
	dialog() {

		// build type array
		s_types = get_property_types();

		// build dialog window
		w = new fltk::Window (400, 300, "Add input");
		w->begin();

			s_name = new fltk::Input (90,10, 250,23, "Name");
			w->add (s_name);
			s_name->tooltip ("Input name");

			s_type = new fltk::Choice (90,40, 120,25, "Type");
			s_type->begin();
				for (types_t::const_iterator t = s_types.begin(); t != s_types.end(); ++t) {

					new fltk::Item (t->c_str());
				}
			s_type->end();
			w->add (s_type);
			s_type->tooltip ("Input type");

			s_default_value = new fltk::Input (90,70, 100,23, "Default value");
			w->add (s_default_value);
			s_default_value->tooltip ("Input's default value");

			// shader parameter checkbox
			s_shader_parameter = new fltk::CheckButton (90,100, 120,23, "Shader parameter");
			w->add (s_shader_parameter);
			s_shader_parameter->tooltip ("Make the input a shader parameter");

			// description text input
			s_description = new fltk::TextEditor (90,130, 200,100, "Description");
			w->add (s_description);
			s_description->tooltip ("Input description");
			s_description->wrap_mode(true);
			w->resizable (s_description);


			// OK / Cancel
			fltk::ReturnButton* rb = new fltk::ReturnButton(150, 250, 70, 25, "OK");
			rb->label("Ok");
			rb->callback(cb_ok, (void*)this);

			fltk::Button* cb = new fltk::Button(250, 250, 70, 25, "Cancel");
			cb->label("Cancel");
			cb->callback(cb_cancel, (void*)this);

		w->end();
	}

	~dialog()
	{
		delete w;
	}

	void open_dialog (shader_block* Block)
	{
		// save processed block
		m_block = Block;

		// save instance for callback
		dialog_instance = this;

		// show it
		w->exec();
	}

	void on_ok (fltk::Widget* W) {

		// get user values
		const std::string name = s_name->value();
		const std::string type = s_types[s_type->value()];
		const std::string default_value = s_default_value->value();
		const std::string description = s_description->text();
		const bool shader_parameter = s_shader_parameter->value();

		// check that the name isn't already used in this block
		// TODO

		// check that the default value matches the input type
		// TODO

		//if tests OK...
		{
			// create the input
			m_block->add_input (name, type, description, default_value, "", shader_parameter);

			// close the dialog
			W->window()->make_exec_return(false);
		}
	}

	void on_cancel(fltk::Widget* W) {

		// close the dialog
		W->window()->make_exec_return(false);
	}

	static void cb_ok(fltk::Widget* W, void* Data) { ((dialog*)Data)->on_ok(W); }
	static void cb_cancel(fltk::Widget* W, void* Data) { ((dialog*)Data)->on_cancel(W); }
};

}

#endif // _ui_add_input_h_

