#ifndef PERCEPTRON_H
#define PERCEPTRON_H
typedef struct {
    int n_features;
    double *weights;
    double bias;
    double learning_rate;
    int epochs;
} Perceptron;
int perceptron_init(Perceptron *model, int n_features, double learning_rate, int epochs);
void perceptron_free(Perceptron *model);
int perceptron_predict(const Perceptron *model, const double *x);
int perceptron_train(Perceptron *model, double **x, const int *y, int n_samples, const char *history_path);
int perceptron_save(const Perceptron *model, const char *path);
#endif
