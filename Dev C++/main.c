#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TRANSLATION_LENGTH 512 //the maximum number of characters a translated word can have
#define MAX_LINE_LENGTH 512        //the maximum number of characters a line in any of the input files can have

#define AUTOMATON_FILENAME "Automaton.txt"

int main()
{
    FILE *automatonFile;
    automatonFile = fopen(AUTOMATON_FILENAME, "r");

    if (automatonFile == NULL)
    {
        printf("Error abriendo el fichero\n");
        exit(1);
    }

    printf("\n***Creando el autómata...***\n");
    char characterRead;

    //Set up language automata (it is horrible coding, but moving to a separate function is hard and this is not a C course)
    //Number of states
    fscanf(automatonFile, "%c", &characterRead);
    printf("%c\n", characterRead);               //TO-DO DELETE
    int numberOfStates = characterRead - '0';    //the total number of states in M. "-'0'" is to convert to int, because C is cool like that
    fscanf(automatonFile, "%c", &characterRead); //\n

    //Number of elements in the alphabet
    fscanf(automatonFile, "%c", &characterRead);
    printf("%c\n", characterRead);            //TO-DO DELETE
    int alphabetLength = characterRead - '0'; //the number of different symbols in the alphabet

    //We create all the necessary structures
    int delta[numberOfStates][alphabetLength]; //Matrix containing states as rows, inputs as columns. With a given state we can know the state to go to next based on a given input

    char alphabet[alphabetLength],                                           //the symbols accepted by M's Sigma
        translationStrings[numberOfStates][alphabetLength][MAX_LINE_LENGTH], //The matrix containing the translated string of each state given each input
        inputToIndex[alphabetLength];                                        //The code to turn a symbol from Sigma into an column index for the automaton. E.g. [a, x, y, z] | a = 0, x = 1 in the automaton matrix

    bool finalStates[numberOfStates]; //[true, false, true, false, false] makes q0 and q2 final

    fscanf(automatonFile, "%c", &characterRead); //\n

    //Alphabet setup
    int i = 0;
    fscanf(automatonFile, "%c", &characterRead); //first letter
    while (characterRead != '\n' && i < alphabetLength)
    {
        printf("%c", characterRead); //TO-DO DELETE
        alphabet[i] = characterRead;
        i++;
        fscanf(automatonFile, "%c", &characterRead); // next character
    }
    printf("\n"); //TO-DO DELETE

    //Automaton setup
    fscanf(automatonFile, "%c", &characterRead); // [0][0] of the automaton
    for (i = 0; i < numberOfStates; i++)
    {
    	printf("i vale: %d\n", i);
        int j = 0;
        while (characterRead != '\n' && j < alphabetLength)
        {
        	printf("\nj vale: %d\n", j);
            printf("%c\n", characterRead); //TO-DO DELETE
            if (characterRead == '_')
            {
                delta[i][j] = -1;
            }
            else
            {
                delta[i][j] = characterRead - '0';
            }
            j++;
            scanf(automatonFile, "%c", &characterRead);  // space
            fscanf(automatonFile, "%c", &characterRead); // next character
        }
    }
    fscanf(automatonFile, "%c", &characterRead); // 2nd \n

    /*Translation setup*/
    char stringRead[MAX_LINE_LENGTH];
    fscanf(automatonFile, "%c", &characterRead); // [0][0][0] of the translations
    for (i = 0; i < numberOfStates; i++)         //for each row
    {
        int j = 0;
        while (characterRead != '\n' && j < alphabetLength) //for each column
        {
            while (characterRead != ' ') //create the new string
            {
                printf("%c\n", characterRead);               //TO-DO DELETE
                strcat(stringRead, characterRead);           //add the character to the string
                fscanf(automatonFile, "%c", &characterRead); // next character
            }

            if (stringRead == "_")
            {
                strcpy(translationStrings[i][j], NULL);
            }
            else
            {
                strcpy(translationStrings[i][j], stringRead);
            }
            j++;
            fscanf(automatonFile, "%c", &characterRead); // next character
        }
    }

    //Final states
    fscanf(automatonFile, "%c", &characterRead); // next character
    i = 0;
    while (characterRead != '\n' && i < numberOfStates)
    {
        printf("%c\n", characterRead); //TO-DO DELETE
        finalStates[i] = characterRead == '1' ? true : false;
        i++;
        fscanf(automatonFile, "%c", &characterRead); // next character
    }

    fclose(automatonFile);
    printf("\nAutómata configurado con éxito");

    //Read word and translate
    char inputWord[MAX_LINE_LENGTH];
    printf("\nPor favor, introduce una palabra con la que probar (máximo %d caracteres) y presiona ENTER. Para salir, introduce \"*SALIR*\":\n", MAX_LINE_LENGTH);
    scanf("%s", &inputWord);
    while (inputWord != "*SALIR*")
    { //translate entered word
        char translatedWord[MAX_TRANSLATION_LENGTH] = {};
        int i = 0; //index for the input word, to traverse it fully

        int currentRow = 0;             //current state
        int currentCol = 0;             //current input's index
        bool correctTranslation = true; //if false, indicates the program had to stop prematurely
        while (inputWord[i] != '\0' && correctTranslation)
        {
            if (strchr(alphabet, inputWord[i]) == NULL) //Check if the letter read is in the alphabet
            {
                printf("\nLo sentimos, has introducido un caracter no aceptado. Prueba de nuevo.");
                correctTranslation = false;
                break;
            }

            char tempChar = strchr(inputToIndex, inputWord[i]); //Never NULL since we already checked for that
            currentCol = (int)(tempChar - *inputToIndex);       //To get the index of inputWord[i], because C is cool like that
            printf("\n\tcurrentCol ahora es: %d", currentCol);  //TO-DO DELETE

            if (translationStrings[currentRow][currentCol] != NULL) //An input may be valid but generate an empty translation
            {
                printf("\n\tLa traducción es: %s", (translationStrings[currentRow][currentCol])); //TO-DO DELETE
                strcat(translatedWord, translationStrings[currentRow][currentCol]);               //concatenate the translation
            }

            currentRow = delta[currentRow][currentCol]; //Se cambia de estado
            if (currentRow == -1)
            { //Transición no posible
                printf("\nLo sentimos, has introducido una palabra no aceptada. Prueba de nuevo.");
                correctTranslation = false;
                break;
            }
            //get the next letter
            i++;
        }

        if (correctTranslation && finalStates[currentRow])
        {
            printf("\nLa traducción es: %s", translatedWord);
        }
        else if (!finalStates[currentRow]) //the current state is not final
        {
            printf("\nLo sentimos, la palabra no está aceptada por el lenguaje.");
        }

        printf("\nPor favor, introduce la siguiente palabra con la que probar (máximo %d caracteres) y presiona ENTER. Para salir, introduce \"*SALIR*\":\n", MAX_LINE_LENGTH);
        scanf("%s", &inputWord);
    }
    printf("Saliendo. Gracias por usar nuestro software.");
    return 0;
}
