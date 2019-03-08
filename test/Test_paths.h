#pragma once
#include <string>
namespace hepics {

#if defined(USER_ANDRES)
struct Test_paths {
	static constexpr auto socker_ball_image = "/home/andres/test_data/images/256x256x3/soccer_ball01.png";
	static constexpr auto socker_ball_image_dump = "/home/andres/test_data/loaded_image.dump";
	static constexpr auto alexnet_caffemodel = "/home/andres/Downloads/bvlc_alexnet.caffemodel";
	static constexpr auto dog = "/home/andres/git/hepics/test/Pictures/dog.jpeg";
	static constexpr auto lion = "/home/andres/git/hepics/test/Pictures/lion.jpeg";
	static constexpr auto layer_dumps = "/home/andres/test_data/layer_dumps/";
};
#elif defined(USER_MEHYAR)
struct Test_paths {
	static constexpr auto socker_ball_image = "";
	static constexpr auto socker_ball_image_dump = "/home/andres/test_images/256x256x3/soccer_ball01.png";
	static constexpr auto alexnet_caffemodel = "/home/mehyar/localRepository/hepics/new_hepics/cfg/bvlc_alexnet.caffemodel";
	static constexpr auto class_name_file = "";
	static constexpr auto caffemodel = "/home/mehyar/localRepository/hepics/new_hepics/cfg/bvlc_alexnet.caffemodel";
	static constexpr auto mean_file = "";
};
#else
#error unknown user
#endif

namespace path {
//constexpr auto dog= "/home/mehyar/localRepository/hepics/new_hepics/test/Pictures/dog.jpeg";
//constexpr auto lion= "/home/mehyar/localRepository/hepics/new_hepics/test/Pictures/lion.jpeg";
//constexpr auto classnames = "/home/mehyar/localRepository/hepics/HepicsModel/test/Classname/classnames.txt";

//constexpr auto dog= "/home/andres/git/hepics/test/Pictures/dog.jpeg";
//constexpr auto lion= "/home/andres/git/hepics/test/Pictures/lion.jpeg";

}
}

