#include "forward_layer.h"
#include<iostream>
#include<stdlib.h>
using namespace std;
forward_layer::forward_layer(const char * layer_name,int input_size, int output_size):name(layer_name)
{
		N_in=input_size;
		N_out=output_size;
		cout<<"construct "<<name<<" layer start"<<endl;
		//initialize all pointer to NULL
		W=dW=B=dB=Sum=in=delta_in=out=delta_out=NULL;
		forward_time=0;
		backward_time=0;
		cout<<"construct "<<name<<" layer finish"<<endl;
}

void forward_layer::set_in(LAYER_IN_TYPE * in_p)
{
		if(in_p!=NULL)
		{
				in=in_p;
		}
		else
		{
				cout<<"warnning: set input is NULL!"<<endl;
		}
}
LAYER_OUT_TYPE forward_layer::get_out(int out_index)
{
		return out[out_index];
}

void forward_layer::set_delta_in(LAYER_OUT_TYPE * in_p)
{
		if(in_p!=NULL)
		{
				delta_in=in_p;
		}
		else
		{
				cout<<"warnning: set delta input is NULL!"<<endl;
		}	
}

forward_layer::~forward_layer()
{
		if(W!=NULL)
		{
				delete []W;
		}
		if(dW!=NULL)
		{
				delete []dW;
		}
		if(B!=NULL)
		{
				delete []B;
		}
		if(dB!=NULL)
		{
				delete []dB;
		}
		if(Sum!=NULL)
		{
				delete []Sum;
		}
		if(out!=NULL)
		{
				delete []out;
		}
		if(delta_out!=NULL)
		{
				delete []delta_out;
		}
		cout<<"destruct "<<name<<" layer finish"<<endl;
}

void forward_layer::scalar_dWB(W_TYPE scalar)
{
		for(int i=0;i<W_size;i++)
		{
				dW[i]*=scalar;
		}
		for(int i=0;i<B_size;i++)
		{
				dB[i]*=scalar;
		}
}

void forward_layer::adjust_WB()
{
		for(int i=0;i<W_size;i++)
		{
				W[i]+=dW[i];
		}
		for(int i=0;i<B_size;i++)
		{
				B[i]+=dB[i];
		}
}

void forward_layer::clean_dWB()
{
		for(int i=0;i<W_size;i++)
		{
				dW[i]=0;
		}
		for(int i=0;i<B_size;i++)
		{
				dB[i]=0;
		}
}

void forward_layer::display_out(int number)
{
		cout<<name<<" output:"<<endl;;
		if(number>=N_out||number<=0)
		{
				for(int i=0;i<N_out;i++)
				{
						cout<<" "<<out[i];
				}
		}
		else
		{
				for(int i=0;i<number;i++)
				{
						cout<<" "<<out[i];
				}
		}
		cout<<endl;
}	
void forward_layer::display_W(int number)
{
		cout<<name<<" W:"<<endl;;
		if(number>=(W_size)||number<=0)
		{
				for(int i=0;i<W_size;i++)
				{
						cout<<" "<<W[W_size];
				}
		}
		else
		{
				for(int i=0;i<number;i++)
				{
						cout<<" "<<W[i];
				}
		}
		cout<<endl;
}
void forward_layer::display_dW(int number)
{
		cout<<name<<" dW:"<<endl;;
		if(number>=(W_size)||number<=0)
	{
				for(int i=0;i<W_size;i++)
				{
						cout<<" "<<dW[W_size];
				}
		}
		else
		{
				for(int i=0;i<number;i++)
				{
						cout<<" "<<dW[i];
				}
		}
		cout<<endl;

}
void forward_layer::display_delta_out(int number)
{
	cout<<name<<" delta out:"<<endl;
	if(number>=(N_in)||number<=0)
	{
				for(int i=0;i<N_in;i++)
				{
						cout<<" "<<delta_out[N_in];
				}
		}
		else
		{
				for(int i=0;i<number;i++)
				{
						cout<<" "<<delta_out[i];
				}
		}
		cout<<endl;
}

void forward_layer::clear_time_count()
{
	forward_time=0;
	backward_time=0;
}
void forward_layer::profile_time()
{
	cout<<name<<" forward time:"<<forward_time<<"|backward_time:"<<backward_time<<endl;
}
void forward_layer::scalar_time(double scalar)
{
	forward_time*=scalar;
	backward_time*=scalar;
}
