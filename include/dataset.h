#ifndef DATASET_H
#define DATASET_H
typedef struct {
    int rows;
    int cols;
    double **x;
    int *y;
} Dataset;
int dataset_load_csv(const char *path, Dataset *data);
void dataset_free(Dataset *data);
#endif