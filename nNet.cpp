#include "nNet.h"

using namespace std;

int activate(float sum)
{
	if(sum > 0) return 1;
	else		return -1;
}


Perception::Perception(int n)
{
    weights.resize(n);
//  start off with random weights between [-1,-1]
    for(int i = 0 ; i < weights.size() ; i++)
	{
		weights[i] = ((rand() % 3) + 1) - 2;
	}
}

int Perception::feedForward(float* input)
{
    float sum = 0;
    for(int i = 0 ; i < weights.size() ; i++)
	{
		sum += input[i]*weights[i];
	}
	return activate(sum);
}

void Perception::train(float *inputs, int desired)
{
	int guess = this->feedForward(inputs);
    float error = (desired -  (float)guess);
	for(int i = 0 ; i < weights.size() ; i++)
	{
        weights[i] += LEARNINGCONSTANT * error * inputs[i];
	}

}
void Perception:: reTrain()
{
    for(int i = 0 ; i < weights.size() ; i++)
    {
        weights[i] = ((rand() % 3) + 1) - 2;
    }
}

Trainer::Trainer(float x , float y, int a)
{

    inputs[0] = x;      //  x value
    inputs[1] = y;      //  y value
    inputs[2] = 1;      //  bias
	answer = a;
}


