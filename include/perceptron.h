#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#define INPUTS 2

typedef struct {
    float weights[INPUTS];
    float bias;
    float learning_rate;
} Perceptron;

void initialize(Perceptron *p);
int predict(Perceptron *p, float inputs[]);
void train(Perceptron *p, float inputs[],
           int expected);

#endif