Sigmoid function: g(z) = 1 / (1 + e^{-z}). It’s used on the output layer so that we can easily interpret the output as probabilities since it has restricted output between 0 and 1. 

Tanh function: g(z) = (e^z -e^{-z}) / (e^z + e^{-z}). It’s superior to sigmoid function in which the mean of its output is very close to zero, which in other words center the output of the activation units around zero and make the range of values very small which means faster.

ReLU function: g(z) = max{0, z}. The models that are close to linear are easy to optimize. Since ReLU shares a lot of the properties of linear functions, it tends to work well on most of the problems. 

Softmax function: It generates a value between 0–1 for each node (the sum of all these softmax values is equal to 1). We can interpret the softmax values for a given image as relative measurements of how likely it is that the image falls into each target class.
