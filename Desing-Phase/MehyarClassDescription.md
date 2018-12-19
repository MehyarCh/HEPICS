Image : is an abstract class which represents the modelisation of an image in the programming language. Its attributes are length, width, channel, and id, which means each uploaded or created image is unique. This class is only a representation of an image object, it can be replaced by an existing library.

InputImage : represents an input image. Has an extra attribute isClassified, which tells if the image has already been classified. In this case, it is not necessary to redo the classification. It is also possible to create a thumbnail out of this image.

ResultImage : represents the image that is displayed which contains the results of the classification. It has an extra attribute called result, which is a string containing the results. These results can also be displayed in other ways if it is wished to extend the functionality of the system (histograms, pie charts)

ImageManager : is responsible of providing the input image to the system and its preprocessing, which means, converting it into a matrix, or an RGB image, depending on what the process needs.

DataSaver : saves the input images loaded during all the time the system has been running in a hashmap. Can also write the results in a text file, and aggregate the results of the given inputs.

ClassificationAssistant : is practically the classifier's secretary. It makes sure that the classifier gets all what it needs to run the classification. It loads weights, sets the input image in the wished form, and loads all the neural networks needed specifications, as well as the classification's class names.

NeuralNetwork : is the modelisation of a neural network. A neurel network has a name, a topology and a set of layers.

Shape : contains constants which define the form and general composition of a layer.

Topology : is the visual representation of the neural network, meaning the layers and the relations or interactions between them.

TopologyDisplayer : is a tool which is responsible of drawing the representation of the topology and generating an image.

Layer : is what a neural network is made of. It is a set of nodes placed on each other which each treat the input image depending on their type and activation function.

LayerType : is an enumeration class of the possible layer types.
