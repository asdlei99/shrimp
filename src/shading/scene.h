
/*
    Copyright 2008-2009, Romain Behar <romainbehar@users.sourceforge.net>

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


#ifndef _scene_h_
#define _scene_h_

#include "shader_block.h"
#include "shrimp_public_structures.h"

#include "../miscellaneous/misc_xml.h"

#include <map>
#include <set>
#include <string>
#include <vector>


// the scene object (contains shaders)
class scene {

public:

	//////////// DAG and block data structures

	shrimp::dag_t m_dag;

	// the list of blocks
	typedef std::map<std::string, shader_block*> shader_blocks_t;
	shader_blocks_t m_blocks;


	//////////// Menu helpers


	//////////// group data structures

	shrimp::groups_t m_groups;
	shrimp::groups_selection_t m_groups_selection;
	shrimp::group_names_t m_group_names;


	//////////// Copy,paste data structures
	shrimp::dag_t m_dag_copy;

	typedef std::pair <std::string, shader_block* > copy_block_t;

	// first copy_block:block original , second copy_block:new block
	typedef std::map<copy_block_t,copy_block_t> shader_blocks_copy_t;
	shader_blocks_copy_t m_copy_buffer;
	shader_blocks_copy_t m_copy_selection;
	shrimp::groups_t m_groups_buffer;

	//////////// Functions

	scene();
	~scene();

	// get and set name, description
	const std::string name() const;
	void set_name (const std::string& Name);
	const std::string description() const;
	void set_description (const std::string& Description);
	const std::string authors() const;
	void set_authors (const std::string& Authors);

	// reset scene
	void empty_scene();
	// create default elements
	void new_scene();

	// return block hierarchy
	block_tree_node_t get_block_hierarchy() const;

	//////////// Blocks

	// add a block to the scene
	void add_block (const std::string& BlockId, const std::string& BlockFile, shader_block* Block);
	// create a block from the predefined block list and add it to the scene
	shader_block* add_predefined_block (const std::string& BlockName);
	// add a new (empty) block to the scene
	shader_block* add_custom_block (const std::string& Name = "New block", const bool RootBlock = false);
	// remove a block from the network and delete it
	void delete_block (const std::string& BlockName);

	// get a block's pointer from its name
	shader_block* get_block (const std::string& Name);
	// find the root block
	shader_block* get_root_block();
	// make a block name unique in the scene
	std::string get_unique_block_name (const std::string& Name) const;
	// set a block's name, making sure it's unique
	void set_block_name (shader_block* Block, const std::string& NewName);

	// connect two blocks
	void connect (const shrimp::io_t& Input, const shrimp::io_t& Output);
	// disconnect an input or output from the network
	void disconnect (const shrimp::io_t& IO);
	// tell whether an input is connected to an output
	bool is_connected (const shrimp::io_t& Input);

	// list of upward blocks in the DAG (parents + parents' parents + etc)
	void upward_blocks (shader_block* StartingBlock, shader_blocks_t& List);

	// copy block
	void copy_blocks(const std::string& Name, const int Group);

	// paste block
	void paste_blocks();

	// copy connections of copy/paste operation
	void copy_connections();

	//////////// Serialization

	// load and save a scene (a network of blocks with additional information, in an XML file)
	bool load (const std::string& Scene);
	bool save_as (const std::string& ShaderFile);

	// return an XML representation of the shader
	xml::element xml_network();


	//////////// Rolled blocks

	// returns whether a block is rolled
	bool is_rolled (const shader_block* Block) const;

	// returns the number of rolled blocks
	int rolled_block_count();

	// unroll all blocks
	void unroll_all_blocks();

	// toggle block rolled / unrolled (normal)
	void set_block_rolled_state (shader_block* Block, const bool Rolled);


	//////////// Grouping

	// useful function to retrieve groups (not used for storage)
	shrimp::group_set_t group_list();

	// turn current selection into a group
	void group_selection();

	// add a block to a group
	void add_to_group (const std::string& Block, const int Group);

	// returns the number of the group the block belongs to (0 == no group)
	int group (const shader_block* Block);

	// dismantles a group
	void ungroup (const int Group);

	// group name functions
	const std::string get_group_name (const int Group) const;
	void set_group_name (const int Group, const std::string& Name);

	std::string get_shader_code();
	void show_preview (const std::string& TempDir);

	// save current scene's RIB and shader files to a directory
	void export_scene (const std::string& Directory);

	// toggle group selection state
	void set_group_selection (const int Group , const bool Selection);

	// returns whether a group is selected
	bool is_group_selected (const int Group);

	int group_selection_size();

	//////////// Misc

	shader_block* get_parent (const std::string& BlockName, const std::string& Input, std::string& ParentOutput) const;


private:

	//////////// Scene

	// scene name
	std::string m_name;
	// scene description
	std::string m_description;
	// scene author(s)
	std::string m_authors;

	// the current scene file name (when saving)
	std::string m_file_name;

	rib_root_block* m_rib_root_block;


	//////////// List of available default blocks
	// the ones that come with the application and are loaded at launch

	typedef std::map <std::string, default_block_t> default_blocks_t;
	default_blocks_t m_default_blocks;

	// load predefined Shrimp blocks
	void load_default_blocks (block_tree_node_t& RootPath, unsigned long& BlockCount);

	// block hierarchy, contains the root block
	block_tree_node_t m_block_classification;

};

#endif // _scene_h_

