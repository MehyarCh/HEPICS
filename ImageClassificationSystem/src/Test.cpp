/*
 * Test.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: ibrahim
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Image.h"

/*
void test_convolve()
{
    Image *dog = new Image(1,1,1);
    *dog = dog->load_image("/home/ibrahim/localRepository/HePICS/hepics/test/src/dog.jpg");
    //show_image_layers(dog, "Dog");
    printf("dog channels %d\n", dog->channels);
    Image *kernel = new Image(1,1,1);
    kernel = kernel->make_random_image(3,3,dog->channels);
    Image edge = Image(dog->height, dog->width, 1);
    int i;
    clock_t start = clock(), end;
    for(i = 0; i < 1000; ++i){
        dog->convolve(kernel, 1, 0, edge);
    }
    end = clock();
    printf("Convolutions: %lf seconds\n", (double)(end-start)/CLOCKS_PER_SEC);
    //show_image_layers(edge, "Test Convolve");
}

void test_load() {
	char buffer[100] = "/home/ibrahim/localRepository/HePICS/hepics/test/src/dog.jpg";
	char *path = buffer;
	Image dog = Image::load_image(path, 1280, 720, 3);
}
*/

int main(int argc, char **argv)
{
    //test_resize("data/bad.jpg");
    //test_box();
    //test_convolutional_layer();
	/*
    if(argc < 2){
        fprintf(stderr, "usage: %s <function>\n", argv[0]);
        return 0;
    }
    */

    /*
     *     if (0 == strcmp(argv[1], "classifier")){
    		run_classifier(argc, argv);
    	   }
     */

    test_convolve();

}

