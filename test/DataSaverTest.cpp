#include "Paths.h"
#include "DataSaver.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace hepics;
using namespace std;

DataSaver* save;

void test_add_result(Image im, Result r){
	save->add_result(im, r);
}
void test_delete_result(){

}
TEST(add_result, test_add_result){
	Result result;
	Image dog= new Image(227,227,3);
	dog.load_image(path::dog);
}
