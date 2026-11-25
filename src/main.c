#include <stdio.h>
#include <stdlib.h>
#include "dataset.h"
#include "perceptron.h"


// a main recebe um numero de argumentos inteiros pelo argc 
// e um ponteiro que armazena os argumentos pelo argv.
int main(int argc, char **argv) {

    // converte para inteiro
    // epochs é as epocas
    int epochs = atoi(argv[3]);
    // converta decimal
    // taxa de aprendizagem
    double rate = atof(argv[4]);


    // inicializa o dataset
    Dataset train = {0}, test = {0};

    dataset_load_csv(argv[1], &train);
    dataset_load_csv(argv[2], &test);

    



    Perceptron p;

    initialize(&p);

    float inputs[4][2] = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}
    };

    int expected[4] = {
        0, 0, 0, 1
    };

    // Treinamento
    for (int epoch = 0; epoch < 100; epoch++) {

        int errors = 0;

        for (int i = 0; i < 4; i++) {

            int prediction = predict(&p, inputs[i]);

            if (prediction != expected[i]) {
                errors++;
            }

            train(&p, inputs[i], expected[i]);
        }

        printf("Epoca %d | Erros: %d\n",
               epoch + 1, errors);

        if (errors == 0) {
            break;
        }
    }

    // Testando o Perceptron
    printf("\nResultados:\n");

    for (int i = 0; i < 4; i++) {

        int result = predict(&p, inputs[i]);

        printf("%.0f AND %.0f = %d\n",
               inputs[i][0],
               inputs[i][1],
               result);
    }

    return 0;
}