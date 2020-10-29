///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FileName: Assignment.es                                                                                                                                                                                    //
//Description: Program that prints user's input to a file and calculates the count and sum of the numbers amongst the characters that the user inputs.                                                                                   //
//Written by Jane Malalane, November 2019                                                                                                                                                                     //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*header file declaration*/
#include <stdio.h>

/*function declaration*/
float mean(float sum, float N);                                         //"mean" function
int main()                                                              //main function
{
    /* variable declaration*/
    char charactersin;

    /*declaration of pointer to the file stream*/
    FILE *fin;

    fin=fopen("File1.txt", "w");                                        //opens file to write
    printf("Type in characters in a line with no spaces: ");            //asks for user's input
    while(charactersin!=0x0A)                                           //loop is executed while the user doesn't press the the "enter" key
    {
        scanf("%c", &charactersin);                                     //scans the user's input and assigns it to the previously declared variable
        fprintf(fin,"%c", charactersin);                                //prints the user's input to a separate file (Filel)
    }
    fclose(fin);                                                        //closes File1
    /* variable declaration*/
    int  N = 0;                                                         //number of numbers
    int sumch = 0;                                                      //sum of the numbers
    char charactersout;                                                 //scanned characters from File1

    fin=fopen("File1.txt","r");                                         //opens file to read
    if(fin==NULL)                                                       //if the file is not found, a null pointer is returned from fopen
    {
       printf("File1 is not in folder, aborting program\n");
    }
    else
    {
       printf("Numbers found in the file:\n");
       while(fscanf(fin, "%c", &charactersout)!=EOF)                    //loop is executed up until the last character in the file is scanned
        {
            if (charactersout >= 0x030 && charactersout <= 0x039)       //the following three statements are only executed if the character scanned is a digit from 0 to 9
            {
                printf("%c\n",charactersout);                           //prints out the numbers found in the file
                N = N + 1;                                              //as each number is scanned, the number of numbers is increased by 1 value
                sumch = sumch + charactersout;                          //as each number is scanned, its value is added to the sum
            }
        }
            /* variable declaration*/
            int sum = sumch - 48*N;                                      //expression that converts the sum of the numbers from a decimal to its equivalent sum in characters, that depends on the number of numbers
            float meanvalue;                                             //mean of the numbers
            meanvalue = mean(sum,N);                                     //"mean" function call

            printf("#numbers = %d \n", N);                               //displays the number of numbers
            printf("sum = %d\n", sum);                                   //displays the sum of the numbers
            if (N != 0)
                {printf("mean = %.2f", meanvalue);}                      //displays the mean of the numbers, if there are numbers in the file
            else
                {printf("mean is undefined");}                           //if there are no numbers, there is no mean
    }
}

float mean(float sum, float N)                                           //function of sum of the numbers and number of numbers to compute mean, as mean is equal to the sum of the numbers divided by the number of numbers
{
    return(sum/N);
}







