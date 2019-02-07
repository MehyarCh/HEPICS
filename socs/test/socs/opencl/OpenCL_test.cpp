#include <gtest/gtest.h>
#include <memory>

#include "../../../src/socs/opencl/OpenCL.h"

using namespace std;
using namespace socs::opencl;

#include <iostream>

TEST(opencl_context_test, create) {
	auto p = Platform { [](const string &) {return true;} };
	auto d = Device { [](const string &) {return true;}, p };
	auto c = make_unique<Context>(p, d);
	ASSERT_NE(c->context, nullptr);
}
