#ifndef NEURAL_NETWORK
#define NEURAL_NETWORK
typedef unsigned char LABEL_TYPE;
#include "forward_layer.h"

class neural_network
{
		protected:
				int layer_num;
				int last_layer;
				int N_out;
				int N_in;
				W_TYPE * delta_in0;
				LABEL_TYPE correct_label;
		public:
				forward_layer ** layers;
				neural_network(int input_size,int output_size);
				~neural_network();
				
				//interface to sgd_learning class
				void set_sample(LAYER_IN_TYPE * sample_in,LABEL_TYPE answer);
				void train_sample();
				bool predict_sample();

				//assistive function
				void scalar_time(double scalar);
				void profile_time();
				void clear_time_count();
				void adjust_WB();
				void scalar_dWB(W_TYPE scalar);
				void clean_dWB();
				void forward();
				void backward();
};
#endif
