# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/seb/CPP_rtype_2018

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/seb/CPP_rtype_2018

# Include any dependencies generated for this target.
include CMakeFiles/rtype.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rtype.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rtype.dir/flags.make

CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.o: CMakeFiles/rtype.dir/flags.make
CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.o: src/game_engine/ecs/Entity.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seb/CPP_rtype_2018/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.o -c /home/seb/CPP_rtype_2018/src/game_engine/ecs/Entity.cpp

CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seb/CPP_rtype_2018/src/game_engine/ecs/Entity.cpp > CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.i

CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seb/CPP_rtype_2018/src/game_engine/ecs/Entity.cpp -o CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.s

CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.o.requires:

.PHONY : CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.o.requires

CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.o.provides: CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.o.requires
	$(MAKE) -f CMakeFiles/rtype.dir/build.make CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.o.provides.build
.PHONY : CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.o.provides

CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.o.provides.build: CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.o


CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.o: CMakeFiles/rtype.dir/flags.make
CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.o: src/game_engine/system/graphical/InitAnimatedSprite.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seb/CPP_rtype_2018/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.o -c /home/seb/CPP_rtype_2018/src/game_engine/system/graphical/InitAnimatedSprite.cpp

CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seb/CPP_rtype_2018/src/game_engine/system/graphical/InitAnimatedSprite.cpp > CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.i

CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seb/CPP_rtype_2018/src/game_engine/system/graphical/InitAnimatedSprite.cpp -o CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.s

CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.o.requires:

.PHONY : CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.o.requires

CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.o.provides: CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.o.requires
	$(MAKE) -f CMakeFiles/rtype.dir/build.make CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.o.provides.build
.PHONY : CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.o.provides

CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.o.provides.build: CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.o


CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.o: CMakeFiles/rtype.dir/flags.make
CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.o: src/game_engine/core/Time.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seb/CPP_rtype_2018/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.o -c /home/seb/CPP_rtype_2018/src/game_engine/core/Time.cpp

CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seb/CPP_rtype_2018/src/game_engine/core/Time.cpp > CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.i

CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seb/CPP_rtype_2018/src/game_engine/core/Time.cpp -o CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.s

CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.o.requires:

.PHONY : CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.o.requires

CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.o.provides: CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.o.requires
	$(MAKE) -f CMakeFiles/rtype.dir/build.make CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.o.provides.build
.PHONY : CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.o.provides

CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.o.provides.build: CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.o


CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.o: CMakeFiles/rtype.dir/flags.make
CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.o: src/game_engine/sfml/Graphic.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seb/CPP_rtype_2018/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.o -c /home/seb/CPP_rtype_2018/src/game_engine/sfml/Graphic.cpp

CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seb/CPP_rtype_2018/src/game_engine/sfml/Graphic.cpp > CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.i

CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seb/CPP_rtype_2018/src/game_engine/sfml/Graphic.cpp -o CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.s

CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.o.requires:

.PHONY : CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.o.requires

CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.o.provides: CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.o.requires
	$(MAKE) -f CMakeFiles/rtype.dir/build.make CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.o.provides.build
.PHONY : CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.o.provides

CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.o.provides.build: CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.o


CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.o: CMakeFiles/rtype.dir/flags.make
CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.o: src/game_engine/system/control/Controls.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seb/CPP_rtype_2018/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.o -c /home/seb/CPP_rtype_2018/src/game_engine/system/control/Controls.cpp

CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seb/CPP_rtype_2018/src/game_engine/system/control/Controls.cpp > CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.i

CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seb/CPP_rtype_2018/src/game_engine/system/control/Controls.cpp -o CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.s

CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.o.requires:

.PHONY : CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.o.requires

CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.o.provides: CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.o.requires
	$(MAKE) -f CMakeFiles/rtype.dir/build.make CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.o.provides.build
.PHONY : CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.o.provides

CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.o.provides.build: CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.o


CMakeFiles/rtype.dir/src/Main.cpp.o: CMakeFiles/rtype.dir/flags.make
CMakeFiles/rtype.dir/src/Main.cpp.o: src/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seb/CPP_rtype_2018/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/rtype.dir/src/Main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rtype.dir/src/Main.cpp.o -c /home/seb/CPP_rtype_2018/src/Main.cpp

CMakeFiles/rtype.dir/src/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rtype.dir/src/Main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seb/CPP_rtype_2018/src/Main.cpp > CMakeFiles/rtype.dir/src/Main.cpp.i

CMakeFiles/rtype.dir/src/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rtype.dir/src/Main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seb/CPP_rtype_2018/src/Main.cpp -o CMakeFiles/rtype.dir/src/Main.cpp.s

CMakeFiles/rtype.dir/src/Main.cpp.o.requires:

.PHONY : CMakeFiles/rtype.dir/src/Main.cpp.o.requires

CMakeFiles/rtype.dir/src/Main.cpp.o.provides: CMakeFiles/rtype.dir/src/Main.cpp.o.requires
	$(MAKE) -f CMakeFiles/rtype.dir/build.make CMakeFiles/rtype.dir/src/Main.cpp.o.provides.build
.PHONY : CMakeFiles/rtype.dir/src/Main.cpp.o.provides

CMakeFiles/rtype.dir/src/Main.cpp.o.provides.build: CMakeFiles/rtype.dir/src/Main.cpp.o


# Object files for target rtype
rtype_OBJECTS = \
"CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.o" \
"CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.o" \
"CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.o" \
"CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.o" \
"CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.o" \
"CMakeFiles/rtype.dir/src/Main.cpp.o"

# External object files for target rtype
rtype_EXTERNAL_OBJECTS =

rtype: CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.o
rtype: CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.o
rtype: CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.o
rtype: CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.o
rtype: CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.o
rtype: CMakeFiles/rtype.dir/src/Main.cpp.o
rtype: CMakeFiles/rtype.dir/build.make
rtype: /usr/lib/x86_64-linux-gnu/libsfml-window.so
rtype: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so
rtype: /usr/lib/x86_64-linux-gnu/libsfml-system.so
rtype: /usr/lib/x86_64-linux-gnu/libsfml-audio.so
rtype: CMakeFiles/rtype.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/seb/CPP_rtype_2018/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable rtype"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rtype.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rtype.dir/build: rtype

.PHONY : CMakeFiles/rtype.dir/build

CMakeFiles/rtype.dir/requires: CMakeFiles/rtype.dir/src/game_engine/ecs/Entity.cpp.o.requires
CMakeFiles/rtype.dir/requires: CMakeFiles/rtype.dir/src/game_engine/system/graphical/InitAnimatedSprite.cpp.o.requires
CMakeFiles/rtype.dir/requires: CMakeFiles/rtype.dir/src/game_engine/core/Time.cpp.o.requires
CMakeFiles/rtype.dir/requires: CMakeFiles/rtype.dir/src/game_engine/sfml/Graphic.cpp.o.requires
CMakeFiles/rtype.dir/requires: CMakeFiles/rtype.dir/src/game_engine/system/control/Controls.cpp.o.requires
CMakeFiles/rtype.dir/requires: CMakeFiles/rtype.dir/src/Main.cpp.o.requires

.PHONY : CMakeFiles/rtype.dir/requires

CMakeFiles/rtype.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rtype.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rtype.dir/clean

CMakeFiles/rtype.dir/depend:
	cd /home/seb/CPP_rtype_2018 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/seb/CPP_rtype_2018 /home/seb/CPP_rtype_2018 /home/seb/CPP_rtype_2018 /home/seb/CPP_rtype_2018 /home/seb/CPP_rtype_2018/CMakeFiles/rtype.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rtype.dir/depend

