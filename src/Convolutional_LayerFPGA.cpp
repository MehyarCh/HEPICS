#include "Convolutional_LayerFPGA.h"

namespace hepics {

Convolutional_LayerFPGA::Convolutional_LayerFPGA() : type {"convolutional"} {
	// TODO Auto-generated constructor stub

}
unique_ptr<Image> Convolutional_LayerFPGA::forward_layer(const Image &input){
	return 0;
}
string Convolutional_LayerFPGA::get_type(){
	return type;
}

} // namespace hepics
