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
    // caso a função dataset_load falhe ele limpa a memoria do treino
    if(!dataset_load_csv(argv[2], &test)) {
        dataset_free(&train);
    }

    Perceptron model = {0};

    // inicia o perceptron
    perceptron_init(&model, train.cols, rate, epochs);
    printf("Treino: %d amostras | Atributos: %d | Teste: %d amostras\n",
       train.rows, train.cols, test.rows);

    
    char history[512], predictions[512], model_file[512];
    snprintf(history, sizeof(history), "%s_history.csv", argv[5]);
    snprintf(predictions, sizeof(predictions), "%s_predictions.csv", argv[5]);
    snprintf(model_file, sizeof(model_file), "%s_model.txt", argv[5]);
    int ok = perceptron_train(&model, train.x, train.y, train.rows, history);

    perceptron_free(&model); dataset_free(&train); dataset_free(&test);
    return 0;

}