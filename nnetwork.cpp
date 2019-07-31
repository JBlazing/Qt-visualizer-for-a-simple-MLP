#include "nnetwork.h"
Connection::Connection(Neuron *from, Neuron *to, float w){
   a = from;
   b = to;
   weight = w;
}

void Connection::feedForward(float input)
{
    b->feedForward(input * weight);
}
void Connection::weights(float input)
{
    weight += input;
}
void Connection::train(float input,float desied)
{

}

Neuron::Neuron()
{
    sum = 0;
}
void Neuron::train(float inputs,float desired)
{
    int guess ;//= this->feedForward(inputs);
    float error = (desired -  (float)guess);

    for(int i = 0 ; i < connected.size() ; i++)
    {
        float input = LEARNINGCONSTANT * error * inputs;
        connected[i]->weights(input);
    }
}

Neuron::~Neuron(){
    if(connected.empty())
        for(int i = 0 ; i < connected.size( ) ; i++)
            delete connected[i];

}
void Neuron::feedForward(float input)
{
    float sum = sum + input;

       this->fire(sum);
       sum = 0;

}
void Neuron::fire(float sum)
{
    for(int i = 0 ; i < connected.size() ; i++)
        connected[i]->feedForward(sum);
}
Network::Network()
{

}

Network::Network(int nodes)
{
    neurons.resize(nodes);
    for(int i = 0; i < neurons.size() ; i++)
    {
        Neuron *temp = new Neuron();
        neurons[i] = temp;
    }
}
Network::~Network()
{
    if(!neurons.empty())
        for(int i = 0 ; i < neurons.size( ) ; i++)
            delete neurons[i];
}

void Network::addNeuron(Neuron * n)
{
    neurons.push_back(n);
}

void Network::connect (Neuron *from, Neuron *to)
{
    Connection *  c = new Connection(from,to,NULL);
    from->addConnection(c);
}

