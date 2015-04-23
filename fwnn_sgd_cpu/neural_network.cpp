#include "neural_network.h"
#include "log_reg_layer.h"
#include "hidden_layer.h"
#include "maxpool_layer.h"
#include "conv_layer.h"
#include <time.h>
#include <iostream>
#include <stdio.h>
using namespace std;
neural_network::neural_network(int input_size,int output_size)
{
		cout<<"constuct neural network"<<endl;

		layer_num=6;

		N_in=input_size;
		N_out=output_size;

		delta_in0=new W_TYPE[N_out];
		last_layer=layer_num-1;
		layers =new forward_layer *[layer_num];
		layers[5]=new log_reg_layer("log regression", 500,N_out);
		layers[4]=new hidden_layer("hidden",800,500);
		layers[3]=new maxpool_layer("max pool 2",3200,800);
		layers[2]=new conv_layer("conv 2",20,12,50,8,5);
		layers[1]=new maxpool_layer("max pool 1",11520,2880);
		layers[0]=new conv_layer("conv 1",1,28,20,24,5);
		//construct network
		//backward path
		layers[last_layer]->set_delta_in(delta_in0);
		for(int i=0;i<last_layer;i++)
		{
				layers[i]->set_delta_in(layers[i+1]->delta_out);
		}
		//forward path
		for(int i=0;i<last_layer;i++)
		{
				layers[i+1]->set_in(layers[i]->out);
		}
}

neural_network::~neural_network()
{
		delete []layers;
		cout<<"destuct neural network"<<endl;
}

void neural_network::set_sample(LAYER_IN_TYPE * sample_in,LABEL_TYPE answer)
{
		layers[0]->set_in(sample_in);
		correct_label=answer;
}

bool neural_network::predict_sample()
{
	LABEL_TYPE max=0;	
	forward();
	for(int i=1;i<N_out;i++)
	{
			if(layers[last_layer]->get_out(i)>layers[last_layer]->get_out(max))
			{
					max=i;
			}
	}
	
	return correct_label==max;
}

void neural_network::train_sample()
{
		int start,end;
		start=clock();
		//cout<<"forward: ";
		//fflush(stdout);
		forward();
		end=clock();
	//	cout<<"forward  time is "<<1.0*(end-start)/CLOCKS_PER_SEC<<" s"<<endl;
		//cout<<"prepare ";
		//fflush(stdout);
		start=clock();
		for(int k=0;k<N_out;k++)
		{
				if(k==correct_label)
				{
						delta_in0[k]=-(1-layers[last_layer]->get_out(k));
				}	
				else
				{
						delta_in0[k]=layers[last_layer]->get_out(k);
				}
		}
		//cout<<"backward:";
		//fflush(stdout);
		backward();
		end=clock();
	//	cout<<"backward time is "<<1.0*(end-start)/CLOCKS_PER_SEC<<" s"<<endl;
}

//assistive function
void neural_network::adjust_WB()
{
		for(int i=0;i<layer_num;i++)
		{
				layers[i]->adjust_WB();
		}
}

void neural_network::scalar_dWB(W_TYPE scalar)
{
		for(int i=0;i<layer_num;i++)
		{
				layers[i]->scalar_dWB(scalar);
		}
}

void neural_network::clean_dWB()
{
		for(int i=0;i<layer_num;i++)
		{
				layers[i]->clean_dWB();
		}
}

void neural_network::forward()
{
		for(int i=0;i<layer_num;i++)
		{
				int start=clock();
				layers[i]->forward();
				int end =clock();
				layers[i]->forward_time+=(1.0*(end-start)/CLOCKS_PER_SEC);
		}
}

void neural_network::backward()
{
		for(int i=last_layer;i>=0;i--)
		{
				//cout<<layers[i]->name<<" ";
				//fflush(stdout);
				int start=clock();
				layers[i]->backward();
				int end =clock();
				layers[i]->backward_time+=(1.0*(end-start)/CLOCKS_PER_SEC);
				//cout<<"|";
				//fflush(stdout);
		}
//		cout<<endl;
}

void neural_network::clear_time_count()
{
		for(int i=0;i<layer_num;i++)
		{
				layers[i]->clear_time_count();
		}
}

void neural_network::profile_time()
{
		for(int i=0;i<layer_num;i++)
		{
				layers[i]->profile_time();
		}
}
void neural_network::scalar_time(double scalar)
{

		for(int i=0;i<layer_num;i++)
		{
				layers[i]->scalar_time(scalar);
		}
}
