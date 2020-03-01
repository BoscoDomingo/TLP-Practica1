#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TRANSLATION_LENGTH 512 //the maximum number of characters a translated word can have
#define MAX_LINE_LENGTH 512        //the maximum number of characters a line in any of the input files can have
#define MAX_ALPHABET_LENGTH 256    //Assuming spaces in between each character
#define MAX_STATES 256

#define AUTOMATON_FILENAME "Automaton.txt"

int main()
{
    FILE *automatonFile;
    automatonFile = fopen(AUTOMATON_FILENAME, "r");

    int states;                         //the total number of states in M
    int alphabetLength;                 //the number of different symbols in the alphabet
    char alphabet[MAX_ALPHABET_LENGTH]; //the symbols accepted by M's Sigma
    bool finalStates[MAX_STATES];       //[true, false, true, false, false] makes q0 and q2 final

    int delta[MAX_STATES][MAX_ALPHABET_LENGTH]; //Matrix containing states as rows, inputs as columns. With a given state we can know the state to go to next based on a given input
    char inputToIndex[MAX_ALPHABET_LENGTH];     //The code to turn a symbol from Sigma into an column index for the automaton. E.g. [a, x, y, z] | a = 0, x = 1 in the automaton matrix

    char translationStrings[MAX_STATES][MAX_ALPHABET_LENGTH][MAX_TRANSLATION_LENGTH]; //The matrix containing the translated string of each state given each input

    printf("\n***Creando el autómata...***\n");
    char characterRead;

    //Set up language automata (it is horrible coding, but moving to a separate function is hard and this is not a C course)
    //Number of states
    fscanf(automatonFile, "%c", &characterRead);
    printf("%c\n", characterRead);               //TO-DO DELETE
    states = characterRead - '0';                //convert to int, because C is cool like that
    fscanf(automatonFile, "%c", &characterRead); //\n

    //Number of elements in the alphabet
    fscanf(automatonFile, "%c", &characterRead);
    printf("%c\n", characterRead);                                //TO-DO DELETE
    alphabetLength = characterRead - '0';                         //converting to int, because C is cool like that
    char newAlphabet[alphabetLength];                             //WE NEED TO COPY THIS ARRAY INTO ALPHABET, since it is the right size and will contain the right letters
    int newDelta[states][alphabetLength];                         //We also need to resize delta since we now know the correct size of the alphabet and the number of states
    char newTranslation[states][alphabetLength][MAX_LINE_LENGTH]; //We also need to resize translations since we now know the correct size of the alphabet and the number of states
    fscanf(automatonFile, "%c", &characterRead);                  //\n

    //Alphabet setup
    int i = 0;
    fscanf(automatonFile, "%c", &characterRead); //first letter
    while (characterRead != "\n" && i < alphabetLength)
    {
        printf("%c\n", characterRead); //TO-DO DELETE
        newAlphabet[i] = characterRead;
        i++;
        fscanf(automatonFile, "%c", &characterRead); // next character
    }

    //Automaton setup
    fscanf(automatonFile, "%c", &characterRead); // [0][0] of the automaton
    for (i = 0; i < states; i++)
    {
        int j = 0;
        while (characterRead != "\n" && j < alphabetLength)
        {
            printf("%c\n", characterRead); //TO-DO DELETE
            if (characterRead == "_")
            {
                newDelta[i][j] = NULL;
            }
            else
            {
                newDelta[i][j] = characterRead - '0';
            }
            j++;
            scanf(automatonFile, "%c", &characterRead);  // space
            fscanf(automatonFile, "%c", &characterRead); // next character
        }
    }

    //Translation setup
    char stringRead[MAX_LINE_LENGTH];
    fscanf(automatonFile, "%c", &characterRead); // [0][0][0] of the translations
    for (i = 0; i < states; i++)
    {
        int j = 0;
        while (characterRead != "\n" && j < alphabetLength)
        {
            while (characterRead != " ")
            {
                printf("%c\n", characterRead);               //TO-DO DELETE
                strcat(stringRead, characterRead);           //add the character to the string
                fscanf(automatonFile, "%c", &characterRead); // next character
            }

            if (stringRead == "_")
            {
                newTranslation[i][j] = NULL;
            }
            else
            {
                newTranslation[i][j] = characterRead - '0';
            }
            j++;
            scanf(automatonFile, "%c", &characterRead);  // space
            fscanf(automatonFile, "%c", &characterRead); // next character
        }
    }
    fscanf(automatonFile, "%c", &characterRead); // next character

    //Final states
    i = 0;
    while (characterRead != "\n" && i < alphabetLength)
    {
        printf("%c\n", characterRead); //TO-DO DELETE
        newAlphabet[i] = characterRead;
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
            if (currentRow == NULL)
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