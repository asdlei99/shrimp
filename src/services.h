
/*
    Copyright 2009, Romain Behar <romainbehar@users.sourceforge.net>

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

#ifndef _services_h_
#define _services_h_

#include "shading/scene.h"
#include "shading/shrimp_public_structures.h"

// Service class used to access all Shrimp functions (used to separate the GUI from the core)
class services {

public: // structures
	typedef std::set<std::string> block_selection_t;

public:
	// constructor/destructor
	services();
	~services();

	// reset to a new scene
	void reset_scene();

	// load and save scene
	bool load (const std::string& Scene) { bool result = m_scene->load (Scene); if (result) { m_scene_file = Scene; } return result; }
	bool save () { if (m_scene_file != "") { /* use current scene file */ m_scene->save_as (m_scene_file); return true; } else { return false; } }
	bool save_as (const std::string& ShaderFile) { m_scene_file = ShaderFile; return m_scene->save_as (ShaderFile); }

	std::string get_scene_name() const { return m_scene->name(); }
	void set_scene_name (const std::string& Name) { m_scene->set_name (Name); }
	std::string get_scene_description() const { return m_scene->description(); }
	void set_scene_description (const std::string& Description) { m_scene->set_description(Description); }
	std::string get_scene_authors() const { return m_scene->authors(); }
	void set_scene_authors (const std::string& Authors) { m_scene->set_authors(Authors); }

	// return block hierarchy
	block_tree_node_t get_block_hierarchy();

	shader_block_map_t get_scene_blocks();

	std::string get_unique_block_name (const std::string& Name) const { return m_scene->get_unique_block_name (Name); }

	shader_block* get_block (const std::string& Name) { return m_scene->get_block (Name); }
	void set_block_name (shader_block* Block, const std::string& NewName) { m_scene->set_block_name (Block, NewName); }
	void delete_block (const std::string& BlockName) { m_scene->delete_block (BlockName); }
	shader_block* add_custom_block (const std::string& Name = "New block", const bool RootBlock = false) { return m_scene->add_custom_block (Name, RootBlock); }

	shrimp::dag_t get_scene_dag() { return m_scene->m_dag; }

	shader_block* get_parent (const std::string& BlockName, const std::string& Input, std::string& ParentOutput) const { return m_scene->get_parent (BlockName, Input, ParentOutput); }

	//////////// Actions
	shader_block* add_predefined_block (const std::string& BlockName) { return m_scene->add_predefined_block (BlockName); }
	void connect (const shrimp::io_t& Input, const shrimp::io_t& Output) { m_scene->connect (Input, Output); }
	void disconnect (const shrimp::io_t& IO) { m_scene->disconnect (IO); }

	void show_preview (const std::string& TempDir) { m_scene->show_preview (TempDir); }
	void export_scene (const std::string& Directory) { m_scene->export_scene (Directory); }

	//////////// Selection
	block_selection_t& get_block_selection() { return m_block_selection; }

	// returns whether a block is selected
	bool is_selected (const shader_block* Block);

	// returns the size of the selection set
	int selection_size();

	// clear current selection
	void clear_selection();

	// clear copy paste buffer
	void clear_copy_selection();

	// toggle block selection state
	void set_block_selection (shader_block* Block, const bool Selection);

	// block roll
	void set_block_rolled_state (shader_block* Block, const bool Rolled);

	/////////// Group handling
	shrimp::group_set_t group_list() { return m_scene->group_list(); }
	void group_selection() { m_scene->group_selection(); }
	void add_to_group (const std::string& Block, const int Group) { m_scene->add_to_group (Block, Group); }
	int group (const shader_block* Block) { return m_scene->group (Block); }
	void ungroup (const int Group) { m_scene->ungroup (Group); }
	const std::string get_group_name (const int Group) const { return m_scene->get_group_name (Group); }
	void set_group_name (const int Group, const std::string& Name) { m_scene->set_group_name (Group, Name); }
	shrimp::groups_t& groups() { return m_scene->m_groups; }
	void set_group_selection (const int Group , const bool Selection) { m_scene->set_group_selection (Group, Selection); }
	bool is_group_selected (const int Group) { return m_scene->is_group_selected (Group); }
	int group_selection_size() { return m_scene->group_selection_size(); }

private:
	// currently edited scene and its file name
	scene* m_scene;
	std::string m_scene_file;
	block_selection_t m_block_selection;

};


#endif // _services_h_


