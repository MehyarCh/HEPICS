# 1. Preface elements
Scope : Image classification system; Level : User Goal
Primary Actor : External system.

# 2. Stakeholders and Interest List
External system : wants the classification of an image through sending one single request, and needs the result in a clear form, without any errors. Receives then the results through ethernet.
User of the external system : sends a request through the external system and awaits for the correct and clear results of his request. 

# 3. Preconditions
A classification request is given by the external system through sending an input image. It is then detected by the image classification system which loads the image and starts classifying it. The classification should run smoothly and be finished.

# 4. Post conditions (Success Guarantees)
The sent input image is correctly classified. The results are saved into a file. The file is sent to the external system.

# 5. Main Success Scenario
1. User sends an input image through the external system.
2. Image classification system detects the classification request.
3. System loads the input image.
4. System starts the classification.
5. System shows results.
6. System saves results into a file.
7. External system reads file.

# 6. Extensions (a.k.a alternative flows)
* a. At any time system fails :
   1. System restarts, signals error to the external system, records the error, and enters a clean state.
   2. System loads in input image and restarts classification.
2a. Invalid input image :
  1. System signals the invalid input and rejects it.
6a. Saving failed :
  1. System signals fail.
  2. System retries saving file.
  
# 7. Special requirements
- Ethernet connection between the system and the external system to allow file sharing.
- System runs per default on high-efficiency mode.
# 8. Technology and Data variations
- Results are saved into a text-file.
