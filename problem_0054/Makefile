ifndef VERBOSE
.SILENT:
endif

APPNAME := program
OBJDIR  := objects
DEPDIR  := objects
SOURCES := $(shell find . -maxdepth 1 -name "*.cpp")
PHE_SRC := ./phe-wasm/src
SOURCES += ${PHE_SRC}/evaluator5.c ${PHE_SRC}/hash.c ${PHE_SRC}/hashtable.c \
           ${PHE_SRC}/hashtable5.c ${PHE_SRC}/dptables.c
INCDIRS := -I ../include -I ./phe-wasm/include

vpath %.c $(PHE_SRC)

CXX := g++
CXXFLAGS := -g -std=c++23 -Wall -Wextra -Werror -pedantic -O3 $(INCDIRS) -fopenmp
EXTRA_LINK_FLAGS := -lgmpxx -lgmp

OBJECTS_WRONG_DIR := $(foreach source, $(SOURCES), $(basename $(source)).o)
OBJECTS := $(addprefix $(OBJDIR)/, $(notdir $(OBJECTS_WRONG_DIR)))

define mkdir_target
test -d $(@D) \
  || ( echo "Creating directory $(@D)" && mkdir -p $(@D) ) \
  || echo Unable to create $(@D);
endef

.PHONY: all clean

all: $(APPNAME)

$(APPNAME): $(OBJECTS)
	$(mkdir_target)
	$(CXX) -o $(APPNAME) $(OBJECTS) $(EXTRA_LINK_FLAGS)

$(OBJDIR)/%.o : %.cpp
	$(mkdir_target)
	@echo Compiling $<
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(OBJDIR)/%.o : %.c
	$(mkdir_target)
	@echo Compiling $<
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	@echo Removing objects
	rm -f $(OBJECTS) > /dev/null 2>&1
	rm -rf $(OBJDIR) > /dev/null 2>&1
	@echo Removing executable
	rm -f $(APPNAME) > /dev/null 2>&1
