#pragma once

namespace hepics {

#if defined(USER_ANDRES)
struct Paths {
	static constexpr auto class_name_file = "/home/andres/git/caffe/data/ilsvrc12/synset_words.txt";
	static constexpr auto path = "";
};
#elif defined(USER_MEHYAR)
struct Paths {
	static constexpr auto class_name_file = "/home/mehyar/localRepository/hepics/new_hepics/files/synset_words.txt";
	static constexpr auto path = "/home/mehyar/cfg/bvlc_alexnet.caffemodel";
};
#else
#error unknown user
#endif

}

