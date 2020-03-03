#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TRANSLATION_LENGTH 512 //the maximum number of characters a translated word can have
#define MAX_LINE_LENGTH 512        //the maximum number of characters a line in any of the input files can have


int getAlphabetIndex(char alphabet[], char input);

int main() {
	
	int option;
	do{
		do{		
			system("cls");
			printf("-----------------------------     PRACTICA 1 TLP     -----------------------------\n\n\n");
			printf("1. Lenguaje A: L = {a(b^n)a: n>=0}, T(M) = {c^(n+3): n>=1})\n"); 	
			printf("2. Lenguaje B: L = {(a^n)b(ca)^(2k)w: n,k>=0,w en {a,b}*}, T(M) = {1(0^(k+1))(1^m): k>=0,m=|m|}\n"); 	
			printf("3. Lenguaje C: L = {w en {a,b}*: w no termina en b}, T(M) = {x en {0,1}*: el valor en binario de x es par}\n"); 	
			printf("0. Salir\n");
		
			printf("\nIntroduzca la opcion deseada: ");
			scanf("%d",&option);
			if((option<0)||(option>3)){
				printf("Opcion no valida\n");
				system("PAUSE");
			}
		}while((option<0)||(option>3));
		
		if(option == 0){
			exit(1);
		}
			
		char stringOption[2] = {('0' + option)};		//Convertimos la opcion elegida a un string para concatenarlo al nombre del archivo
		char fileName[MAX_LINE_LENGTH] = "Automaton";
		strcat(fileName,stringOption);
		strcat(fileName,".txt");
		
		//Abrimos el archivo que contiene el autómata elegido
		FILE *automatonFile;
		automatonFile = fopen(fileName, "r");
		
		if (automatonFile == NULL) {
			printf("Error abriendo el fichero\n");
			exit(1);
		}

		printf("\n***\tCreando el automata...\t***\n");
		char characterRead;
		
		//Set up language automata
	
		//Number of states
		fscanf(automatonFile, "%c", &characterRead);
		printf("Numero de estados del automata: %c\n", characterRead);
		int numberOfStates = characterRead - '0';    //the total number of states in M. "-'0'" is to convert to int, because C is cool like that
		fscanf(automatonFile, "%c", &characterRead); //\n

		//Number of elements in the alphabet
		fscanf(automatonFile, "%c", &characterRead);
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
		printf("Alfabeto: ");
		fscanf(automatonFile, "%c", &characterRead); //first letter
		while (characterRead != '\n' && i < alphabetLength) {
			printf("%c ", characterRead); //TO-DO DELETE
			alphabet[i] = characterRead;
			i++;
			fscanf(automatonFile, "%c", &characterRead); // next character
		}
		printf("\n"); //TO-DO DELETE
	
		//Automaton setup
		fscanf(automatonFile, "%c", &characterRead); // [0][0] of the automaton
		for (i = 0; i < numberOfStates; i++) {
			int j = 0;
			while (characterRead != '\n' && j < alphabetLength) {
				if (characterRead == '_') {
					delta[i][j] = -1;
				} else {
					delta[i][j] = characterRead - '0';
				}
				j++;
				fscanf(automatonFile, "%c", &characterRead);  // space
				fscanf(automatonFile, "%c", &characterRead); // next character
			}
		}
	
		//Translation setup
		char stringRead[MAX_LINE_LENGTH] = "";
		int j = 0;
		fscanf(automatonFile, "%c", &characterRead); // [0][0][0] of the translations
		for (i = 0; i < numberOfStates; i++) {       //for each row
			int j = 0;
			while (characterRead != '\n' && j < alphabetLength) { //for each column
				while ((characterRead != ' ') && (characterRead != '\n')) { //create the new string
					char characterReadString[2] = {characterRead};
					strcat(stringRead, characterReadString);           //add the character to the string	PETA PORQUE EL SEGUNDO PARÁMETRO HA DE SER UN STRING
					fscanf(automatonFile,"%c", &characterRead); // next character
				}
				if (stringRead == "_") {
					strcpy(translationStrings[i][j], NULL);
				} else {
					strcpy(translationStrings[i][j], stringRead);
				}
				memset(stringRead, 0, MAX_LINE_LENGTH );		//Vaciamos el string
				j++;
				fscanf(automatonFile, "%c", &characterRead); // next character
			}
		}
	
		//Final states
		fscanf(automatonFile, "%c", &characterRead); // next character
		i = 0;
		while (characterRead != '\n' && i < numberOfStates) {
			finalStates[i] = characterRead == 't' ? true : false;
			i++;
			fscanf(automatonFile, "%c", &characterRead); // next character
		}
	
		//Show final states
		printf("\nEstados finales: ");
		for(i=0; i<numberOfStates; i++) {
			if(finalStates[i])
				printf("Q%d ",i);
		}
		
		fclose(automatonFile);
		printf("\n\n***\tAutomata configurado con exito\t***\n\n");
		

		//Read word and translate
	
		char inputWord[MAX_LINE_LENGTH];
		
		do{ 
			system("cls");
			printf("-----------------------------     PRACTICA 1 TLP     -----------------------------\n\n\n");
			switch(option){
				case 0:
					break;
				case 1: 
					printf("Lenguaje A: L = {a(b^n)a: n>=0}, T(M) = {c^(n+3): n>=1})\n"); 	
					break;
				case 2:
					printf("Lenguaje B: L = {(a^n)b(ca)^(2k)w: n,k>=0,w en {a,b}*}, T(M) = {1(0^(k+1))(1^m): k>=0,m=|m|}\n"); 
					break;	
				case 3:
					printf("Lenguaje C: L = {w en {a,b}*: w no termina en b}, T(M) = {x en {0,1}*: el valor en binario de x es par}\n"); 
					break;
				default:
					break;
			}
		
			printf("\nIntroduzca una palabra(maximo %d caracteres) y presione ENTER. \nPara volver al menu principal, introduzca \"*ATRAS*\".\nPara salir, introduzca \"*SALIR*\". \nPalabra: ", MAX_LINE_LENGTH);
			scanf("%s", &inputWord);
			printf("\n");		

			//translate entered word
			char translatedWord[MAX_TRANSLATION_LENGTH] = {};
			int i = 0; //index for the input word, to traverse it fully	

			int currentRow = 0;             //current state
			int currentCol = 0;             //current input's index
			bool correctTranslation = true; //if false, indicates the program had to stop prematurely
			
			if((strcmp(inputWord,"*SALIR*"))&&(strcmp(inputWord,"*ATRAS*"))){
				while (inputWord[i] != '\0' && correctTranslation) {
		
					if (getAlphabetIndex(alphabet,inputWord[i]) == -1) { //Check if the letter read is in the alphabet
						printf("Ha introducido un caracter que no forma parte del lenguaje.\n");
						correctTranslation = false;
						break;
					}
	
					currentCol = getAlphabetIndex(alphabet,inputWord[i]);
	
					if (translationStrings[currentRow][currentCol] != NULL && strcmp(translationStrings[currentRow][currentCol],"_") != 0) { //An input may be valid but generate an empty translation
						strcat(translatedWord, translationStrings[currentRow][currentCol]); //concatenate the translation
					}
	
					currentRow = delta[currentRow][currentCol]; //Move to next state
					if (currentRow == -1) {
						//transition not possible
							printf("La palabra introducida no esta dentro del lenguaje.\n");
						correctTranslation = false;
						break;
					}
					//get the next letter
					i++;
				}	
		
				if (correctTranslation && finalStates[currentRow]) {
					printf("La traduccion es: %s\n", translatedWord);
				} 
					else if (!finalStates[currentRow]) { //the current state is not final
					printf("La palabra introducida no esta dentro del lenguaje.\n");
				}
				printf("\n\n\n\n");
				system("PAUSE");
				
			}
		}while((strcmp(inputWord,"*SALIR*"))&&(strcmp(inputWord,"*ATRAS*")));		//Checks for *SALIR*
		
		if(!strcmp(inputWord,"*SALIR*"))
			option = 0;
						
	}while(option!=0);
	
	printf("\n\nSaliendo. Gracias por usar nuestro software.");
	return 0;
}

//Obtain index for the language matrix of a given input
int getAlphabetIndex(char alphabet[], char input) {
	int i=0;
	int found = 0;
	while(!found && i<strlen(alphabet)) {
		if(input == alphabet[i]) {
			found = 1;
		} else i += 1;
	}

	if(!found) i = -1;

	return i;
}
