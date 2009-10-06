# scons configuration file

import os, platform


# Optional FLTK 2 paths
vars = Variables('custom.py')
vars.Add(PathVariable('fltk_include_path', 'Point to the fltk header files', '', PathVariable.PathAccept))
vars.Add(PathVariable('fltk_lib_path', 'Point to the fltk library files', '', PathVariable.PathAccept))


# Path setup
env = Environment(variables = vars)

env.ParseConfig("fltk2-config --cxxflags --ldflags")
env.Append(LIBS = ['tinyxml', 'GL', 'GLU', 'fltk2_gl', 'fltk2_images', 'jpeg', 'png'])

if platform.system() == 'Linux':
	env.Append(CPPPATH = ['/usr/include/GL', '$fltk_include_path', '/usr/local/include/fltk/compat/'])
	env.Append(LIBPATH = ['.', '/usr/local/lib', '/usr/X11R6/lib', '$fltk_lib_path'])

elif platform.system() == 'Darwin':
# OS X
	env.Append(CPPPATH = ['/System/Library/Frameworks/OpenGL.framework/Headers', '$fltk_include_path', '/usr/local/include/fltk/compat'])
	env.Append(LIBPATH = ['.', '/usr/local/lib', '/usr/X11R6/lib', '/opt/local/lib', '$fltk_lib_path'])
	env.Append(LINKFLAGS = ['-framework', 'Cocoa', '-framework', 'AGL', '-framework', 'OpenGL', '-framework', 'Carbon'])

else:
	print "Unknown platform: " + platform.system()
	Exit(1)


# Check GL headers
conf = Configure(env)
if not conf.CheckCHeader('gl.h') or not conf.CheckCHeader('glu.h'):
	print 'Shrimp requires OpenGL and GLU'
	Exit(1)

# Check FLTK 2 headers
if not conf.CheckCXXHeader('fltk/run.h'):
	print 'Shrimp requires FLTK 2'
	Exit(1)

env = conf.Finish()


# Debug
#env.Append(CXXFLAGS = '-O2')
env.Append(CXXFLAGS = '-g -Wall')
#env.Append(LINKFLAGS = '-static-libgcc')


# TinyXML
StaticLibrary('tinyxml', Split("""
	src/miscellaneous/tinyxml/tinystr.cpp
	src/miscellaneous/tinyxml/tinyxml.cpp
	src/miscellaneous/tinyxml/tinyxmlerror.cpp
	src/miscellaneous/tinyxml/tinyxmlparser.cpp
"""))


# Shrimp
env.Append(CPPPATH = ['src/application', 'src/miscellaneous', 'src/shading'])

shrimp_files = Split("""
	src/application/shrimp.cpp
	src/application/ui_about.cpp
	src/application/ui_application_window.cpp
	src/application/ui_scene_view.cpp
	src/application/ui_scene_view_events.cpp
	src/application/ui_splash.cpp
	src/miscellaneous/misc_system_functions.cpp
	src/miscellaneous/misc_xml.cpp
	src/miscellaneous/logging.cpp
	src/shading/console.cpp
	src/shading/preferences.cpp
	src/shading/shader_block.cpp
	src/shading/scene.cpp
	src/shading/scene_blocks.cpp
	src/shading/scene_grouping.cpp
	src/shading/scene_serialization.cpp
	src/shading/scene_selection.cpp
	src/shading/rib_root_block.cpp
""")


env.Program(target = 'shrimp', source = shrimp_files)


# File change test
Decider('timestamp-match')

