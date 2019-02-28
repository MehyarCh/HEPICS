#include "Paths.h"
#include "Result.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace hepics;
using namespace std;

TEST(save_result, test_save_result){
	Result* r = new Result();
	r->save_result("dog", 90);
	ASSERT_EQ(r->get_results()[0].first, "dog");
	ASSERT_EQ(r->get_results()[0].second, 90);
}
TEST(save_mult_results, test_save_result){
	Result* r = new Result();
	r->save_result("dog", 90);
	r->save_result("lion", 95);
	r->save_result("cat", 92);

	ASSERT_EQ(r->get_results()[0].first, "lion");
	ASSERT_EQ(r->get_results()[0].second, 95);
	ASSERT_EQ(r->get_results()[1].first, "cat");
	ASSERT_EQ(r->get_results()[1].second, 92);
	ASSERT_EQ(r->get_results()[2].first, "dog");
	ASSERT_EQ(r->get_results()[2].second, 90);
}
TEST(to_string, test_to_string){
	Result* r = new Result();
	r->save_result("dog", 90);
	r->save_result("lion", 95);
	r->save_result("cat", 92);
	string results = "lion: 95.000000\ncat: 92.000000\ndog: 90.000000\n";
	ASSERT_EQ(r->toString(), results);
}
