#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "vector.h"

#define MAX_TRANSLATION_LENGTH 512 //the maximum number of characters a translated word can have
#define MAX_LINE_LENGTH 512        //the maximum number of characters a line in any of the input files can have
#define MAX_ALPHABET_LENGTH 256
#define MAX_STATES 256

#define LANGUAGE_AUTOMATON_FILENAME "Language Automaton.txt"
#define TRANSLATION_AUTOMATON_FILENAME "Translation Automaton.txt"
#define TEST_INPUTS_FILENAME "Test inputs.txt"

/*     int i;

    VECTOR_INIT(v);

    VECTOR_ADD(v, "Bonjour");
    VECTOR_ADD(v, "tout");
    VECTOR_ADD(v, "le");
    VECTOR_ADD(v, "monde");

    for (i = 0; i < VECTOR_TOTAL(v); i++)
        printf("%s ", VECTOR_GET(v, char *, i));
    printf("\n");

    VECTOR_DELETE(v, 3);
    VECTOR_DELETE(v, 2);
    VECTOR_DELETE(v, 1);

    VECTOR_SET(v, 0, "Hello");
    VECTOR_ADD(v, "World");

    for (i = 0; i < VECTOR_TOTAL(v); i++)
        printf("%s ", VECTOR_GET(v, char *, i));
    printf("\n");

    VECTOR_FREE(v);*/
int main()
{

    //Read the first character
    FILE *languageAutomatonFile, *translationAutomatonFile, *inputFile;
    languageAutomatonFile = fopen(LANGUAGE_AUTOMATON_FILENAME, "r");
    translationAutomatonFile = fopen(TRANSLATION_AUTOMATON_FILENAME, "r");
    inputFile = fopen(TEST_INPUTS_FILENAME, "r");

    int languageStates;                              //the total number of states in L
    int languageAlphabetLength;                      //the number of different symbols in the alphabet
    char *languageAlphabet[MAX_ALPHABET_LENGTH];     //the symbols accepted by L's Sigma
    bool *languageFinalStates[MAX_STATES];           //[true, false, true, false, false] makes q0 and q2 final
    char *languageAutomaton[MAX_STATES][MAX_STATES]; //matrix containing all the states' transitions

    int translationStates;
    char *translationAlphabet[MAX_ALPHABET_LENGTH];
    bool *translationFinalStates[MAX_STATES];
    char *translationAutomaton[MAX_STATES][MAX_STATES];

    char characterRead;

    fscanf(inputFile, "%c", &characterRead);
    //Set up language automata (it is horrible coding, but moving to a separate function is hard and this is not a C class)
    while (!feof(languageAutomatonFile))
    {
        int lineNumber = 0;
        if (characterRead == '\n')
        {
            //go on to next line LALALAL
            lineNumber++;
            continue;
        }
        if (characterRead == ' ')
        {
            //next word
            continue;
        }
        switch (lineNumber)
        {
        case 0:
            languageStates = characterRead - '0'; //converting to int, because C is cool like that
            break;
        case 1:
            languageAlphabetLength = characterRead - '0'; //converting to int, because C is cool like that
            break;
        case 2:
            if ((int)(sizeof(languageAlphabet) / sizeof(languageAlphabet[0])) <= 0)
            {
                *languageAlphabet = char[languageAlphabetLength];
            }
            break;
        default:
            break;
        }

        //Number of states
        //Alphabet
        //First Row
        //...
        //Last Row
        //Array of final states

        fscanf(inputFile, "%c", &characterRead);
    }
    while (!feof(translationAutomatonFile))
    {
        int lineNumber = 0;
        if (characterRead == '\n')
        {
            //go on to next line
            lineNumber++;
            continue;
        }
        if (characterRead == ' ')
        {
            //next word
        }

        //Number of states
        //Alphabet
        //First Row
        //...
        //Last Row
        //Array of final states

        fscanf(inputFile, "%c", &characterRead);
    }

    //translate each word
    while (!feof(inputFile))
    {
        //read each word and translate it
        char translatedWord[MAX_TRANSLATION_LENGTH];
        for (int i = 0; i < input.length(); i++)
        {
            //Check if the letter read (if any) is in L's alphabet

            //...

            //Check if translation's length is == 0, and if such a thing is accepted by T(M)
        }

        printf("");
    }
    return 0;
}
