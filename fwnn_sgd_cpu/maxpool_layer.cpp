#include "maxpool_layer.h"
#include<stdlib.h>
#include<iostream>
#include<stdio.h>
#include<math.h>
using namespace std;

maxpool_layer::maxpool_layer(const char * layer_name,int input_size, int output_size):
	forward_layer(layer_name,input_size,output_size),
	pool_size(input_size/output_size)
{
	cout<<"construct max pooling layer"<<endl;
	cout<<"pool size: "<<pool_size<<endl;
	pool_side_len=sqrt(pool_size);
	cout<<"pool side len: "<<pool_side_len<<endl;
	W_size=0;
	B_size=0;	
	alloc_parameter();
}
void maxpool_layer::alloc_parameter()
{
	cout<<"start allocating "<<name<<" parameter space"<<endl;

	out=new LAYER_OUT_TYPE[N_out];
	delta_out=new LAYER_OUT_TYPE[N_in];
	if(out==NULL||delta_out==NULL)
	{
		cout<<"alloc space failed"<<endl;
		exit(1);
	}
}
void maxpool_layer::initial_parameter()
{

}
void maxpool_layer::forward()
{
	for(int i=0;i<N_out;i++)
	{
		LAYER_OUT_TYPE max_value=in[i*pool_size];
		for(int j=0;j<pool_side_len;j++)
		{
			for(int k=0;k<pool_side_len;k++)		
			{
				if(in[i*pool_size+j*pool_side_len+k]>max_value)
				{
					max_value=in[i*pool_size+j*pool_side_len+k];
				}
			}
		}
		out[i]=max_value;
	}
}
void maxpool_layer::backward()
{
	for(int i=0;i<N_out;i++)
	{
		int max_x=0;
		int max_y=0;
		LAYER_OUT_TYPE max_value=in[i*pool_size];
		for(int j=0;j<pool_side_len;j++)
		{
			for(int k=0;k<pool_side_len;k++)		
			{
				delta_out[i*pool_size+j*pool_side_len+k]=0;
				if(in[i*pool_size+j*pool_side_len+k]>max_value)
				{
					max_x=j;
					max_y=k;
					max_value=in[i*pool_size+j*pool_side_len+k];
				}
			}
		}
		delta_out[i*pool_size+max_x*pool_side_len+max_y]=delta_in[i];
	}
}
