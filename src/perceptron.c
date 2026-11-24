#include <stdlib.h>
#include "perceptron.h"

// inicialização
void initialize(Perceptron *p) {

    for (int i = 0; i < INPUTS; i++) {
        p->weights[i] = 0.0;
    }

    p->bias = 0.0;
    p->learning_rate = 0.1;

}

// função de previsao

int predict(Perceptron *p, float inputs[]) {

    float sum = p->bias;

    for (int i = 0; i < INPUTS; i++) {
        sum += inputs[i] * p->weights[i];
    }

    return (sum >= 0) ? 1 : 0;
}

// Treinamento
void train(Perceptron *p, float inputs[],
           int expected) {

    int prediction = predict(p, inputs);

    int error = expected - prediction;

    for (int i = 0; i < INPUTS; i++) {

        p->weights[i] +=
            p->learning_rate * error * inputs[i];
    }

    p->bias += p->learning_rate * error;
}