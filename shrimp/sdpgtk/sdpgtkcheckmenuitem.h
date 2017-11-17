#ifndef SDPGTKCHECKMENUITEM_H
#define SDPGTKCHECKMENUITEM_H

// SDPGTK Library
// Copyright � 1995-2003, Timothy M. Shead
//
// Contact: tshead@k-3d.com
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA



#include "sdpgtkmenuitem.h"


////////////////////////////////////////////////////////////////
// sdpGtkCheckMenuItem

class sdpGtkCheckMenuItem : public sdpGtkMenuItem
{
public:
	sdpGtkCheckMenuItem();
	sdpGtkCheckMenuItem(GtkCheckMenuItem* CheckMenuItem);

	// Creation ...
	bool Create();
	bool Create(SDPCSTRING Label);
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	// Operations ...
	void SetState(bool State);
	bool GetState();

	// Casting ...
	operator GtkCheckMenuItem*() { return GTK_CHECK_MENU_ITEM(m_Object); }
};



#endif // SDPGTKCHECKMENUITEM_H