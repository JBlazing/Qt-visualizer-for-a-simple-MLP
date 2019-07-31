#ifndef nNet_H
#define nNet_h
#include <vector>
#include <ctime>
#include <cstdlib>

#define LEARNINGCONSTANT .02

using namespace std;

class Perception{
	vector<float> weights;
public:
    Perception(int);
    int feedForward(float* input);
    void train(float* inputs, int desired);
    void reTrain();
};

class Trainer{
    float inputs[3];
	int answer;
public:
	Trainer(float,float,int);
    float* input() {return inputs;}
    float getX(void) {return inputs[0];}
	float getY() {return inputs[1];}
	int getAnswer(void) {return answer;}
};


#endif
