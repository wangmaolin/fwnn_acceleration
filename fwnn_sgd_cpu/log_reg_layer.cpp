#include "log_reg_layer.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

extern double gaussrand();

log_reg_layer::log_reg_layer(const char * layer_name,int input_size,int output_size):full_connect_layer(layer_name,input_size,output_size)
{
		initial_parameter();
}
void log_reg_layer::initial_parameter()
{
		cout<<"initial log layer parameter "<<endl;
		//initial W and B
		for (int i=0;i<N_out;i++)
		{
				B[i]=0;
				for(int j=0;j<N_in;j++)
				{
						W[i*N_in+j]=0;
				}
		}
}

void log_reg_layer::forward()
{
		//softmax function
		compute_sum();
		//calculate final softmax
		float sum=0;
		for(int i=0;i<N_out;i++)
		{
				out[i]=exp(Sum[i]);
				sum+=out[i];
		}
		for(int i=0;i<N_out;i++)
		{
				out[i]/=sum;
		}
}

void log_reg_layer::backward()
{
		for(int k=0;k<N_out;k++)
		{
				for(int j=0;j<N_in;j++)
				{
						dW[k*N_in+j]+=in[j]*(-delta_in[k]);
				}
				dB[k]+=(-delta_in[k]);
		}

		for(int k=0;k<N_in;k++)
		{
				delta_out[k]=0;
				for(int m=0;m<N_out;m++)
				{
						delta_out[k]+=delta_in[m]*W[m*N_in+k];
				}	
		}
}
