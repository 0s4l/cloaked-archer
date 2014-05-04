# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lanham/TRW/cloaked-archer/blocking_search

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lanham/TRW/cloaked-archer/blocking_search/build

# Include any dependencies generated for this target.
include software/routines/CMakeFiles/BlockingSearch.dir/depend.make

# Include the progress variables for this target.
include software/routines/CMakeFiles/BlockingSearch.dir/progress.make

# Include the compile flags for this target's objects.
include software/routines/CMakeFiles/BlockingSearch.dir/flags.make

software/routines/CMakeFiles/BlockingSearch.dir/src/blocking.cpp.o: software/routines/CMakeFiles/BlockingSearch.dir/flags.make
software/routines/CMakeFiles/BlockingSearch.dir/src/blocking.cpp.o: ../software/routines/src/blocking.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lanham/TRW/cloaked-archer/blocking_search/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object software/routines/CMakeFiles/BlockingSearch.dir/src/blocking.cpp.o"
	cd /home/lanham/TRW/cloaked-archer/blocking_search/build/software/routines && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/BlockingSearch.dir/src/blocking.cpp.o -c /home/lanham/TRW/cloaked-archer/blocking_search/software/routines/src/blocking.cpp

software/routines/CMakeFiles/BlockingSearch.dir/src/blocking.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BlockingSearch.dir/src/blocking.cpp.i"
	cd /home/lanham/TRW/cloaked-archer/blocking_search/build/software/routines && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lanham/TRW/cloaked-archer/blocking_search/software/routines/src/blocking.cpp > CMakeFiles/BlockingSearch.dir/src/blocking.cpp.i

software/routines/CMakeFiles/BlockingSearch.dir/src/blocking.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BlockingSearch.dir/src/blocking.cpp.s"
	cd /home/lanham/TRW/cloaked-archer/blocking_search/build/software/routines && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lanham/TRW/cloaked-archer/blocking_search/software/routines/src/blocking.cpp -o CMakeFiles/BlockingSearch.dir/src/blocking.cpp.s

software/routines/CMakeFiles/BlockingSearch.dir/src/blocking.cpp.o.requires:
.PHONY : software/routines/CMakeFiles/BlockingSearch.dir/src/blocking.cpp.o.requires

software/routines/CMakeFiles/BlockingSearch.dir/src/blocking.cpp.o.provides: software/routines/CMakeFiles/BlockingSearch.dir/src/blocking.cpp.o.requires
	$(MAKE) -f software/routines/CMakeFiles/BlockingSearch.dir/build.make software/routines/CMakeFiles/BlockingSearch.dir/src/blocking.cpp.o.provides.build
.PHONY : software/routines/CMakeFiles/BlockingSearch.dir/src/blocking.cpp.o.provides

software/routines/CMakeFiles/BlockingSearch.dir/src/blocking.cpp.o.provides.build: software/routines/CMakeFiles/BlockingSearch.dir/src/blocking.cpp.o

# Object files for target BlockingSearch
BlockingSearch_OBJECTS = \
"CMakeFiles/BlockingSearch.dir/src/blocking.cpp.o"

# External object files for target BlockingSearch
BlockingSearch_EXTERNAL_OBJECTS =

../bin/BlockingSearch: software/routines/CMakeFiles/BlockingSearch.dir/src/blocking.cpp.o
../bin/BlockingSearch: software/FSM_library/libFSM_library.a
../bin/BlockingSearch: software/routines/CMakeFiles/BlockingSearch.dir/build.make
../bin/BlockingSearch: software/routines/CMakeFiles/BlockingSearch.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../bin/BlockingSearch"
	cd /home/lanham/TRW/cloaked-archer/blocking_search/build/software/routines && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BlockingSearch.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
software/routines/CMakeFiles/BlockingSearch.dir/build: ../bin/BlockingSearch
.PHONY : software/routines/CMakeFiles/BlockingSearch.dir/build

software/routines/CMakeFiles/BlockingSearch.dir/requires: software/routines/CMakeFiles/BlockingSearch.dir/src/blocking.cpp.o.requires
.PHONY : software/routines/CMakeFiles/BlockingSearch.dir/requires

software/routines/CMakeFiles/BlockingSearch.dir/clean:
	cd /home/lanham/TRW/cloaked-archer/blocking_search/build/software/routines && $(CMAKE_COMMAND) -P CMakeFiles/BlockingSearch.dir/cmake_clean.cmake
.PHONY : software/routines/CMakeFiles/BlockingSearch.dir/clean

software/routines/CMakeFiles/BlockingSearch.dir/depend:
	cd /home/lanham/TRW/cloaked-archer/blocking_search/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lanham/TRW/cloaked-archer/blocking_search /home/lanham/TRW/cloaked-archer/blocking_search/software/routines /home/lanham/TRW/cloaked-archer/blocking_search/build /home/lanham/TRW/cloaked-archer/blocking_search/build/software/routines /home/lanham/TRW/cloaked-archer/blocking_search/build/software/routines/CMakeFiles/BlockingSearch.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : software/routines/CMakeFiles/BlockingSearch.dir/depend

