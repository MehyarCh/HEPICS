#include "Convolutional_LayerFPGA.h"

namespace hepics {

Convolutional_LayerFPGA::Convolutional_LayerFPGA() {
	// TODO Auto-generated constructor stub

}
unique_ptr<Image> Convolutional_LayerFPGA::forward_layer(const Image &input){
	return 0;
}
Layer::Type Convolutional_LayerFPGA::get_type(){
	return Type::convolutional;
}

} // namespace hepics
