# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_SOURCE_DIR = /mnt/e/Cpp/Project03

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/e/Cpp/Project03

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /mnt/e/Cpp/Project03/CMakeFiles /mnt/e/Cpp/Project03//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /mnt/e/Cpp/Project03/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named matlib

# Build rule for target.
matlib: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 matlib
.PHONY : matlib

# fast build rule for target.
matlib/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/matlib.dir/build.make CMakeFiles/matlib.dir/build
.PHONY : matlib/fast

src/Benchmark.o: src/Benchmark.c.o
.PHONY : src/Benchmark.o

# target to build an object file
src/Benchmark.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/matlib.dir/build.make CMakeFiles/matlib.dir/src/Benchmark.c.o
.PHONY : src/Benchmark.c.o

src/Benchmark.i: src/Benchmark.c.i
.PHONY : src/Benchmark.i

# target to preprocess a source file
src/Benchmark.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/matlib.dir/build.make CMakeFiles/matlib.dir/src/Benchmark.c.i
.PHONY : src/Benchmark.c.i

src/Benchmark.s: src/Benchmark.c.s
.PHONY : src/Benchmark.s

# target to generate assembly for a file
src/Benchmark.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/matlib.dir/build.make CMakeFiles/matlib.dir/src/Benchmark.c.s
.PHONY : src/Benchmark.c.s

src/MatrixC.o: src/MatrixC.c.o
.PHONY : src/MatrixC.o

# target to build an object file
src/MatrixC.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/matlib.dir/build.make CMakeFiles/matlib.dir/src/MatrixC.c.o
.PHONY : src/MatrixC.c.o

src/MatrixC.i: src/MatrixC.c.i
.PHONY : src/MatrixC.i

# target to preprocess a source file
src/MatrixC.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/matlib.dir/build.make CMakeFiles/matlib.dir/src/MatrixC.c.i
.PHONY : src/MatrixC.c.i

src/MatrixC.s: src/MatrixC.c.s
.PHONY : src/MatrixC.s

# target to generate assembly for a file
src/MatrixC.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/matlib.dir/build.make CMakeFiles/matlib.dir/src/MatrixC.c.s
.PHONY : src/MatrixC.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... matlib"
	@echo "... src/Benchmark.o"
	@echo "... src/Benchmark.i"
	@echo "... src/Benchmark.s"
	@echo "... src/MatrixC.o"
	@echo "... src/MatrixC.i"
	@echo "... src/MatrixC.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

