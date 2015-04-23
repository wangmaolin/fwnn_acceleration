#ifndef FORWARD_LAYERB
#define FORWARD_LAYERB
#include<string>

typedef float W_TYPE;
typedef float B_TYPE;

typedef float LAYER_OUT_TYPE;
typedef float LAYER_IN_TYPE;

using namespace std;

class forward_layer
{
		protected:
				W_TYPE * W;
				W_TYPE * dW;
				B_TYPE * B;
				B_TYPE * dB;

				W_TYPE * Sum;
				LAYER_IN_TYPE * in;
				LAYER_IN_TYPE * delta_in;

				int N_in;
				int N_out;
				//initial W and B size in the consturctor of sub class
				int W_size;
				int B_size;
		public:
				double forward_time;
				double backward_time;	
				void clear_time_count();
				void profile_time();
				void scalar_time(double scalar);
				const string name;
				LAYER_OUT_TYPE * out;
				LAYER_OUT_TYPE * delta_out;

				//construct and destruct
				forward_layer(const char * layer_name,int input_size,int output_size);
				~forward_layer();

				void set_in(LAYER_IN_TYPE * in_p);
				void set_delta_in(LAYER_OUT_TYPE * in_p);
				LAYER_OUT_TYPE get_out(int out_index);

				//scan W and B function
				void adjust_WB();
				void scalar_dWB(W_TYPE scalar);
				void clean_dWB();
				void display_W(int number);
				void display_dW(int number);
				void display_out(int number);
				void display_delta_out(int number);

				//interface to neural network class
				virtual void alloc_parameter()=0;
				virtual void initial_parameter()=0;
				virtual void forward()=0;
				virtual void backward()=0;
				
};
#endif
