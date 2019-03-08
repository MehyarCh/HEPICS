#include "hepics/Paths.h"
#include "hepics/DataSaver.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace hepics;
using namespace std;

DataSaver* save;

void test_add_result(int i, unique_ptr<Result>& r){
	save->set_result(i, move(r));
}

TEST(add_result, test_add_result){
	Image* dog= new Image(227,227,3,1);
	DataSaver* data = new DataSaver();
	auto r = make_unique<Result>();
	r->save_result("lion", 90.66);
	r->save_result("dog", 95.4);
	r->save_result("cat", 92.00);
	data->set_result(dog->id, move(r));
}
TEST(delete_result, test_delete_result){
	ASSERT_EQ(0,0);
}
TEST(set_result, test_set_result){
	ASSERT_EQ(0,0);
}
TEST(get_result, test_get_result){
	ASSERT_EQ(0,0);
}
TEST(write_result, test_write_result){
	ASSERT_EQ(0,0);
}
TEST(aggregate, test_aggregate){
	ASSERT_EQ(0,0);
}
