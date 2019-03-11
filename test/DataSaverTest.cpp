#include "Test_paths.h"
#include "hepics/DataSaver.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace hepics;
using namespace std;

DataSaver* save;

TEST(add_result, test_add_result){
	Image* dog= new Image(227,227,3,1);
	DataSaver* data = new DataSaver();
	auto r = make_unique<Result>();
	r->save_result("lion", 90);
	r->save_result("dog", 95);
	r->save_result("cat", 92.00);
	data->set_result(dog->id, move(r));
	string results = "dog: 95.000000\ncat: 92.000000\nlion: 90.000000\n";
	ASSERT_EQ(data->get_result(dog->id)->toString(), results);
}
TEST(delete_result, test_delete_result){
	Image* dog= new Image(227,227,3,1);
	DataSaver* data = new DataSaver();
	auto r = make_unique<Result>();
	r->save_result("lion", 90.66);
	data->set_result(dog->id, move(r));
	data->delete_result(dog->id);
	ASSERT_EQ(data->get_map().size(),0);
}

TEST(write_result, test_write_result){
	Image* dog= new Image(227,227,3,1);
	DataSaver* data = new DataSaver();
	auto r = make_unique<Result>();
	r->save_result("lion", 90.66);
	data->set_result(dog->id, move(r));
	data->write_result_in_file(dog->id);
	std::ifstream infile(Test_paths::resultpath);
	bool exist = infile.good();
	ASSERT_EQ(exist,true);
}
TEST(aggregate, test_aggregate){
	Image* i1= new Image(227,227,3,1);
	Image* i2=new Image(227,227,3,1);
	Image* i3=new Image(227,227,3,1);
	auto r1= make_unique<Result>();
	auto r2= make_unique<Result>();
	auto r3= make_unique<Result>();
	DataSaver* save = new DataSaver();
	r1->save_result("dog",90);
	r1->save_result("cat",50);
	r1->save_result("truck",20);
	save->set_result(i1->id,move(r1));
	r2->save_result("dog", 80);
	r2->save_result("truck",60);
	r2->save_result("cat", 10);
	save->set_result(i2->id,move(r2));
	r3->save_result("dog", 70);
	r3->save_result("fish", 15);
	r3->save_result("truck", 10);
	save->set_result(i3->id,move(r3));
	auto final= save->aggregate();
	string results = "dog: 80.000000\ntruck: 30.000000\ncat: 20.000000\nfish: 5.000000\n";
	ASSERT_EQ(final.toString(),results);
}
