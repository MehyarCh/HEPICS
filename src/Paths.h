#pragma once

namespace hepics {

#if defined(USER_ANDRES)
struct Paths {
	static constexpr auto class_name_file = "/home/andres/git/caffe/data/ilsvrc12/synset_words.txt";
	static constexpr auto caffemodel = "/home/andres/Downloads/bvlc_alexnet.caffemodel";
	static constexpr auto mean_file = "/home/andres/git/caffe/data/ilsvrc12/imagenet_mean.binaryproto";
};
#elif defined(USER_MEHYAR)
struct Paths {
	static constexpr auto class_name_file = "";
	static constexpr auto caffemodel = "/home/mehyar/localRepository/hepics/new_hepics/cfg/bvlc_alexnet.caffemodel";
	static constexpr auto mean_file = "";
};
#else
#error unknown user
#endif

}

