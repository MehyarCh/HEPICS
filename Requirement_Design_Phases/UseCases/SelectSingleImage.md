# 1. Preface elements
Scope : Image Classification System  ; Level : User Goal.
Primary Actor : User.

# 2. Stakeholders and Interest List
User : wants the classification of an image through selecting one single image as an input, and needs the result showed in a clear form, without any errors.

# 3. Preconditions
The system is started, the welcome screen is showed, the main window loads correctly.

# 4. Post conditions (Success Guarantees)
The input image is correctly selected. The thumbnail of the image is showed on the screen with the possibility of removing it. The start button is active and the classification can be started.

# 5. Main Success Scenario
  1. User starts the program.
  2. Welcome screen is displayed.
  3. User clicks on the "start" button.
  4. Main window is displayed.
  5. User clicks on a "add image..." button.
  6. User selects an image.
  7. System loads image file.
  8. Selected image's thumbnail is displayed and start button is activated.

# 6. Extensions (a.k.a alternative flows)
  * a. At any time system fails :
    1. System signals error to the user, records the error and enters a clean state. 
    2. System reloads the main window.
  6a. Invalid input image :
    1. System signals the invalid input and rejects it.
    2. User selects a new input image, or cancels the selection.
    
# 7. Technology and Data variations
- Only image files are accepted as input.
