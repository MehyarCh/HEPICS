In this diagram seveal design patterns were used.
In order to decouple  major components and allow parallel development we use the Model-View-Controller as a global architecture.
The class diagram consists of several common patterns to reduce complexity and dependencies between classes.
We use the template Method as pattern for sections to define the skeleton of the algorithm in an operation.
However the results and states are updated using an observer which define a one-to-many dependency between objects.
Different Modes as well as Worker are represented by simple is-relationships.
Another interesting pattern to be used by layers is the strategy-pattern. In this context we define a family of algorithm, encapsulate
each one and make them interchangeable.This approach also lets the algoritm vary independently from the layer that use it.
