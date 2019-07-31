#include <nNet.h>
#ifndef NNETWORK_H
#define NNETWORK_H

class Neuron;
class Connection{
    Neuron * a;
    Neuron * b;
    float weight;
public:
    Connection(Neuron *, Neuron *, float);
    Neuron * destination(){ return b; }
    void feedForward(float);
    void train(float,float);
    void weights(float);

};
class Neuron{
    vector< Connection * > connected;
    int sum;
public:
    Neuron();
    ~Neuron();
    void addConnection(Connection * c) {connected.push_back(c) ;}
    void feedForward(float input);
    void fire(float sum);
    void train(float, float);


};

class Network{
    vector< Neuron * > neurons;
    float xLocation, yLocation;
public:
    Network(int);
    Network();
    ~Network();
    void addNeuron(Neuron *n);
    void connect ( Neuron *from, Neuron *to);
};


#endif // NNETWORK_H
