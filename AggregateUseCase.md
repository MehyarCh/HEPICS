Use Case : Aggregate results

Preface elements :
Scope: Image classification system; Level : User Goal; 
Primary actor : User

Stakeholders and Interest List:
User: wants the result of the classification of multiple images he selects. This result is an aggregation of the results of each image. 

Preconditions:
The selection of up to 5 images runs correctly. The classification of each image is correctly executed. 

Post conditions (Success Guarantees)
The results of each image are aggregated creating a new result. This new result is displayed on the main window.

Main Success Scenario
1. User starts program.
2. User adds one image.
3. User adds more images.
4. System starts the classification.
5. System starts the aggregation.
6. System shows the aggregation results.

Extensions (a.k.a alternative flows)
* a. At any time system fails :
    1. System signals error to the user, restarts, records the error, and enters a clean state.
    2. System loads in input images and restarts classification.
2-3a. Invalid input image :
    1. System signals the invalid input and rejects it.
