INCPATH = \
-I/usr/include/x86_64-linux-gnu/qt5 \
-I/usr/include/x86_64-linux-gnu/qt5/QtWidgets \
-I/usr/include/x86_64-linux-gnu/qt5/QtGui \
-I/usr/include/x86_64-linux-gnu/qt5/QtCore \
-I.

CPP = g++ # Compiler
LIBS := -lQt5Core -lQt5Gui -lQt5Widgets -lprotobuf # Libraries
SRC_HEPICS = ./hepics/
SRC_GUI = ./gui/
SRC_PROTO = ./proto/
OBJDIR = ./obj/
EXEC = hepics.exe # Executable
CFLAGS = -std=c++1y -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC # Display all warnings and errors
LDFLAGS= -pthread # Informations passed through the linker
OPTS := # Other options
USER = 

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

OPTS = -O3
CFLAGS += $(OPTS)

GEN_PROTO = \
proto/caffe.pb.h \
proto/caffe.pb.cc

GEN_MOC = \
gui/moc_control_section.cpp \
gui/moc_image_section.cpp \
gui/moc_main_window.cpp \
gui/moc_platform_mode_section.cpp \
gui/moc_welcome_window.cpp

# All targets to build
all: obj $(GEN_PROTO) $(GEN_MOC) $(EXEC)

$(GEN_PROTO): proto/caffe.proto
	@echo 'Compiling protobuf definition'
	protoc proto/caffe.proto --cpp_out .
	@echo 'Protobuf definition compiled'
	@echo ' '

$(SRC_GUI)moc_%.cpp: $(SRC_GUI)%.h
	@echo 'Precompiling file: $<'
	moc '$<' > '$@'
	@echo 'Finished building: $<'
	@echo ' '

# Linking
$(EXEC): $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	$(CPP) $(LDFLAGS) -o "$@" $(OBJS) $(LIBS)
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
.PHONY: clean install precompile

clean:
	@echo 'Cleaning Project'
	rm -rf $(OBJS) $(OBJDIR) $(EXEC) $(GEN_PROTO) $(GEN_MOC)
	@echo ' '

install:
	@if ! [ "$(shell id -u -r)" -eq 0 ]; then \
		echo "Please run as root user"; \
		exit 1; \
	fi
	@echo 'Installing'
	sudo mkdir -m 0755 -p /opt/hepics
	cp hepics.exe /opt/hepics/hepics
	cp ../bvlc_alexnet.caffemodel /opt/hepics/
	cp ../synset_words.txt /opt/hepics/
	cp ../welcome_image.jpeg /opt/hepics/
	cp ../imagenet_mean.binaryproto /opt/hepics/
	ln -fs /opt/hepics/hepics /usr/bin/
	@echo 'Installed'
	
precompile: $(GEN_PROTO) $(GEN_MOC)


