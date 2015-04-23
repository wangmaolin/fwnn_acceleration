#include "hidden_layer.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;
extern double gaussrand();

hidden_layer::hidden_layer(const char * layer_name,int input_size,int output_size):full_connect_layer(layer_name,input_size,output_size)
{
		initial_parameter();
}
void hidden_layer::initial_parameter()
{
		cout<<"initial hidden layer parameter"<<endl;

		//initial W and B use uniform 
		double is=-4*sqrt(6.0/(N_in+N_out));
		cout<<"start:"<<is<<" ";
		double ie=4*sqrt(6.0/(N_in+N_out));
		cout<<"end:"<<ie<<endl;

		for (int i=0;i<N_out;i++)
		{
				B[i]=0;
				for(int j=0;j<N_in;j++)
				{
						W[i*N_in+j]=gaussrand();//is+(rand()%1000)*(ie-is)/1000.0;
				}
		}
}

void hidden_layer::forward()
{
		compute_sum();
		//calculate W*x+b
		for(int i=0;i<N_out;i++)
		{
				//calculate sigmoid
				out[i]=1/(1+exp(-Sum[i]));
		}
}

void hidden_layer::backward()
{
		for(int k=0;k<N_out;k++)
		{
				delta_in[k]*=out[k]*(1-out[k]);
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
