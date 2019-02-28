#pragma once

namespace hepics {

#if defined(USER_ANDRES)
struct Paths {
	static constexpr auto class_name_file = "/home/andres/git/caffe/data/ilsvrc12/synset_words.txt";
};
#elif defined(USER_MEHYAR)
struct Paths {
	static constexpr auto class_name_file = "";
};
#else
#error unknown user
#endif

}

