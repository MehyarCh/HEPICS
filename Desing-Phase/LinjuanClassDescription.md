InputLayer Class: This class inherits the abstract Layer class. It is the first layer of a neural network model, which contains the input shape of an input image as its attribute.

Abstract ConvolutionalLayer Class: This class modifies the convolutional layers, which applies a specified number of convolution filters to the image. For each subregion, the layer performs a set of mathematical operations to produce a single value in the output feature map. 
The filters attribute specifies the number of filters to apply, kernel_size specifies the dimensions of the filters and strides specifies the strides of the convolution along the height and width.

CPUConvolutionalLayer Class: This class inherits the abstract ConvolutionalLayer Class. Its computation would be executed on the CPU. 

FPGAConvolutionalLayer Class: This class inherits the abstract ConvolutionalLayer Class. Its computation would be executed on the FPGA. 

MaxPoolLayer Class: This class modifies the maxpool layer, which downsample the image data extracted by the convolutional layers to reduce the dimensionality of the feature map in order to decrease processing time. It uses max pooling as its pooling algorithms, which extracts subregions of the feature map (e.g., 2x2-pixel tiles), keeps their maximum value, and discards all other values.
The pool_size attribute specifies the size of the max pooling filter as [height, width]. If both dimensions have the same value, you can instead specify a single integer and the strides specifies the size of the stride.

ResponseNormalizationLayer Class: This class modifies the response normalization layer, which normalizes the activations of the previous layer at each batch, i.e. applies a transformation that maintains the mean activation close to 0 and the activation standard deviation close to 1.
The axis attribute specifies the axis that should be normalized (typically the features axis).

DenseLayer Class: This class modifies the dense layer, which performs classification on the features extracted by the convolutional layers and downsampled by the pooling layers. In a dense layer, every node in the layer is connected to every node in the preceding layer.
The units attribute specifies the number of neurons in the dense layer.

TrainableLayer Class: This class modifies the layer whose trainable parameters (e.g. weights) can be optimized and updated by the training algorithms (like back-propagation).
The weight attribute specifies the weights of this layer and use_bias specifies whether the layer uses a bias vector.
The getWeight method returns the weights of the layer as a matrix and setWeight method sets the weights of the layer from a matrix (with the same shapes as the output of getWeight).

All the layer implements the forward propagation method in order to use the pre-trained parameters to get the output. 

ActivationFunction Class: This abstract class encapsulates the activation function whose purpose is to allow small changes in the weights or bias to only cause a small change on the output, this property is helpful when training a network.
The name attribute specifies the name of the activation function.
The activate method specifies the function that would be applied.

Sigmoid Class: This class encapsulates an activation function called Sigmoid. Its method activate implements the function: g(z) = 1 / (1 + e^{-z}). It’s used on the output layer so that we can easily interpret the output as probabilities since it has restricted output between 0 and 1.

Tanh Class: This class encapsulates an activation function called Tanh. Its method activate implements the function: g(z) = (e^z -e^{-z}) / (e^z + e^{-z}). It’s superior to sigmoid function in which the mean of its output is very close to zero, which in other words center the output of the activation units around zero and make the range of values very small which means faster.

ReLU Class: This class encapsulates an activation function called ReLU. Its method activate implements the function: g(z) = max{0, z}. The models that are close to linear are easy to optimize. Since ReLU shares a lot of the properties of linear functions, it tends to work well on most of the problems.

Softmax Class: This class encapsulates an activation function called Softmax. Its method activate generates a value between 0–1 for each node (the sum of all these softmax values is equal to 1). We can interpret the softmax values for a given image as relative measurements of how likely it is that the image falls into each target class.
