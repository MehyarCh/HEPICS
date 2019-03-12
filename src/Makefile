INCPATH = \
-I/usr/include/x86_64-linux-gnu/qt5 \
-I/usr/include/x86_64-linux-gnu/qt5/QtWidgets \
-I/usr/include/x86_64-linux-gnu/qt5/QtGui \
-I/usr/include/x86_64-linux-gnu/qt5/QtCore

CPP = g++ # Compiler
DEBUG = 1 # Debugger
LIBS := -lQt5Core -lQt5Gui -lQt5Widgets -lprotobuf # Libraries
SRC_HEPICS = ./hepics/
SRC_GUI = ./gui/
SRC_PROTO = ./proto/
OBJDIR = ./obj/
EXEC = hepics.exe # Executable
CFLAGS = -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC # Display all warnings and errors
LDFLAGS= -pthread # Informations passed through the linker
OPTS := # Other options
USER = -DUSER_IBRAHIM

# List of Objects
OBJ = \
Assistant.o \
Caffemodel.o \
Classifier.o \
Convolutional_layer.o \
DataSaver.o \
Exception.o \
Fully_connected_layer.o \
Function_layer.o \
Image.o \
Layer.o \
Local_response_normalization_layer.o \
Maxpool_layer.o \
Network.o \
Result.o \
Scheduler.o \
caffe.pb.o \
control_section.o \
image_section.o \
main.o \
main_window.o \
moc_control_section.o \
moc_image_section.o \
moc_main_window.o \
moc_platform_mode_section.o \
moc_welcome_window.o \
platform_mode_section.o \
welcome_window.o 

# Append object file names
OBJS = $(addprefix $(OBJDIR), $(OBJ))

# Get all header files from hepics directory
DEPS_HEPICS = $(wildcard $(SRC_HEPICS)/*.h)

# Get all header files from gui directory
DEPS_GUI = $(wildcard $(SRC_GUI)/*.h)

# Get all header files from prot directory
DEPS_PROTO = $(wildcard $(SRC_PROTO)/*.h)

# Set debugger options
ifeq ($(DEBUG), 1) 
OPTS = -O0 -g3
CFLAGS += $(OPTS)
endif

# All targets to build
all: obj $(EXEC)

# Linking
$(EXEC): $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ $(LDFLAGS) -o "$@" $(OBJS) $(LIBS)
	@echo 'Finished building: $<'
	@echo ' '

# Compiling CPP files from hepics directory
$(OBJDIR)%.o: $(SRC_HEPICS)%.cpp $(DEPS_HEPICS)
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CPP) $(USER) $(INCPATH) $(CFLAGS) -c $(LDFLAGS) -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Compiling CPP files from gui directory
$(OBJDIR)%.o: $(SRC_GUI)%.cpp $(DEPS_GUI)
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CPP) $(USER) $(INCPATH) $(CFLAGS) -c $(LDFLAGS) -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Compiling CC files from proto directory
$(OBJDIR)%.o: $(SRC_PROTO)%.cc $(DEPS_PROTO)
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CPP) $(USER) $(INCPATH) $(CFLAGS) -c $(LDFLAGS) -o "$@" "$<"
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

