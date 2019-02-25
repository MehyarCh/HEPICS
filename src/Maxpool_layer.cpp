#include "Maxpool_layer.h"

namespace hepics {

Maxpool_layer::Maxpool_layer(){
	// TODO Auto-generated constructor stub

}

Maxpool_layer::~Maxpool_layer() {
	// TODO Auto-generated destructor stub
}
unique_ptr<Image> Maxpool_layer::forward_layer(hepics::Image const&){
	return 0;
}
Layer::Type Maxpool_layer::get_type(){
	return Type::maxpool;
}

} // namespace hepics
