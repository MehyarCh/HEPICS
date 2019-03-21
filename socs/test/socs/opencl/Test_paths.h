#pragma once
#include <string>
namespace socs {

#if defined(USER_ANDRES)
struct Test_paths {
	static constexpr auto layer_dumps = "/home/andres/test_data/layer_dumps/";
};
#else
struct Test_paths {
	static constexpr auto layer_dumps = "";
};
#endif

}

