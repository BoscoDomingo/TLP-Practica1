#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_TRANSLATION_LENGTH 500 //the maximum number of characters a translated word can have
#define MAX_ALPHABET_LENGTH 500    //the maximum number of symbols an alphabet can have

char input[] = {'c', 'a'};
int languageStates;         //the total number of states in L
char languageAlphabet[];    //the symbols accepted by L's Sigma
bool languageFinalStates[]; //[true, false, true, false, false] makes q0 and q2 final
char languageAutomaton[][]; //matrix containing all the states' transitions
bool isLanguageAutomatonReady = false;

int translationStates;
char translationAlphabet[];
bool translationFinalStates[];
char translationAutomaton[][];
bool isTranslationAutomatonReady = false;

int main()
{
    //Read the file
    FILE *inputFile;
    inputFile = fopen("input.txt", "r");
    char characterRead;
    fscanf(inputFile, "%c", &characterRead);
    //Set up automata (moving to a separate function is hard)
    while (!isLanguageAutomatonReady || !isTranslationAutomatonReady)
    {
        if (characterRead == ' ')
        {
            //next word
        }
        if (characterRead == '\n')
        {
            //next line
        }
        //Alphabet
        //Number of states
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
    }
    char translation[MAX_TRANSLATION_LENGTH];
    for (int i = 0; i < input.length(); i++)
    {
        //Check if the letter read (if any) is in L's alphabet

        //...

        //Check if translation's length is == 0, and if such a thing is accepted by T(M)
    }

    printf("");
    return 0;
}