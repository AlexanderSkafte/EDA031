# Define the compiler and the linker. The linker must be defined since
# the implicit rule for linking uses CC as the linker. g++ can be
# changed to clang++.
CXX = g++
CC  = g++

# Define preprocessor, compiler, and linker flags. Uncomment the # lines
# if you use clang++ and wish to use libc++ instead of libstd++.
CPPFLAGS  = -std=c++11 -I..
CXXFLAGS  = -g -O2 -Wall -W -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast 
CXXFLAGS += -std=c++11 
LDFLAGS   = -g -L..
#CPPFLAGS += -stdlib=libc++
#CXXFLAGS += -stdlib=libc++
#LDFLAGS +=  -stdlib=libc++

# Libraries
#LDLIBS = -lclientserver

# Targets
PROGS = client server_main testDisk server_disk

all: $(PROGS)

# Targets rely on implicit rules for compiling and linking
# The dependency on libclientserve	r.a is not defined.
#TestDNA: TestDNA.o in_memory_data_base.o newsgroup.o article.o connection.o messagehandler.o 
client: client.o in_memory_data_base.o newsgroup.o article.o connection.o messagehandler.o server.o connection.o
server_main: in_memory_data_base.o newsgroup.o article.o connection.o messagehandler.o  server_main.o adapter.o server.o connection.o 
server_disk: adapter_disk.o disk_memory_data_base.o newsgroup.o article.o connection.o messagehandler.o server_disk.o server.o connection.o
testDisk: testDisk.o disk_memory_data_base.o newsgroup.o article.o connection.o messagehandler.o
# Phony targets
.PHONY: all clean

# Standard clean
clean:
	rm -f *.o $(PROGS)
	rm -rf ./../bin

install:
	mkdir -p ./../bin
	cp client server_main server_disk testDisk ./../bin

# Generate dependencies in *.d files
%.d: %.cc
	@set -e; rm -f $@; \
         $(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

# Include the *.d files
SRC = $(wildcard *.cc)
include $(SRC:.cc=.d)
