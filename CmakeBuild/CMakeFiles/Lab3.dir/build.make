# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/crystal/compilerPriciple/Lab

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/crystal/compilerPriciple/Lab/CmakeBuild

# Include any dependencies generated for this target.
include CMakeFiles/Lab3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Lab3.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Lab3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lab3.dir/flags.make

CMakeFiles/Lab3.dir/src/Lab3.c.o: CMakeFiles/Lab3.dir/flags.make
CMakeFiles/Lab3.dir/src/Lab3.c.o: ../src/Lab3.c
CMakeFiles/Lab3.dir/src/Lab3.c.o: CMakeFiles/Lab3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/crystal/compilerPriciple/Lab/CmakeBuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Lab3.dir/src/Lab3.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Lab3.dir/src/Lab3.c.o -MF CMakeFiles/Lab3.dir/src/Lab3.c.o.d -o CMakeFiles/Lab3.dir/src/Lab3.c.o -c /home/crystal/compilerPriciple/Lab/src/Lab3.c

CMakeFiles/Lab3.dir/src/Lab3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Lab3.dir/src/Lab3.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/crystal/compilerPriciple/Lab/src/Lab3.c > CMakeFiles/Lab3.dir/src/Lab3.c.i

CMakeFiles/Lab3.dir/src/Lab3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Lab3.dir/src/Lab3.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/crystal/compilerPriciple/Lab/src/Lab3.c -o CMakeFiles/Lab3.dir/src/Lab3.c.s

# Object files for target Lab3
Lab3_OBJECTS = \
"CMakeFiles/Lab3.dir/src/Lab3.c.o"

# External object files for target Lab3
Lab3_EXTERNAL_OBJECTS =

../crystal/Lab3: CMakeFiles/Lab3.dir/src/Lab3.c.o
../crystal/Lab3: CMakeFiles/Lab3.dir/build.make
../crystal/Lab3: lib/libInterCodeGenerator.a
../crystal/Lab3: lib/libSemanticAnalyzer.a
../crystal/Lab3: lib/libParserAnalyzer.a
../crystal/Lab3: lib/libParser.a
../crystal/Lab3: lib/libLexer.a
../crystal/Lab3: /usr/lib/x86_64-linux-gnu/libfl.so
../crystal/Lab3: lib/libErrorReporter.a
../crystal/Lab3: lib/libSimpleContainers.a
../crystal/Lab3: CMakeFiles/Lab3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/crystal/compilerPriciple/Lab/CmakeBuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../crystal/Lab3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lab3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lab3.dir/build: ../crystal/Lab3
.PHONY : CMakeFiles/Lab3.dir/build

CMakeFiles/Lab3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lab3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lab3.dir/clean

CMakeFiles/Lab3.dir/depend:
	cd /home/crystal/compilerPriciple/Lab/CmakeBuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/crystal/compilerPriciple/Lab /home/crystal/compilerPriciple/Lab /home/crystal/compilerPriciple/Lab/CmakeBuild /home/crystal/compilerPriciple/Lab/CmakeBuild /home/crystal/compilerPriciple/Lab/CmakeBuild/CMakeFiles/Lab3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Lab3.dir/depend

