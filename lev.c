#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function: Every word, except for, with, the, or like that must be a capital letter,
// connected with "_" each other.
// Variable: Every word is a lower case, connected with "_" respectively.



// Calculating Levenshtein Distance
// first_arg, second_arg are the letters compared with each other
// the output is the distance

int Calc_Levenshtein_Distance(char *first_arg, char *second_arg){

    //numbers of indexes of array
    int x_axis = strlen(first_arg);
    int y_axis = strlen(second_arg);
    printf("%d, %d", x_axis, y_axis);

    //copying the letters
    //char array_letter_1[] = first_arg;
    //char array_letter_2[] = second_arg;

    // char array_letter_1[x_axis];
    // char array_letter_2[y_axis];
    char *array_letter_1 = (char *)malloc(sizeof(char) * x_axis);
    char *array_letter_2 = (char *)malloc(sizeof(char) * y_axis);
    strcpy(array_letter_1, first_arg);
    strcpy(array_letter_2, second_arg);
    
    printf("succeeded in generating arraies");
    
    //Generating the 2-D array
    //int array_lev[x_axis][y_axis];
    int **array_lev = (int **)malloc(x_axis);
    for(int i=0;i<x_axis;i++){
      array_lev[i] = (int *)malloc(y_axis);
    }

    int i;
    for(i = 0; i < x_axis + 1; i++) {
        array_lev[0][i] = i;
    }
    int j;
    for (j = 0; j < y_axis + 1; j++) {
        array_lev[j][0] = j;
    }
    
    //This is the main algorithm
    int k;
    for (k = 1; k < x_axis + 1; k++) {
        int l;
        for (l = 1; l < y_axis + 1; l++) {
            int number_upper_right_diagonal = array_lev[k-1][l-1];
            int number_left = array_lev[k-1][l] + 1;
            int number_upper = array_lev[k][l-1] + 1;

            // The flag for coparing letters
            int flag_same_or_true;
            if (array_letter_1[k-1] == array_letter_2[l-1]) {
                flag_same_or_true = 1;//same flag
            }
            else {
                flag_same_or_true = 0;
            }

            // Adding the number upper left diagonal if same 
            if (flag_same_or_true == 0){
                number_upper_right_diagonal = number_upper_right_diagonal + 1;
            }


            //So troublesome if-statements so please fix it hahahaha

            // if all the same
            if ((number_upper_right_diagonal == number_left) && (number_left == number_upper)){
                array_lev[k][l] = number_upper_right_diagonal;
            }

            // if one is smaller than others that are the same 
            if ((number_upper_right_diagonal == number_left) && (number_left > number_upper)){
                array_lev[k][l] = number_upper_right_diagonal;
            }
            if ((number_upper_right_diagonal == number_upper) && (number_upper > number_left)){
                array_lev[k][l] = number_upper_right_diagonal;
            }
            if ((number_left == number_upper) && (number_upper > number_upper_right_diagonal)){
                array_lev[k][l] = number_left;
            }
            if((number_upper_right_diagonal > number_left) && (number_left > number_upper)){
                array_lev[k][l] = number_upper_right_diagonal;
            }

            //if all is not same so boring
            if((number_upper_right_diagonal > number_left) && (number_left > number_upper)){
                array_lev[k][l] = number_upper_right_diagonal;
            }
            if((number_upper_right_diagonal > number_upper) && (number_upper > number_left)){
                array_lev[k][l] = number_upper_right_diagonal;
            }
            if((number_left > number_upper) && (number_upper > number_upper_right_diagonal)){
                array_lev[k][l] = number_left;
            }
            if((number_left > number_upper_right_diagonal) && (number_upper_right_diagonal > number_upper)){
                array_lev[k][l] = number_left;
            }
            if((number_upper > number_upper_right_diagonal) && (number_upper_right_diagonal > number_left)){
                array_lev[k][l] = number_upper;
            }
            if((number_upper > number_left) && (number_left > number_upper_right_diagonal)){
                array_lev[k][l] = number_upper;
            }
        }
    }
    free(array_letter_1);
    free(array_letter_2);
    for(int i=0;i<x_axis;i++){
      free(array_lev[i]);
    }
    free(array_lev);
    if (array_lev[x_axis][y_axis] != 0){
        return array_lev[x_axis][y_axis];
    }
    else{
        printf("fails");
        return 0;
    }

}

int main(){

    printf("Go");

    char *letter_1 = "sternritter";
    char *letter_2 = "askin_nakk_le_vaar";

    printf("sternritter");

    printf("pass 1");

    int answer = Calc_Levenshtein_Distance(letter_1, letter_2);

    printf("The distance is %d", answer);

    return 0;
}
