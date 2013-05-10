#
# Makefile for CS100 Assignment P3
#

#
# Common source/object files
#
SOURCES		= BitInputStream.cpp BitOutputStream.cpp HCNode.cpp HCTree.cpp
OBJECTS		= BitInputStream.o BitOutputStream.o HCNode.o HCTree.o

#
# Compress utility source/object files
# 
COMP_SRCS	= ${SOURCES} compress.cpp
COMP_OBJS	= ${OBJECTS} compress.o

#
# Uncompress utility source/object files
# 
UNCOMP_SRCS	= ${SOURCES} uncompress.cpp
UNCOMP_OBJS	= ${OBJECTS} uncompress.o

#
# Executable names
#
COMP_EXE	= compress
UNCOMP_EXE	= uncompress

#
# Compiler/linker flags
#
GCC		= g++
STDCPP		= -std=c++11
OPTIMIZATION	= -O2
WARNINGS	= -W -Wall -pedantic
GCC_FLAGS	= -c ${WARNINGS} ${OPTIMIZATION} ${STDCPP}
LD_FLAGS	= ${WARNINGS} ${OPTIMIZATION} ${STDCPP}

#
# make gdb=1
# Turns off optimizations and includes debugging symbols
#
ifeq ($(gdb), 1)
  GCC_FLAGS	+= -g
  LD_FLAGS	+= -g
  OPTIMIZATION	= -O0
endif

#
# Standard rules
#
.cpp.o:
	@echo "Compiling" $< "..."
	${GCC} ${GCC_FLAGS} $<
	@echo ""

default: ${COMP_EXE} ${UNCOMP_EXE}

${COMP_EXE}: ${OBJECTS} ${COMP_OBJS}
	@echo "Linking all object modules ..."
	${GCC} -o ${COMP_EXE} ${LD_FLAGS} ${COMP_OBJS}
	@echo ""

${UNCOMP_EXE}: ${OBJECTS} ${UNCOMP_OBJS}
	@echo "Linking all object modules ..."
	${GCC} -o ${UNCOMP_EXE} ${LD_FLAGS} ${UNCOMP_OBJS}
	@echo ""

clean:
	@echo "Cleaning up project directory ..."
	rm -f *.o ${COMP_EXE} ${UNCOMP_EXE} core a.out
	@echo ""
	@echo "Clean."

new:
	make clean
	make
