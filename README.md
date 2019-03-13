# HePICS : Heterogeneous Platform for Image an Classification System
An Image classification system deploys artificial intelligence, particularly artificial neural networks, in order to be able to process images and cite the objects that are displayed on it.

___________________________________________________________________
# Motivation :
In the frame of the software engineering practise at the Karlsruhe Institute Of Technology, we have been assigned the task of implementing an image classification system based on the AlexNet neural network model.

___________________________________________________________________
# Build status :
The last step was the integration of the back- and frontend. The classification runs for the moment on the CPU, but can be extended to run on a GPU and an FPGA for an optimization.
The program is currently in a stable status.

___________________________________________________________________
# Code Style :
Overall the code style is standard.

___________________________________________________________________
# Tech/Framework used :
## Frontend : 
The gui has been developed on the QtCreator tool. It has been later exported to eclipse to be joined with the backend.
## Backend : 
The project has been built on eclipse IDE on Ubuntu.
Caffe has been integrated to provide a parser for the config files.
The following libraries have been used and must be installed for the program to correctly run.
- Qt5Gui
- Qt5Widgets
- Qt5Core
- protobuf

___________________________________________________________________
# Installation :
This is a step-by-step installation to deploy the software on a user's machine.
An Ubuntu version 16.04 environment is necessary.


1. install the protoc library through running the following command in the console
- sudo apt-get install libprotobuf-dev
2. install Qt5 libraries through running the following commands in the console
- sudo apt-get install build-essential
- sudo apt-get install qtcreator
- sudo apt-get install qt5-default
3. change the directory to the "HePICS" installation folder and run
- make all 
4. run 
- sudo make install
5. run 
- HePICS 
___________________________________________________________________
# API Reference :
- [QT5](https://doc.qt.io/qt-5/classes.html)
- [caffe](http://caffe.berkeleyvision.org/)
- [Googletest](https://github.com/google/googletest)

___________________________________________________________________
# How to use?
The GUI is user friendly. A normal classification runs as follows :
1. run the software
2. click on the start button on the welcome window
3. click the add button, choose one/multiple image(s)
4. you can select the images you do not wish to classify and delete them
5. choose the platforms you want to enable
6. choose the operation mode
7. click the start button
8. wait for the progress bar to reach 100% then select the image to display its results
9. click the aggregate button to calculate an aggregation of the classified images' results.

___________________________________________________________________
# Credits :
Karlsruhe Institute of Technology, practise of software engineering.
Andres Stober, Linjuan Fan, Baha Mhaagne, Ibrahim Bouriga, Mehyar Cherni
under the supervision of Dennis Weller, Sarath Mohanachandran Nair.
