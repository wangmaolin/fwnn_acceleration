#ifndef HIDDEN_LAYER
#define HIDDEN_LAYER

#include "full_connect_layer.h"
class hidden_layer :public full_connect_layer
{
		public:
				void initial_parameter();
				void forward();
				void backward();
				hidden_layer(const char * layer_name,int input_size,int output_size);
};
#endif
