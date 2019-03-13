#pragma once

namespace hepics {

#if defined(USER_ANDRES)
struct Paths {
	static constexpr auto class_name_file = "/home/andres/git/caffe/data/ilsvrc12/synset_words.txt";
	static constexpr auto caffemodel = "/home/andres/Downloads/bvlc_alexnet.caffemodel";
	static constexpr auto mean_file = "/home/andres/git/caffe/data/ilsvrc12/imagenet_mean.binaryproto";
	static constexpr auto welcome_image = "/home/andres/test_data/images/dog01.png";
};
#elif defined(USER_MEHYAR)
struct Paths {
	static constexpr auto class_name_file = "";
	static constexpr auto caffemodel = "/home/mehyar/localRepository/hepics/new_hepics/cfg/bvlc_alexnet.caffemodel";
	static constexpr auto mean_file = "";
	static constexpr auto welcome_image = "/home/mehyar/Pictures/welcome.jpg";
};
#elif defined(USER_IBRAHIM)
struct Paths {
	static constexpr auto class_name_file = "/home/ibrahim/Caffe/synset_words.txt";
	static constexpr auto caffemodel = "/home/ibrahim/Caffe/bvlc_alexnet.caffemodel";
	static constexpr auto mean_file = "/home/ibrahim/Caffe/imagenet_mean.binaryproto";
	static constexpr auto welcome_image = "/home/ibrahim/Caffe/welcome_image.jpeg";
};
#else
struct Paths {
	static constexpr auto class_name_file = "/opt/hepics/synset_words.txt";
	static constexpr auto caffemodel = "/opt/hepics/bvlc_alexnet.caffemodel";
	static constexpr auto mean_file = "/opt/hepics/imagenet_mean.binaryproto";
	static constexpr auto welcome_image = "/opt/hepics/welcome_image.jpeg";
};
#endif

}

