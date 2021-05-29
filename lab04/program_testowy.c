#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

int t;

struct Matrix
{
    int length;
    float **values;
};


struct Matrix* allocate_memory(int length) {
    struct Matrix* m = malloc(sizeof(struct Matrix));
    m->length = length;
    m->values = malloc(length * sizeof(float *));
    for (int i = 0; i < length; i++) {
        m->values[i] = malloc(m->length * sizeof(float));
        for (int j = 0; j < length; j++)
            m->values[i][j] = 0;
    }
    return m;
}

struct Matrix* read_matrix(char *path){
    int tmp;
    int length;
    FILE *file;
    file = fopen(path, "r");
    fscanf(file, "%d", &length);
    fscanf(file, "%d", &tmp);
    struct Matrix* m = allocate_memory(length);
    for (int i = 0; i < m->length; i++){
        for (int j = 0; j < m->length; j++)
            fscanf(file, "%f", &m->values[i][j]);
    }
    fclose(file);
    return m;

}


void print_matrix(struct Matrix *m)
{
    for (int i = 0; i < m->length; i++)
    {
        for (int j = 0; j < m->length; j++)
        {
            printf("%f ", m->values[i][j]);
        }
        printf("\n");
    }
}

struct Matrix* multiply_matrix_nm(struct Matrix *a, struct Matrix *b)
{
    int i, j, k;
    int length = a->length;
    struct Matrix *r = allocate_memory(length);
    
    for (i = 0; i < length; ++i)
        for (j = 0; j < length; ++j)
            for (k = 0; k < length; ++k)
                r->values[i][j] += a->values[i][k] * b->values[k][j];
    return r;
}



int main(int argc, char **argv){
    // struct Matrix a, b, c;
    struct Matrix *a, *b, *r;

    char* path1 = "matrix/matrixA500.txt";
    char* path2 = "matrix/matrixB500.txt";
    a = read_matrix(path1);
    b = read_matrix(path2);
    r = multiply_matrix_nm(a, b);
    
    
    printf("test");
    // int len = atoi(argv[2]);
    // make_matrix(&a, len);
    // make_matrix(&b, len);
    // make_matrix(&c, len);
    // float t = (float)atoi(argv[1]);
    // int N = a.length;
    // printf("Dlugosc macierzy: %d\n", len);
    // fill_matrix(&a, len);
    // fill_matrix(&b, len);
    // fill_matrix(&c, len);

    // pthread_t threads[(int)t];

    // struct info *inf = malloc(t * sizeof(struct info));

    // for (int i = 0; i < (int)t; i++)
    // {
    //     inf[i].start = (int)(((float)i * 1.0 / t) * (float)len);
    //     inf[i].end = (int)((((float)i + 1) * 1.0 / t) * (float)len);
    //     inf[i].length = len;
    //     inf[i].a = &a;
    //     inf[i].b = &b;
    //     inf[i].c = &c;

    // }
    // int rc;
    // struct timeval t0, t1;
    // gettimeofday(&t0, 0);
    // for (int i = 0; i < (int)t; i++)
    // {
    //     rc = pthread_create(&threads[i], NULL, multiply_matrix, &inf[i]);
    //     if (rc)
    //     {
    //         printf("Error:unable to create thread, %d\n", rc);
    //         exit(-1);
    //     }
    // }

    // for (int i = 0; i < t; i++)
    // {
    //     rc = pthread_join(threads[i], NULL);
    //     if (rc)
    //     {
    //         printf("Error:unable to join thread, %d\n", rc);
    //         exit(-1);
    //     }
    // }
    // gettimeofday(&t1, 0);
    // long long elapsed = (t1.tv_sec-t0.tv_sec)*1000000LL + t1.tv_usec-t0.tv_usec;
    // double elapsed2 = (double) elapsed/1000000;
    // printf("Czas z %d watkami: %f\n\n", (int)t, elapsed2);

    // pthread_exit(NULL);
    return 0;
}
