#include "dataset.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define LINE_SIZE 1048576

static int count_columns(const char *line) {
    int count = 1;
    for (const char *p = line; *p; ++p) if (*p == ',') count++;
    return count;
}



int dataset_load_csv(const char *path, Dataset *data) {
    FILE *fp = fopen(path, "r");

    char *line = malloc(LINE_SIZE);
    fgets(line, LINE_SIZE, fp);

    int features = count_columns(line) - 1;


    int capacity = 256, rows = 0;
    double **x = malloc((size_t)capacity * sizeof(*x));
    int *y = malloc((size_t)capacity * sizeof(*y));

    while (fgets(line, LINE_SIZE, fp)) {
        if (line[0] == '\n' || line[0] == '\r') continue;
        if (rows == capacity) {
            capacity *= 2;
            double **nx = realloc(x, (size_t)capacity * sizeof(*x));
            int *ny = realloc(y, (size_t)capacity * sizeof(*y));
            if (!nx || !ny) {
                if (nx) x = nx;
                if (ny) y = ny;
                for (int i = 0; i < rows; ++i) free(x[i]);
                free(x); free(y); free(line); fclose(fp); return 0;
            }
            x = nx; y = ny;
        }

        x[rows] = malloc((size_t)features * sizeof(**x));
        if (!x[rows]) {
            for (int i = 0; i < rows; ++i) free(x[i]);
            free(x); free(y); free(line); fclose(fp); return 0;
        }

        char *token = strtok(line, ",\r\n");
        char *end = NULL;
        if (!token) continue;
        errno = 0;
        long label = strtol(token, &end, 10);
        if (errno || end == token || *end || (label != -1 && label != 1)) {
            fprintf(stderr, "Rótulo inválido na linha %d\n", rows + 2);
            free(x[rows]);
            for (int i = 0; i < rows; ++i) free(x[i]);
            free(x); free(y); free(line); fclose(fp); return 0;
        }
        y[rows] = (int)label;
        int col = 0;
        while ((token = strtok(NULL, ",\r\n")) && col < features) {
            errno = 0;
            double value = strtod(token, &end);
            if (errno || end == token || *end) {
                fprintf(stderr, "Valor inválido na linha %d, coluna %d\n", rows + 2, col + 2);
                free(x[rows]);
                for (int i = 0; i < rows; ++i) free(x[i]);
                free(x); free(y); free(line); fclose(fp); return 0;
            }
            x[rows][col++] = value;
        }
        if (col != features) {
            fprintf(stderr, "Número incorreto de colunas na linha %d\n", rows + 2);
            free(x[rows]);
            for (int i = 0; i < rows; ++i) free(x[i]);
            free(x); free(y); free(line); fclose(fp); return 0;
        }
        rows++;
    }
    free(line); fclose(fp);
    if (!rows) { free(x); free(y); return 0; }
    data->rows = rows; data->cols = features; data->x = x; data->y = y;
    return 1;
}

void dataset_free(Dataset *data) {
    if (!data) return;
    for (int i = 0; i < data->rows; ++i) free(data->x[i]);
    free(data->x); free(data->y);
    data->x = NULL; data->y = NULL; data->rows = data->cols = 0;
}
