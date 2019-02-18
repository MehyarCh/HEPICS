TEMPLATE = app
TARGET = HePICS

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

HEADERS += \
    welcomewindow.h \
    mainwindow.h \
    platform_mode_section.h \
    image_section.h \
    control_section.h \
    HepicsModel/src/Assistant.h \
    HepicsModel/src/Classifier.h \
    HepicsModel/src/DataSaver.h \
    HepicsModel/src/Image.h \
    HepicsModel/src/Layer.h \
    HepicsModel/src/NeuralNetwork.h \
    HepicsModel/src/Result.h \
    HepicsModel/src/Scheduler.h \
    HepicsModel/src/stb_image.h \
    HepicsModel/src/Worker.h \
    ImageClassificationSystem/src/Activation.h \
    ImageClassificationSystem/src/BLAS.h \
    ImageClassificationSystem/src/Classifier.h \
    ImageClassificationSystem/src/Connected_layer.h \
    ImageClassificationSystem/src/Convolutional_layer.h \
    ImageClassificationSystem/src/IM2COL.h \
    ImageClassificationSystem/src/Image.h \
    ImageClassificationSystem/src/Layer.h \
    ImageClassificationSystem/src/Layer_Type.h \
    ImageClassificationSystem/src/List.h \
    ImageClassificationSystem/src/Maxpool_layer.h \
    ImageClassificationSystem/src/Network.h \
    ImageClassificationSystem/src/Node.h \
    ImageClassificationSystem/src/Options_list.h \
    ImageClassificationSystem/src/Parser.h \
    ImageClassificationSystem/src/Section.h \
    ImageClassificationSystem/src/Softmax_layer.h \
    ImageClassificationSystem/src/stb_image.h \
    ImageClassificationSystem/src/Utils.h \
    socs/src/socs/opencl/Aligned_array.h \
    socs/src/socs/opencl/Convolution.h \
    socs/src/socs/opencl/OpenCL.h \
    socs/src/socs/socket/Socket.h \
    socs/src/socs/App.h \
    socs/src/socs/Exception.h \
    control_section.h \
    image_section.h \
    mainwindow.h \
    platform_mode_section.h \
    welcomewindow.h

SOURCES += \
    welcomewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    platform_mode_section.cpp \
    image_section.cpp \
    control_section.cpp \
    HepicsModel/src/Assistant.cpp \
    HepicsModel/src/Classifier.cpp \
    HepicsModel/src/DataSaver.cpp \
    HepicsModel/src/Image.cpp \
    HepicsModel/src/Layer.cpp \
    HepicsModel/src/Main.cpp \
    HepicsModel/src/NeuralNetwork.cpp \
    HepicsModel/src/Result.cpp \
    HepicsModel/src/Scheduler.cpp \
    HepicsModel/src/Worker.cpp \
    ImageClassificationSystem/src/Activation.cpp \
    ImageClassificationSystem/src/Classifier.cpp \
    ImageClassificationSystem/src/Connected_layer.cpp \
    ImageClassificationSystem/src/Convolutional_layer.cpp \
    ImageClassificationSystem/src/Hepics.cpp \
    ImageClassificationSystem/src/Image.cpp \
    ImageClassificationSystem/src/Layer.cpp \
    ImageClassificationSystem/src/Layer_Type.cpp \
    ImageClassificationSystem/src/List.cpp \
    ImageClassificationSystem/src/Maxpool_layer.cpp \
    ImageClassificationSystem/src/Network.cpp \
    ImageClassificationSystem/src/Node.cpp \
    ImageClassificationSystem/src/Options_list.cpp \
    ImageClassificationSystem/src/Section.cpp \
    ImageClassificationSystem/src/Softmax_layer.cpp \
    ImageClassificationSystem/src/Utils.cpp \
    socs/src/socs/opencl/Convolution.cpp \
    socs/src/socs/opencl/OpenCL.cpp \
    socs/src/socs/socket/Socket.cpp \
    socs/src/socs/App.cpp \
    socs/src/socs/Exception.cpp \
    socs/src/socs/padding.cpp \
    socs/src/main.cpp \
    socs/test/socs/opencl/Aligned_array_test.cpp \
    socs/test/socs/opencl/OpenCL_test.cpp \
    socs/test/socs/socket/Socket_test.cpp \
    socs/test/socs/Hello_world_test.cpp \
    control_section.cpp \
    image_section.cpp \
    main.cpp \
    mainwindow.cpp \
    platform_mode_section.cpp \
    welcomewindow.cpp

