#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>

struct MATRIX{
    int **mat;
    int dim[2];
    int status;

}Mat[3];
void get_Dim(int ar, char c);
int validate_input(int row , int col);
void getMatrix(int ar);
void printM(int ar);
int get_user_option();
void save_to_file(int ar, char file_name[20]);
void do_opretion(int op);
int cheakIfMatrixExites(int ar,char c);
void load_mat_from_file(int ar);

int main(){
    printf("hHELLO IN matrix operation center\n");
    printf("What do you want to do today?\n");
    while (1)
    {
        int option = get_user_option();
        if (option == 1 || option == 2 ||option == 3){
            do_opretion(option);
        }else if (option == 4)
        {
            int arr;
            printf("1. Matrix A\n2. Matrix B\nEnter which matrix: ");
            scanf("%d",&arr);
            load_mat_from_file((arr-1));
        } else if(option == 5){
            int arr;
            char file_name[20];
            printf("1. Matrix A\n2. Matrix B\n3. Matrix C\nEnter which You want to save matrix: ");
            scanf("%d",&arr);
            printf("Enter file name: ");
            scanf_s("%s",&file_name);
            save_to_file((arr-1),file_name);

        }
        else if (option == 6){
            printf("exiting .....\n if you want to do another operations rerun the program\n");
            return 0;
        }else {

            printf("please enter a number between 1 and 6\n");
            printf("==============================================================================================================\n");
        }
    }
    return 0;


}

void getMatrix(int ar){
    /*
     * this function uses the array number in
     * the struct Matrix and uses a dynamic allocation
     * then asks the user for the values for the matrix
     */
    //Matrix array declaration using dynamic allocation
    Mat[ar].mat = (int**)malloc(sizeof(int*)*(Mat[ar].dim[0]));
    for(int i=0; i<(Mat[ar].dim[0]); i++)
        *(Mat[ar].mat+i) = (int*)malloc(sizeof(int)*(Mat[ar].dim[1]));
    // getting the values from the user
    for (int i = 0; i < (Mat[ar].dim[0]); i++) {
        for (int j = 0; j < (Mat[ar].dim[1]); j++) {
            scanf("%d", & Mat[ar].mat[i][j]);
        }
    }
    Mat[ar].status = 1;

}

void get_Dim(int ar, char c){
    printf("Enter Matrix %c dimtions \n", c);
    printf("enter the number of row:");
    scanf("%d", &(Mat[ar].dim[0]));
    printf("enter the number of column:");
    scanf("%d", &(Mat[ar].dim[1]));
    validate_input((Mat[ar].dim[0]), (Mat[ar].dim[1]));
}

int validate_input(int row , int col){
    //checks if the user inputs for the row and col are correct
    if (row <= 0 || col <=0 ){
        printf("pleaes Enter a Valid dimensions for the Matrix");
        exit(-1);
    }
    else return 1;

}
void printM(int ar){
    for(int i=0; i<(Mat[ar].dim[0]); i++) {
        for(int j=0; j<(Mat[ar].dim[1]); j++)
            printf("%d\t", Mat[ar].mat[i][j]);
        printf("\n");
    }
}
int get_user_option(){
    printf("1. Addition\n2. Subtraction\n3. Multiplication\n4. Load a MATRIX from a file \n5. save a MATRIX to a File\n6. Exit\n");
    int option ;
    printf("Enter numbers between 1 to 6 : ");
    scanf("%d", &option);
    return option;
}
void save_to_file(int ar, char file_name[20]){
    /* the function  takes the number of the array of the struct and
     * the name of the file that the user want to save in
     * and save the matrix and a file in format
     *  row
     *  col
     *     MATRIX
     *
     */

    if(Mat[ar].status != 1){
        printf("Can't save an empty Matrix do an operation than save the matrix\n");
        return;
    }
    FILE * fPtr;
    fPtr = fopen(file_name,"w");
    if (fPtr){
        fprintf(fPtr,"%d\n", Mat[ar].dim[0]);
        fprintf(fPtr,"%d\n", Mat[ar].dim[1]);
        for (int i = 0; i < Mat[ar].dim[0]; i++)
        {
            for (int j = 0; j < Mat[ar].dim[1]; j++)
            {
                fprintf(fPtr,"%d\t", Mat[ar].mat[i][j]);
            }
            fprintf(fPtr, "\n");

        }

        printf("the file was written successfully the name the file is %s\n",file_name);
    }else{
        printf("can't Write to the file \n");
    }
    fclose(fPtr);
}
void sumM(){
    Mat[2].mat = (int**)malloc(sizeof(int*)*(Mat[2].dim[0]));
    for(int i=0; i<(Mat[2].dim[0]); i++)
        *(Mat[2].mat+i) = (int*)malloc(sizeof(int)*(Mat[2].dim[1]));
    for(int i=0; i<(Mat[2].dim[0]); i++)
        for(int j=0; j<(Mat[2].dim[1]); j++)
            Mat[2].mat[i][j] = Mat[0].mat[i][j] + Mat[1].mat[i][j];
}
void subM(){
    Mat[2].mat = (int**)malloc(sizeof(int*)*(Mat[2].dim[0]));
    for(int i=0; i<(Mat[2].dim[0]); i++)
        *(Mat[2].mat+i) = (int*)malloc(sizeof(int)*(Mat[2].dim[1]));
    for(int i=0; i<(Mat[2].dim[0]); i++)
        for(int j=0; j<(Mat[2].dim[1]); j++)
            Mat[2].mat[i][j] = Mat[0].mat[i][j] - Mat[1].mat[i][j];

}
//NOTE make mat 2 dim 0 to mat 0 dim 0 && and mat 2 dim 1 to mat 1 dim 1
void mulM(){
    Mat[2].mat = (int**)malloc(sizeof(int*)*(Mat[2].dim[0]));
    for(int i=0; i<(Mat[2].dim[0]); i++)
        *(Mat[2].mat+i) = (int*)malloc(sizeof(int)*(Mat[2].dim[1]));
    for(int i=0; i<(Mat[2].dim[0]); i++)
        for(int j=0; j<(Mat[2].dim[1]); j++){
            Mat[2].mat[i][j] = 0;
            for (int k = 0; k < (Mat[1].dim[0]); k++) {
                Mat[2].mat[i][j] += Mat[0].mat[i][k] * Mat[1].mat[k][j];
            }
        }

}

void do_opretion(int op){
    /* the function takes an option to operation on and check if the operation can be done
     * then do the operation and save the changes to matrix C
     * */
    if (cheakIfMatrixExites(0, 'A')){
        get_Dim(0,'A');
        printf("enter Matrix A:\n");
        getMatrix(0);
    }
    if (cheakIfMatrixExites(1, 'B')){
        get_Dim(1,'B');
        printf("enter Matrix B:\n");
        getMatrix(1);
    }
    if (op == 1){
        if (Mat[0].dim[0] == Mat[1].dim[0] && Mat[0].dim[1] == Mat[1].dim[1]){
            Mat[2].dim[0] = Mat[0].dim[0];
            Mat[2].dim[1] = Mat[0].dim[1];
            printf("the Addiotion of Matrix A and Matrix B is : \n");
            sumM();
            printM(2);
            Mat[2].status = 1;
        }
        else {
            printf("can't do the optretion , Enter an identical size matrices ");
        }
    }else if (op == 2)
    {
        if (Mat[0].dim[0] == Mat[1].dim[0] && Mat[0].dim[1] == Mat[1].dim[1]){
            Mat[2].dim[0] = Mat[0].dim[0];
            Mat[2].dim[1] = Mat[0].dim[1];
            printf("the Subtraction of Matrix A and Matrix B is : \n");
            subM();
            printM(2);
            Mat[2].status = 1;

        }
        else {
            printf("can't do the optretion , Enter an identical size matrices ");
        }

    }else {
        if (Mat[0].dim[1] != Mat[1].dim[0]){
            printf("can't do matrix multiplication ");
        }
        Mat[2].dim[0] = Mat[0].dim[0];
        Mat[2].dim[1] = Mat[1].dim[1];
        printf("the Mul is : \n");
        mulM();
        printM(2);
        Mat[2].status = 1;

    }
}
int cheakIfMatrixExites(int ar, char c){
    /* checks if the status var in struct Matrix
     * which mean if the matrix dose have values or not
    */
    if (Mat[ar].status != 1){
        return 1;
    } else{
        char ans;
        printf("do you want to rewrite Matrix %c (y,n): ",c);
        scanf(" %c",&ans);
        if (ans == 'y'){
            return 1;
        } else{
            return 0;
        }
    }

}

void load_mat_from_file(int ar){
    char file_name[100];
    int row,col,num;
    printf("Enter the name of the file: \n");
    scanf("%s", file_name);
    FILE * fPtr;
    fPtr = fopen(file_name,"r");
    if (fPtr != NULL){

        fscanf(fPtr,"%d", &row);
        Mat[ar].dim[0] = row;
        fscanf(fPtr,"%d", &col);
        Mat[ar].dim[1] = col;
        Mat[ar].mat = (int**)malloc(sizeof(int*)*row);
        for(int i=0; i<row; i++)
            *(Mat[ar].mat+i) = (int*)malloc(sizeof(int)*col);
        for (int i = 0; i < Mat[ar].dim[0]; i++)
        {
            for (int j = 0; j < Mat[ar].dim[1]; j++)
            {
                fscanf(fPtr,"%d\t", &num);
                Mat[ar].mat[i][j] = num;
            }
        }
        Mat[ar].status = 1;
        printf("the file was read successfully from file : %s \n", file_name);
    }else{
        printf("can't read from file %s\n",file_name);
    }
    fclose(fPtr);

}