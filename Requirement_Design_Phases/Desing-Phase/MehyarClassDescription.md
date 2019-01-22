Class-Image :
is an abstract class which represents the modelisation of an image in the programming language. Its attributes are length, width, channel, and id, which means each uploaded or created image is unique. This class is only a representation of an image object, it can be replaced by an existing library.
	Attributes:
		-length: is the length of the image object
		-width: is the width of the image object
		-channel: number of channels of the image, by default set to 3 (Red, Green, Blue)
		-id: is a unique number for each image, used to identify them and differentiate them from each other.
	Methods:
		-getLength(): returns the length of the image	
		-setLength(length:int): sets the value of the image's length	
		-getWidth(): returns the width of the image
		-setWidth(width:int): sets the valye of the image's width
		-getChannel(): returns the number of channels the image has
		-setChannel(channel:int): sets the number of channels of the image
		-resize(length : int, width : int): changes the size of the image to the new dimensions


Class-InputImage : 
represents an input image. Has an extra attribute isClassified, which tells if the image has already been classified. In this case, it is not necessary to redo the classification. It is also possible to create a thumbnail out of this image.
	Attributes: 
		- isClassified : a boolean which tells if the image has already been classified. True : display results without classifying, false : start a normal classification process.
	Methods:
		- createThumbnail() : creates a thumbnail of the input image and returns it as an image. A thumbnail is a smaller representation of the image itself.
		- setStatus( b : boolean) : changes the status of the image to classified or non classified.
		- getStatus() : returns the status of the image : classified/true, not classified/false


Class-ResultImage : represents the image that is displayed which contains the results of the classification. It has an extra attribute called result, which is a string containing the results. These results can also be displayed in other ways if it is wished to extend the functionality of the system (histograms, pie charts)
	Attributes:
		- result : a string which contains the results of the classification of an image in percentages.
	Methods:
		- getResult() : returns the string containing the results of the classification.
		- setResult( results: String) : sets the results of a classification
		- createResult() : draws the results of a classification contained in the string on an image and returns it. This method can be later modified in such way that results would be displayed in a better way.

Class-ImageManager : is responsible of providing the input image to the system and its preprocessing, which means, converting it into a matrix, or an RGB image, depending on what the process needs.
	Attributes:
		- input  : is the image object representation of the input image.
		- inputPath : is a String which contains the path to the input image
	Methods:
		- getPath() : returns a string containing the path to the input image
		- setPath( path : String) : sets the path of the input image
		- loadInput(path  : String ) : loads the input image from its path and returns it
		- convertRGB(input : Image, length : int, width : int, channel : int) : returns an RGB image of the input image for the sake of the classification.
		- preProcessImage : returns the image in the form of a matrix for the sake of the classification.
		- getImage() : returns the input image.

Class-DataSaver : is practically the data holder. It saves the input images loaded during the time the system has been running in a hashmap. Can also write the results in a text file, and aggregate the results of the given inputs. Aggregating results means in this case calculating the average
	Attributes:
		-results : is a hashmap whose key is the id of the images, and value is the results of the classification of the corresponding image.
	Methods:
		- addResult( input : InputImage, result :  ResultImage) : adds the result of the classification of an input image
		- setResult( input : InputImage, result : ResultImage) : sets the result of the classification of an input image
		- getResult( input : InputImage) : returns the result of the classification of an input image 
		- aggregate() : aggregates the results of the last classification process, if there are multiple inputs  
		- writeFile( id : int) : writes the results of the corresponding input image to a text file 


Class-ClassificationAssistant : is practically the classifier's secretary. It makes sure that the classifier gets all what it needs to run the classification. It loads weights, sets the input image in the wished form, and loads all the neural networks needed specifications, as well as the classification's class names.
Input images get transfered one by one through the assistant.
	Attributes:
		- inputImage : is the input image
		- weightFilePath : is a String containing the path to the weights file.
		- weights : is an array of double containing the weights of the neural network
		- classNamesPath : is a string containing the path to the class names file. These are the objects to be identified during the classification.
		- isClassified() : is a boolean which tells if the currently loaded input image is classified. By default, it is set on false.
		- manager : is an instance of the class ImageManager. It is responsible for the necessary preprocessing of the input image.
	Methods:
		- getNeuralNetwork() : returns the currently established neural network
		- setNeuralNetwork( nn : NeuralNetwork) : sets the currently established neural network
		- getInputImage() : returns the currently loaded input image
		- setWeights( weights : Array of double) : sets the array of weights through a new one
		- getWeights() : returns an array of double which contains the weights of the neural network
		- loadClassNames() : returns an array of string containing the class names.
		- getClassNamesPath() : returns a string containing the path to the class names file
		- setClassNamesPath( path : String ) : sets the path to the class names file

Class-NeuralNetwork : is the modelisation of a neural network. A neural network has a name, a topology and a set of layers.
	Attributes:
		- name : a string containing the name of the neural network
		- topology : an instance of the class topology. It is a characteristic of the neural network
		- layers : is an array of layers that build the neural network
	Methods:
		- getName() : returns the name of the neural network
		- setName( name : String) : sets the name of the neural network
		- getTopology() : returns the topology object of the neural network
		- setTopology( topology : Topology) : sets the topology of the neural network through a new one
		- addLayer( type : LayerType) : adds a layer to the list of layers of the neural network
		- forwardPropagation ( inputImage : Image) : returns a matrix of floats that represent the build through the classification.


Class-Shape : contains constants which define the dimensions, which means the form and general composition of a layer represented as a matrix.
	Attributes:
		- rows : the number of rows of the layer and the first dimension of the matrix
		- cols : the number of columns of the layer and the second dimension of the matrix
		- channels : the number of channels of the layer and the third dimension of the matrix
	Methods:
		- getRow() : returns the number of rows of the layer
		- getCols() : returns the number of columns of the layer
		- getChannels() : returns the number of channels of the layer


Class-Topology : is the visual representation of the neural network, meaning the layers and the relations or interactions between them.
	Attributes:
		- displayer : is an instance of the class TopologyDisplayer.
	Methods:
		- display() : displays the topology of the neural network.

Class-TopologyDisplayer : is a tool which is responsible for drawing the representation of the topology and generating an image.
	Attributes:
		- layers : is a list of the layers that constitute the neural network
		- display : is an image on which the topology is drawn
	Methods:
		- drawTopology() : draws the topology on an image and returns it
		- getDisplay() : returns the image to display


Class-Layer : is what a neural network is made of. It is a set of nodes placed on each other which each treat the input image depending on their type and activation function.
	Attributes:
		- type : is an enumeration called LayerType. It defines the type of the layer, and on that note, the way it handles the treatment of the data it receives.
	Methods:
		- getType() : returns the type of the layer.
		- setType( type : LayerType) : sets the type of the layer
		- getInputShape() : returns the shape of the input
		- setInputShape() : sets the shape of the input
		- getOutputShape() : returns the output's shape
		- setOutputShape() : sets the shape ouf the ouput
		- forwardPropagation(inputImage : Image) consists of processing the data of the input image through one layer, it returns a matrix of float values
Enumeration Class-LayerType : is an enumeration class of the possible layer types. Each type defines how the layer treats the data it receives and how it gives it over to the next one.
	-InputLayer
	-ConvolutionalLayer
	-MaxPoolLayer
	-ResponseNormalizationLayer
	-DenseLayer
	-FullyConnectedLayer
