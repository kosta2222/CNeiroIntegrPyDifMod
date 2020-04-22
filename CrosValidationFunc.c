#include "hedNN.h"
#include "utilMacr.h"
extern whole_NN_params NN[1];
extern int debug;

int is_2vecs_eq(float *out_NN, float *vec_y_test, int vec_size);
int calc_accur( int *scores, int rows);

int cross_validation(float * X_test, float *Y_test, int rows, int cols_X_test, int cols_Y_test) {
    float vec_x_test[max_in_nn];
    float vec_y_test[max_rows_orOut];
    int scores[max_validSet_rows];
    int scores_row = 0;
    int is_2vecs_eq_i=0;
    int acc = 0;
    for (int row = 0; row < rows; row++){
        for (int elem = 0; elem < NN->inputNeurons; elem++)
            vec_x_test[elem] = X_test[row * cols_X_test + elem];
        for (int elem = 0; elem < NN->outputNeurons; elem++)
            vec_y_test[elem] = Y_test[row * cols_Y_test + elem];
        predict_direct_CV(vec_x_test, debug);
        is_2vecs_eq_i=is_2vecs_eq(getHidden(&NN->list[NN->nlCount - 1]), vec_y_test, NN->outputNeurons);
        scores[scores_row] = is_2vecs_eq_i; 
        scores_row++;
        }
    acc = calc_accur(scores,rows);
    printf("Accuracy:%d%s\n",acc,"%");
/*
    _0_("cross_validation");
*/
    return acc;
}

/*
 *  Возвращает 1 если вектора равны и 0 если не равны
 */
int is_2vecs_eq(float *out_NN, float *vec_y_test, int vec_size) {
    float elem_of_out_nn = 0;
    for (int col = 0; col < vec_size; col++){
        elem_of_out_nn = (out_NN[col] > 0.5) ? 1 : 0;
        if ((int )elem_of_out_nn ==(int)vec_y_test[col])
            continue;
        else return 0;
        }
    return 1;
}

int calc_accur( int *scores, int rows) {
    int accuracy = 0;
    int sum = 0;
    // Посчитаем аккуратность
    for (int col = 0; col < rows; col++) sum += scores[col];
    accuracy =  ((float)sum / rows) * 100; // выразим в процентах
    return accuracy;
}
