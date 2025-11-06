MAKEFLAGS += --no-builtin-rules --no-builtin-variables

CXX := g++

include Makefile.localconfig

ifdef DEBUG
  debug_defs := DEBUG _DEBUG
  debug_cxx_flags := -O0 -ggdb3
else
  debug_defs := NDEBUG
  debug_cxx_flags := -O3 -s
endif

ifndef NOWARN
  warnings := -Wall -Wextra -Werror
endif

# Equality function
eq = $(and $(findstring $(1),$(2)),$(findstring $(2),$(1)))

# Source files
src := $(wildcard *.cpp)
# Source headers (needed for generate_dep.sh)
hdr := $(wildcard *.hpp)
# Source dependencies
dep := $(src:.cpp=.d)
# Source objects
obj := $(src:.cpp=.o)
# Preprocessor definitions
defs := $(debug_defs)
# Compiler/preprocessor flags
CXXFLAGS := $(warnings) $(debug_cxx_flags) $(addprefix -D,$(defs))
# Linker flags
LDFLAGS := -static -static-libstdc++

.PHONY: all clean test
all:

# Build missing dependencies (existing ones can remake themselves)
$(filter-out $(wildcard *.d),$(dep)): %.d: %.cpp
	./generate_dep.sh "$(CXX)" "$(<:.cpp=)"
	
# Build executables
tests: $(obj)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Build source objects
$(obj): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I.

# Deletes all generated files
clean:
	rm -rf javas $(obj) $(dep)

# Runs unit tests
test: tests
	./tests

# Existing dependency files have rules to update themselves. This also directs make to build
# missing dep files.
# Don't update/generate dependency files if clean is the only target.
ifeq (,$(call eq,clean,$(MAKECMDGOALS)))
  include $(dep)
endif
