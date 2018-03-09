CC = g++ # define the C compiler to use
CFLAGS = -O3 -Wall -Wextra -pedantic -fPIC
# define any directories containing header files other than /usr/include
INCLUDES = -I/home/fran/drive/projects/VBBinaryLensing
# define the C++ source files
SRCS = VBBinaryLensingLibrary.cpp 
# define the C object files 
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
OBJS = $(SRCS:.c=.o)
# define the shared library name
TARGET = libVBB.so

.PHONY: clean
    
all:    $(TARGET)
	@echo  Successfully compiled.

# compile object file to .so shared library
$(TARGET): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -shared -o $(TARGET) $(OBJS) 

# compile source files to object files

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -cpp $<  -o $@
clean:
	$(RM) *.o 
