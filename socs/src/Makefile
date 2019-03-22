INCPATH = \
-I.

AOCL=1

ifeq ($(AOCL),1)
MAKE_PTR = -DMAKE_PTR
CROSS-COMPILER=arm-linux-gnueabihf-
AOCL_COMPILE_CONFIG=$(shell aocl compile-config --arm)
AOCL_LINK_CONFIG=$(shell aocl link-config --arm)
else
MAKE_PTR = 
CROSS-COMPILER=
endif

CPP = $(CROSS-COMPILER)g++ # Compiler
LIBS := -lOpenCL # Libraries
SRC_DIR = ./
SRC_SOCS = ./socs/
SRC_OPENCL = ./socs/opencl/
SRC_SOCKET = ./socs/socket/
OBJDIR = ./obj/
EXEC = socs.exe # Executable
CFLAGS = -std=c++1y -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors # Display all warnings and errors
LDFLAGS= -pthread # Informations passed through the linker
OPTS := # Other options
USER = 
DEBUG = 0 # If you want to debug with an ide, just set this flag

# List of Objects
OBJ = \
Convolution.o \
OpenCL.o \
Socket.o \
App.o \
Exception.o \
main.o

# Append object file names
OBJS = $(addprefix $(OBJDIR), $(OBJ))

# Get all header files from src directory
DEPS_SRC_DIR = $(wildcard $(SRC_DIR)/*.h)

# Get all header files from socs directory
DEPS_SOCS = $(wildcard $(SRC_SOCS)/*.h)

# Get all header files from opencl directory
DEPS_OPENCL = $(wildcard $(SRC_OPENCL)/*.h)

# Get all header files from socket directory
DEPS_SOCKET = $(wildcard $(SRC_SOCKET)/*.h)

OPTS = -O3 -DNDEBUG
CFLAGS += $(OPTS) $(MAKE_PTR)

ifeq ($(DEBUG), 1) 
OPTS = -O0 -g3
CFLAGS += $(OPTS) $(MAKE_PTR)
endif

# All targets to build
all: obj $(EXEC)

# Linking
$(EXEC): $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	$(CPP) $(LDFLAGS) -o "$@" $(OBJS) $(LIBS) $(AOCL_LINK_CONFIG)
	@echo 'Finished building: $<'
	@echo ' '

# Compiling CPP files from proto directory
$(OBJDIR)%.o: $(SRC_DIR)%.cpp $(DEPS_SRC_DIR)
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CPP) $(USER) $(INCPATH) $(CFLAGS) -c $(LDFLAGS) $(AOCL_COMPILE_CONFIG) -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Compiling CPP files from socs directory
$(OBJDIR)%.o: $(SRC_SOCS)%.cpp $(DEPS_SOCS)
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CPP) $(USER) $(INCPATH) $(CFLAGS) -c $(LDFLAGS) $(AOCL_COMPILE_CONFIG) -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Compiling CPP files from opencl directory
$(OBJDIR)%.o: $(SRC_OPENCL)%.cpp $(DEPS_OPENCL)
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CPP) $(USER) $(INCPATH) $(CFLAGS) -c $(LDFLAGS) $(AOCL_COMPILE_CONFIG) -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Compiling CPP files from proto directory
$(OBJDIR)%.o: $(SRC_SOCKET)%.cpp $(DEPS_SOCKET)
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CPP) $(USER) $(INCPATH) $(CFLAGS) -c $(LDFLAGS) $(AOCL_COMPILE_CONFIG) -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Rule to make a directory for binaries
obj:
	@echo 'Making a folder for binaries if it does not exist'
	mkdir -p obj
	@echo ' '

# Clean project
.PHONY: clean

clean:
	@echo 'Cleaning Project'
	rm -rf $(OBJS) $(OBJDIR) $(EXEC)
	@echo ' '

