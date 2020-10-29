///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FileName: Assignment 2.0.es                                                                                                                                //                                                                              //
//Description: Program that reads the values from a file into a 2D array that makes up a matrix, extracts a part of that matrix to form a 2x2 sub matrix     //
//and, subsequently, finds the inverse of the 2x2 matrix.                                                                                                    //
//The size of the first matrix, i.e., number of rows and number of columns is defined by the user, so long as it is within the bounds of a 10 x 10 matrix.   //
//If this matrix is chosen to be greater than 2x2, the program proceeds to compute a 2x2 subset of this matrix. It asks the user, from which row and column  //
//in the original matrix, the subset should start and displays it the screen. After, it calculates and displays the determinant of the sub matrix and if it  //
//is different from 0, the inverse of this matrix is displayed. Finally, the program asks the user whether it wants to run the program again and will go on  //
//a loop until the user decides to quit.                                                                                                                     //
//For all of these matrices, the program asks the user to name them and displays their contents alongside a reference to their given name.                   //
//Four functions are used: one for the user to input the name and size of the first matrix; one to display the various matrices; another to build the 2x2    //
//subset matrix and calculate its determinant and, one to compute the inverse of the subset matrix.                                                          //                                                                                                                                                                                                         //
//Written by Jane Malalane, April 2020                                                                                                                       //                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*header file declarations*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct matrix
{
   char name;   // to hold the 1 character name of the matrix
   float matrix[10][10];    // to hold the values in a matrix of a maximum of 10 rows and 10 columns
   int nrows;       // to hold the number of rows used  in the matrix
   int ncolumns;    // to hold the number of columns used in the matrix
};
/*Function declarations*/
void matrixInput(struct matrix *m1, FILE *fin);
void matrixDisplay(struct matrix mat);
float matrixDeterminant(struct matrix m1, struct matrix *m2, int *check);
void matrixInverse(struct matrix m2, float det, struct matrix *m3);

int main()  // main function
{
    char answer = '1';  // used to know whether the user wants to loop the program or end it

    while(answer=='1')  // the program will run as long as the user wants, i.e., as the character value that the "answer" character holds is '1'.
    {
        struct matrix m1;   // original matrix
        struct matrix m2;   // 2x2 sub matrix
        struct matrix m3;   // inverse matrix

        /*variable declarations*/
        float det;          // determinant of the 2x2 sub matrix
        int check;          // variable used to program defensively

        /* declaration of pointer to the file stream*/
        FILE* fin;

        fin=fopen("matrix2.txt","r");   // opens file to read
        if(fin==NULL)                   // if the file is not found, a null pointer is returned from fopen
        {
            printf("File was not found.");
        }
        else
        {
            matrixInput(&m1, fin);  // entering original matrix
            matrixDisplay(m1);      // displays original matrix
            det = matrixDeterminant(m1, &m2, &check);   // finding the determinant
            if(check!=0)    // if the size of the original matrix is greater than 2x2
            {
                matrixDisplay(m2);  // displays 2x2 sub matrix
                printf("The determinant is: %.2f.\n\n",det);    // prints out the determinant of the 2x2 sub matrix
                if(check==1)    // if the determinant is different from 0, the generated 2x2 sub matrix has an inverse
                {
                    matrixInverse(m2, det, &m3);
                    matrixDisplay(m3);  // displays the inverse matrix
                }
                else    // if the determinant of the 2x2 sub matrix is equal to 0, it has no inverse
                {
                    printf("Matrix %c doesn't have an inverse because its determinant equals 0.\n",m2.name);
                }
            }
            else    // if the size of the original matrix is less than 2x2, a 2x2 sub matrix cannot be built from it and, hence, neither can the inverse of the sub matrix
            {
                printf("Matrix is smaller than 2x2.\nThe determinant and inverse do not exist!");
            }
        }

            getchar();  // without this, program sees the enter as part of the meaningful user input, which causes faults in the output
            printf("\nWould you like to input another matrix? (type 1 for yes or 0 for no): ");
            scanf("%c",&answer);
            getchar();
            while(answer!='0'&&answer!='1') // if the user inputs anything different from 0 or 1, they will be asked to input again
            {
            printf("Input is invalid.\n");
            printf("Would you like to input another matrix? (type 1 for yes or 0 for no): ");
            scanf("%c",&answer);
            getchar();
            }
            printf("\n");
    }
}
void matrixInput(struct matrix *m1, FILE *fin)  // function to input the size and name of the matrix and read in the values from the file that integrate the matrix
{
    /* variable declarations */
    int b, nrows, ncolumns, i, j;
    float a;
    char name, enter;   //"enter" variable is used to filter out the non-meaningful part of the user input, just like getchar()

    /* sets name of matrix */
    printf("Enter one character name for the matrix:\n");
    (*m1).name = getchar(); // scans the user's input and assigns it to the name variable
    getchar();
    while(!(((*m1).name>='A' && (*m1).name<='Z')||((*m1).name>='a' && (*m1).name<='z'))) // user must input an upper or lower case letter as the name of the matrix, otherwise they will be asked to input again
    {
        printf("Character is invalid. Try again:\n");
        (*m1).name = getchar();
        getchar();
    }

    /* sets number of rows of matrix */
    printf("Enter the number of rows of the matrix (1-10):\n");
    scanf("%f%c", &a,&enter);   // number of rows input is read as a character and the enter from the user after the row number input is assigned to the "enter" variable
    b = (int) a;    // converts character into integer
    while(!((a-b==0)&&(a>0 && a<11)))   // user must input a whole number from 1 to 10 as the number of rows of the matrix, otherwise they will be asked to input again
    {
        printf("number is invalid. Try again:\n");
        scanf("%f%c", &a,&enter);
        b = (int) a;
    }
    (*m1).nrows = b;    // assigns the integer to the variable that represents the number of rows of the matrix

    /*  sets number of columns of matrix */
    printf("Enter the number of columns of the matrix (1-10):\n");
    scanf("%f%c", &a,&enter);   // number of columns input is read as a character
    b = (int) a;     // converts character into integer
    while(!((a-b==0)&&(a>0 && a<11)))   // user must input a number from 1 to 10 as the number of columns of the matrix, otherwise they will be asked to input again
    {
        printf("number is invalid. Try again:\n");
        scanf("%f%c", &a,&enter);
        b = (int) a;
    }
    (*m1).ncolumns = b; // assigns the integer to the variable that represents the number of columns of the matrix

    /* reads values from the file into the matrix */
    for(i=0; i<(*m1).nrows; i++)    // this loop index controls the rows
    {
        for(j=0; j<(*m1).ncolumns; j++) // this loop index controls the columns
        {
            fscanf(fin,"%f",&((*m1).matrix[i][j])); // values are read in from the file to integrate the matrix whose size has been previously defined
        }
    }
}

void matrixDisplay(struct matrix mat)   // function to display the name of the matrix and the values in the 2D array that makes up the matrix
{
   /*variable declarations*/
   int i,j;

   printf("Matrix %c is a %d x %d matrix. \n", mat.name, mat.nrows, mat.ncolumns);  // prints name and size of matrix

   /*prints matrix contents, filling out every column for each row*/
   printf("Matrix %c:\n",mat.name);
   for(i=0; i<mat.nrows; i++)   // this loop index controls the rows
   {
        printf("Row %d:", i);
        for(j=0; j<mat.ncolumns; j++)   // this loop index controls the columns
        {
            printf("\t%3.2f ", mat.matrix[i][j]);;
        }
        printf("\n");
   }
}

float matrixDeterminant(struct matrix m1, struct matrix *m2, int*check) // function to build the 2x2 subset matrix and find its determinant

{
    /*variable declarations*/
    int b, nrow2, ncolumn2, i, j;
    float a, det;
    char enter;

    if(!(m1.nrows>=2&&m1.ncolumns>=2))  // if the size of the original matrix is less than 2x2, check equals 0
    {
        *check = 0;
    }

    else    // if the size of the original matrix is greater than 2x2, program can proceed to create a 2x2 matrix
    {
        /*sets name of 2x2 matrix*/
        printf("Enter one character name for the 2x2 matrix:\n");
        (*m2).name = getchar(); // scans the user's input and assigns it to the name variable
        getchar();
        while(!(((*m2).name>='A' && (*m2).name<='Z')||((*m2).name>='a' && (*m2).name<='z')))    // user must input an upper or lower case letter as the name of the sub matrix, otherwise they will be asked to input again
        {
            printf("character is invalid. Try again:\n");
            (*m2).name = getchar();
            getchar();
        }

        /* sets number of rows of 2x2 matrix*/
        printf("Enter row number where to start 2x2 matrix, number needs to be between 0 and %d:\n", m1.nrows-2);
        scanf("%f%c", &a,&enter);   // row number input is read as a character
        b = (int) a;    // converts character into integer
        while(!((a-b==0)&&(a>=0 && a<=m1.nrows-2))) // user must input a whole number as the row number from which the subset matrix should start, that is at least one row from the last row of the original matrix
        {
            printf("number is invalid. Try again:\n");
            scanf("%f%c", &a,&enter);
            b = (int) a;
        }
        nrow2 = b;  // assigns the integer to the variable that represents the row from which the 2x2 subset of the original matrix will begin

        /*sets number of columns of 2x2 matrix*/
        printf("Enter column number where to start 2x2 matrix, number needs to be between 0 and %d:\n", m1.ncolumns-2);
        scanf("%f%c", &a,&enter);   // column number input is read as a character
        b = (int) a;    // converts character into integer
        while(!((a-b==0)&&(a>=0 && a<=m1.ncolumns-2)))  // user must input a whole number as the column number from which the subset matrix should start, that is at least one column from the last row of the original matrix
        {
            printf("number is invalid. Try again:\n");
            scanf("%f%c", &a, &enter);
            b = (int) a;
        }
        ncolumn2 = b;   // assigns the integer to the variable that represents the column from which the 2x2 subset of the original matrix will begin

        /*sets subset matrix as a 2x2 matrix*/
        (*m2).nrows=2;
        (*m2).ncolumns=2;

        /*reads the values from the original matrix into the 2x2 matrix*/
        for(i=0; i<2; i++)  // this loop index controls the rows
        {
            for(j=0; j<2; j++)  // this loop index controls the columns
            {
                (*m2).matrix[i][j]=m1.matrix[nrow2+i][ncolumn2+j];
            }
        }

        /*computes determinant of 2x2 matrix*/
        det = (*m2).matrix[0][0]*(*m2).matrix[1][1]-(*m2).matrix[0][1]*(*m2).matrix[1][0];

        /*check for defensive programming*/

        if(det>0||det<0)   // if the determinant is other than zero, the integer "1" is assigned to the check variable
        {
            *check = 1;
        }
        else    // if the determinant equals zero, the integer "2" is assigned to the check variable
        {
            *check = 2;
        }

        return det; // returns the determinant of the 2x2 subset matrix

    }
}

void matrixInverse(struct matrix m2, float det, struct matrix *m3)   // function to find the inverse of the 2x2 matrix and give it a name

{
    /*variable declarations*/
    int b, i, j;
    float a;
    char enter;

    /*sets name of 2x2 matrix*/
    printf("Enter one character name for the inverse matrix:\n");
    (*m3).name = getchar(); // scans the user's input and assigns it to the name variable
    while(!(((*m3).name>='A' && (*m3).name<='Z')||((*m3).name>='a' && (*m3).name<='z'))) // user must input an upper or lower case letter as the name of the matrix, otherwise they will be asked to input again
    {
        printf("character is invalid. Try again:\n");
        (*m3).name = getchar();
    }

    /*sets inverse matrix as a 2x2 matrix*/
    (*m3).nrows=2;
    (*m3).ncolumns=2;

    /*matches the elements in the 2x2 matrix to the positions in the 2x2 array that makes up the inverse matrix and changes them according to the definition of inverse matrix*/
    ((*m3).matrix[0][0])=(m2.matrix[1][1])/det;
    (*m3).matrix[1][1]=(m2.matrix[0][0])/det;
    (*m3).matrix[0][1]=(-m2.matrix[0][1])/det;
    (*m3).matrix[1][0]=(-m2.matrix[1][0])/det;
}




