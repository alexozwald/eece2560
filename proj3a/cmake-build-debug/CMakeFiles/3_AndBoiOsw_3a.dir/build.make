# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/aozwald/Documents/2560/3-AndBoiOsw-3a

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/aozwald/Documents/2560/3-AndBoiOsw-3a/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/3_AndBoiOsw_3a.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/3_AndBoiOsw_3a.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/3_AndBoiOsw_3a.dir/flags.make

CMakeFiles/3_AndBoiOsw_3a.dir/main.cpp.o: CMakeFiles/3_AndBoiOsw_3a.dir/flags.make
CMakeFiles/3_AndBoiOsw_3a.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aozwald/Documents/2560/3-AndBoiOsw-3a/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/3_AndBoiOsw_3a.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/3_AndBoiOsw_3a.dir/main.cpp.o -c /Users/aozwald/Documents/2560/3-AndBoiOsw-3a/main.cpp

CMakeFiles/3_AndBoiOsw_3a.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/3_AndBoiOsw_3a.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/aozwald/Documents/2560/3-AndBoiOsw-3a/main.cpp > CMakeFiles/3_AndBoiOsw_3a.dir/main.cpp.i

CMakeFiles/3_AndBoiOsw_3a.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/3_AndBoiOsw_3a.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/aozwald/Documents/2560/3-AndBoiOsw-3a/main.cpp -o CMakeFiles/3_AndBoiOsw_3a.dir/main.cpp.s

# Object files for target 3_AndBoiOsw_3a
3_AndBoiOsw_3a_OBJECTS = \
"CMakeFiles/3_AndBoiOsw_3a.dir/main.cpp.o"

# External object files for target 3_AndBoiOsw_3a
3_AndBoiOsw_3a_EXTERNAL_OBJECTS =

3_AndBoiOsw_3a: CMakeFiles/3_AndBoiOsw_3a.dir/main.cpp.o
3_AndBoiOsw_3a: CMakeFiles/3_AndBoiOsw_3a.dir/build.make
3_AndBoiOsw_3a: CMakeFiles/3_AndBoiOsw_3a.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/aozwald/Documents/2560/3-AndBoiOsw-3a/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 3_AndBoiOsw_3a"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/3_AndBoiOsw_3a.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/3_AndBoiOsw_3a.dir/build: 3_AndBoiOsw_3a
.PHONY : CMakeFiles/3_AndBoiOsw_3a.dir/build

CMakeFiles/3_AndBoiOsw_3a.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/3_AndBoiOsw_3a.dir/cmake_clean.cmake
.PHONY : CMakeFiles/3_AndBoiOsw_3a.dir/clean

CMakeFiles/3_AndBoiOsw_3a.dir/depend:
	cd /Users/aozwald/Documents/2560/3-AndBoiOsw-3a/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/aozwald/Documents/2560/3-AndBoiOsw-3a /Users/aozwald/Documents/2560/3-AndBoiOsw-3a /Users/aozwald/Documents/2560/3-AndBoiOsw-3a/cmake-build-debug /Users/aozwald/Documents/2560/3-AndBoiOsw-3a/cmake-build-debug /Users/aozwald/Documents/2560/3-AndBoiOsw-3a/cmake-build-debug/CMakeFiles/3_AndBoiOsw_3a.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/3_AndBoiOsw_3a.dir/depend

