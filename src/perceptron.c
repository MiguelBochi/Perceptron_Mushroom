#include <stdio.h>
#include <stdlib.h>
#include "perceptron.h"

// inicialização
int perceptron_init(Perceptron *model, int n_features, double learning_rate, int epochs) {
    model->n_features = n_features;
    model->learning_rate = learning_rate;
    model->epochs = epochs;

    // Aloca memória para os pesos
    model->weights = (double *)malloc(n_features * sizeof(double));
    if (model->weights == NULL) {
        return -1; // Falha na alocação de memória
    }

    // Inicializa os pesos e o bias
    for (int i = 0; i < n_features; i++) {
        model->weights[i] = 0.0;
    }
    model->bias = 0.0;

    model->learning_rate = learning_rate;
    model->epochs = epochs;

    return 0; // Sucesso
}

void perceptron_free(Perceptron *model) {
    if (model->weights != NULL) {
        free(model->weights);
        model->weights = NULL;
    }
}

int perceptron_predict(const Perceptron *model, const double *x) {
    double sum = model->bias;
    for (int i = 0; i < model->n_features; i++) {
        sum += x[i] * model->weights[i];
    }
    return (sum >= 0) ? 1 : 0;
}

int perceptron_train(Perceptron *model, double **x, const int *y, int n_samples, const char *history_path) {
    FILE *history_file = fopen(history_path, "w");
    if (history_file == NULL) {
        return -1; // Falha ao abrir o arquivo de histórico
    }

    for (int epoch = 0; epoch < model->epochs; epoch++) {
        int correct_predictions = 0;
        for (int i = 0; i < n_samples; i++) {
            int prediction = perceptron_predict(model, x[i]);
            int error = y[i] - prediction;

            // Atualiza os pesos e o bias
            for (int j = 0; j < model->n_features; j++) {
                model->weights[j] += model->learning_rate * error * x[i][j];
            }
            model->bias += model->learning_rate * error;

            if (error == 0) {
                correct_predictions++;
            }
        }
        fprintf(history_file, "Epoch %d: Accuracy: %.2f%%\n", epoch + 1, (double)correct_predictions / n_samples * 100);
    }

    fclose(history_file);
    return 0; // Sucesso
}

int perceptron_save(const Perceptron *model, const char *path) {
    FILE *file = fopen(path, "wb");
    if (file == NULL) {
        return -1; // Falha ao abrir o arquivo
    }

    fwrite(&model->n_features, sizeof(int), 1, file);
    fwrite(model->weights, sizeof(double), model->n_features, file);
    fwrite(&model->bias, sizeof(double), 1, file);
    fwrite(&model->learning_rate, sizeof(double), 1, file);
    fwrite(&model->epochs, sizeof(int), 1, file);

    fclose(file);
    return 0; // Sucesso
}
