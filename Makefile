# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/parsa/Desktop/Programming/FOP96/Pacman

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/parsa/Desktop/Programming/FOP96/Pacman

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/parsa/Desktop/Programming/FOP96/Pacman/CMakeFiles /home/parsa/Desktop/Programming/FOP96/Pacman/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/parsa/Desktop/Programming/FOP96/Pacman/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Pacman

# Build rule for target.
Pacman: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Pacman
.PHONY : Pacman

# fast build rule for target.
Pacman/fast:
	$(MAKE) -f CMakeFiles/Pacman.dir/build.make CMakeFiles/Pacman.dir/build
.PHONY : Pacman/fast

src/game.o: src/game.c.o

.PHONY : src/game.o

# target to build an object file
src/game.c.o:
	$(MAKE) -f CMakeFiles/Pacman.dir/build.make CMakeFiles/Pacman.dir/src/game.c.o
.PHONY : src/game.c.o

src/game.i: src/game.c.i

.PHONY : src/game.i

# target to preprocess a source file
src/game.c.i:
	$(MAKE) -f CMakeFiles/Pacman.dir/build.make CMakeFiles/Pacman.dir/src/game.c.i
.PHONY : src/game.c.i

src/game.s: src/game.c.s

.PHONY : src/game.s

# target to generate assembly for a file
src/game.c.s:
	$(MAKE) -f CMakeFiles/Pacman.dir/build.make CMakeFiles/Pacman.dir/src/game.c.s
.PHONY : src/game.c.s

src/physics.o: src/physics.c.o

.PHONY : src/physics.o

# target to build an object file
src/physics.c.o:
	$(MAKE) -f CMakeFiles/Pacman.dir/build.make CMakeFiles/Pacman.dir/src/physics.c.o
.PHONY : src/physics.c.o

src/physics.i: src/physics.c.i

.PHONY : src/physics.i

# target to preprocess a source file
src/physics.c.i:
	$(MAKE) -f CMakeFiles/Pacman.dir/build.make CMakeFiles/Pacman.dir/src/physics.c.i
.PHONY : src/physics.c.i

src/physics.s: src/physics.c.s

.PHONY : src/physics.s

# target to generate assembly for a file
src/physics.c.s:
	$(MAKE) -f CMakeFiles/Pacman.dir/build.make CMakeFiles/Pacman.dir/src/physics.c.s
.PHONY : src/physics.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... Pacman"
	@echo "... edit_cache"
	@echo "... src/game.o"
	@echo "... src/game.i"
	@echo "... src/game.s"
	@echo "... src/physics.o"
	@echo "... src/physics.i"
	@echo "... src/physics.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
