#
#
#
# Variables
CXX      :=   g++
CFLAGS   :=
CPPFLAGS := -I./include 
LDFLAGS  := 

ifeq (x$(METHOD),x)
METHOD := dbg
endif

ifeq ($(METHOD),opt)
  obj-suffix:=opt.o
  bin-suffix:=-opt.exe 
  CFLAGS := -O2 -fPIC -funroll-loops -fstrict-aliasing
endif

ifeq ($(METHOD),dbg)
  obj-suffix:= dbg.o
  bin-suffix:=-dbg.exe 
  CFLAGS := -g
endif

#depedencies
#GTS
GTS_DIR     :=
GTS_INCLUDE := 
GTS_LIB     := -lgts

#GLIB
GLIB_INCLUDE := -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/
GLIB_LIB     := -lglib-2.0 

CPPFLAGS += $(GTS_INCLUDE) $(GLIB_INCLUDE)
LDFLAGS  += $(GTS_LIB) $(GLIB_LIB)



# files
srcfiles := $(wildcard src/*.cpp)
objects  := $(patsubst %.cpp, %.$(obj-suffix), $(srcfiles))


all: ./bin/coast2d3d$(bin-suffix)

./bin/coast2d3d$(bin-suffix): $(objects)
	@echo "Linking "$@
	@$(CXX) -o $@  $(objects) $(LDFLAGS)


%.$(obj-suffix): %.cpp
	@echo "Compiling C++ (in "$(METHOD)" mode) "$<"..."
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $< -o $@


clean:
	rm $(objects)


