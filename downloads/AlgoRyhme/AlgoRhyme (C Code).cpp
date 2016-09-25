//      ___     __               ____   __                          
//     /   |   / /____ _ ____   / __ \ / /_   __  __ ____ ___   ___ 
//    / /| |  / // __ `// __ \ / /_/ // __ \ / / / // __ `__ \ / _ \
//   / ___ | / // /_/ // /_/ // _, _// / / // /_/ // / / / / //  __/
//  /_/  |_|/_/ \__, / \____//_/ |_|/_/ /_/ \__, //_/ /_/ /_/ \___/ 
//             /____/                      /____/                   
//
//                  By Alexandre Pana & Kenta Morris
//                   Completed on January 22, 2016
//						Tested in Dev-C++ 5.9.2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <conio.h>
#include <time.h>

#define MAX_WORD_LEN 50
#define MAX_SENTENCE_CHARS 400
#define MAX_SENTENCE_WORDS 20
#define MAX_PHONES 20
#define MAX_PHONE_CHARS 4
#define PHONES_REQ 5
#define PHONES_NUM 38
#define MAX_SPEECH_WORDS 2000

#define NOUN_Syntaxes 11
#define MAX_Syntaxes 13

#define MIN_CHAR 'a'
#define MAX_CHAR 'z'

#define SPACE_SIGN ' '
#define NEWLINE_SIGN '\n'
#define Gen_Char ' '
#define Clear_Char 'c'
#define Save_Char 's'
#define Quit_Char 'x'

//Change these if you want verses to be longer
#define MIN_RHYMES 2
#define MAX_RHYMES 4

int rb (int min, int max)
{
    return rand() % (max - min + 1) + min;
}

enum speechType {NOUN, ADJ, ADV, VERB, PREP, CONJ,PRO, UNDEFINED};                          //Part of speech type
const char *SPEECHTYPE[] = {"NOUN", "ADJ", "ADV","VERB", "PREP","CONJ","PRO","UNDEFINED"};  //String for parsing parts of speech

enum phoneType {AA, AE, AH, AO, AW, AY, B, CH, D, DH, EH, ER, EY, F, G, HH, IH, IY, JH, K, L, M, N, NH, OW, OY, P, R, S, SH, T, TH, UH, UW, V, W, Y, Z, ZH};    //Every phonetic
const char *PHONETYPE[] = {"AA", "AE", "AH", "AO", "AW", "AY", "B", "CH", "D", "DH", "EH", "ER", "EY", "F", "G", "HH", "IH", "IY", "JH", "K", "L", "M", "N", "NH", "OW", "OY", "P", "R", "S", "SH", "T", "TH", "UH", "UW", "V", "W", "Y", "Z", "ZH"};

typedef struct wordType{            //Word structure
    char name [MAX_WORD_LEN];       //The actual word
    speechType type;                //What part of speech it is
    phoneType phone[MAX_PHONES];    //All of its phonetics
    int phoneNum;                   //Amount of phonetics
}wordType;

class Sentence {                    //Sentence Class, which is actually comprised of a string with 2-5 sentences that rhyme together
      private:       
          int syntax;
          wordType rhymingWord[MAX_RHYMES];
          int sentenceAmount;
          void chooseRhymeWords();
          int chooseSyntax(speechType);
          char* chooseWord(speechType);
      public:
          char string[MAX_SENTENCE_CHARS];
        
          wordType Noun[MAX_SPEECH_WORDS];
          int nounSize;
          wordType Adj[MAX_SPEECH_WORDS];         //Replace the title of these with "NounArray"...
          int adjSize;
          wordType Adv[MAX_SPEECH_WORDS];
          int advSize;
          wordType Verb[MAX_SPEECH_WORDS];
          int verbSize;
          wordType Prep[MAX_SPEECH_WORDS];
          int prepSize;
          wordType Conj[MAX_SPEECH_WORDS];
          int conjSize;
          wordType Pro[MAX_SPEECH_WORDS];
          int proSize;
          
          void createString();
          void print() {printf("%s\n", string);}
};

void FisherYatesShuffle(wordType *array, int n) {    //Generates a random permutation of an array.
    int i, j;                                        //Used to make sure that the rhyme searching doesn't check a word more than once
    wordType temp;
    
    for (i = n - 1; i > 0; i--) {
        j = rb(0, i + 1);
        temp = array[j];
        array[j] = array[i];
        array[i] = temp;
    }
}


bool checkRhymingWords(wordType *word, int n){    //Makes sure that none of the words are the same and that they rhyme.
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= i; j++){
        
            if ( i != j && !strcmp(word[i].name, word[j].name))    //Checks if the words are the same
                return false;
            else{
                for (int k = 0; k < PHONES_REQ; k++){            //Checks if their ending phonetics are the same
                    if ((word[i].phoneNum - k) < 0)
                        return false;
                    if (word[i].phone[word[i].phoneNum - k] != word[j].phone[word[j].phoneNum - k])
                        return false;
                }
            }
        }
    }
    
    return true;
}

void Sentence::chooseRhymeWords(){
    int temp;
    int nounCounter;
    int adjCounter;
    bool rhymingCheck;
    sentenceAmount = rb (MIN_RHYMES, MAX_RHYMES);       //Chooses how many sentence it's going to make rhyme
    
    do{
        FisherYatesShuffle(Noun, nounSize);
        FisherYatesShuffle(Adj, adjSize);
        nounCounter = 0;
        adjCounter = 0;
        
        temp = rb(0, 1);	//Chooses randomly between a noun or adjective
        
        // ----------------------- Chooses First Word
        if (temp == 0){        //Random Noun
            rhymingWord[0] = Noun[rb(0, nounSize)];
            rhymingWord[0].type = NOUN;
        }
        else {                //Random adjective
            rhymingWord[0] = Adj[rb(0, adjSize)];
            rhymingWord[0].type = ADJ;
        }
        
        
        // ----------------------- Chooses all subsequent words
        for (int i = 1; i < sentenceAmount; i++){
            do{
                temp = rb(0, 1);        //Again, only chooses between nouns and adjectives
                
                if (temp == 0){
                    rhymingWord[i] = Noun[nounCounter];
                    rhymingWord[i].type = NOUN;
                    nounCounter++;
                }
                else{
                    rhymingWord[i] = Adj[adjCounter];
                    rhymingWord[i].type = ADJ;
                    adjCounter++;
                }
                
                rhymingCheck = checkRhymingWords(rhymingWord, i);
            } while (!rhymingCheck && (nounCounter < nounSize || adjCounter < adjSize));	//Exits once all the words rhyme or the end of the array has been reached
        }
        
    } while (nounCounter >= nounSize && adjCounter >= adjSize);	//Keeps rerolling all the words until they all rhyme
    
}


int Sentence::chooseSyntax (speechType end) {
    if (end == NOUN)             	//There are only two options so a case and switch is not needed
        return rb(1, NOUN_Syntaxes);
    else if (end == ADJ)
        return rb(NOUN_Syntaxes+1, MAX_Syntaxes);
    else
        return 0;
}


char* Sentence::chooseWord(speechType partOfSpeech){	//Returns a random word depending on what part of speech is needed
    
    char *str = (char *) malloc(sizeof(char) * 3);
     
    switch(partOfSpeech){
        case NOUN:
            strcpy(str, Noun[rb(0, nounSize)].name);
            break;
        case ADJ:
            strcpy(str, Adj[rb(0, adjSize)].name);
            break;
        case ADV:
            strcpy(str, Adv[rb(0, advSize)].name);
            break;
       case VERB:
            strcpy(str, Verb[rb(0, verbSize)].name);
            break;
       case PREP:
            strcpy(str, Prep[rb(0, prepSize)].name);
            break;
       case CONJ:
            strcpy(str, Conj[rb(0, conjSize)].name);
            break;
       case PRO:
            strcpy(str, Pro[rb(0, proSize)].name);
            break;
        default:
            strcpy(str, "error");
            break;
    }
    
    return str;
}


char* capitalize(char *s){
    char *str = (char *) malloc(sizeof(char) * 3);
    strcpy (str, s);
    if (str[0] >= MIN_CHAR && str[0] <= MAX_CHAR)
        str[0] = str[0] - 32;                   //Hard coded because this will never, ever have to change
    return str;
}

void Sentence::createString (){
    string[0]=0;    //flushes out previous string
    chooseRhymeWords();
    
    for (int i = 0; i < sentenceAmount; i++){
        
        syntax = chooseSyntax (rhymingWord[i].type);    //Picks a random syntax depending on what kind of word the rhyming one is
        
        switch(syntax){
            case 1:                //1> [Proper noun] [adj]ly [verb] your [adj] [noun]
                strcat (string, capitalize(chooseWord(PRO)));
                strcat (string, " ");
                strcat (string, chooseWord(ADJ));
                strcat (string, "ly ");
                strcat (string, chooseWord(VERB));
                strcat (string, "s ");
                strcat (string, "your ");
                strcat (string, chooseWord(ADJ));
                strcat (string, " ");
                break;
            case 2:                 //2> Your [noun] will [verb] [adj] [noun]
                strcat (string, "Your ");
                strcat (string, chooseWord(NOUN));
                strcat (string, " will ");
                strcat (string, chooseWord(VERB));
                strcat (string, " ");
                strcat (string, chooseWord(ADJ));
                strcat (string, " ");
                break;
            case 3:                 //3> Sometimes, I [verb] [adj] [noun] [prep] [noun]
                strcat (string, "Sometimes, I ");
                strcat (string, chooseWord(VERB));
                strcat (string, " ");
                strcat (string, chooseWord(ADJ));
                strcat (string, " ");
                strcat (string, chooseWord(NOUN));
                strcat (string, " ");
                strcat (string, chooseWord(PREP));
                strcat (string, " ");
                break;
            case 4:                 //4> [Pronoun] likes to [verb] [preposition] [adj] [noun]
                strcat (string, capitalize(chooseWord(PRO)));
                strcat (string, " likes to ");
                strcat (string, chooseWord(VERB));
                strcat (string, " ");
                strcat (string, chooseWord(PREP));
                strcat (string, " ");
                strcat (string, chooseWord(ADJ));
                strcat (string, " ");
                break;
            case 5:                 //5> Your [noun] [verb]s [preposition] [adjx?] [noun]
                strcat (string, "Your ");
                strcat (string, chooseWord(NOUN));
                strcat (string, " ");
                strcat (string, chooseWord(VERB));
                strcat (string, "s ");
                strcat (string, chooseWord(PREP));
                strcat (string, " ");
                strcat (string, chooseWord(ADJ));
                strcat (string, " ");
                break;
            case 6:                 //6> A [noun] might [verb] a [adjx?] [noun]
                strcat (string, "A ");
                strcat (string, chooseWord(NOUN));
                strcat (string, " might ");
                strcat (string, chooseWord(VERB));
                strcat (string, " a ");
                strcat (string, chooseWord(ADJ));
                strcat (string, " ");
                break;
            case 7:                 //7> A [noun] [adj]ly [verb]s [preposition] a [noun]
                strcat (string, "A ");
                strcat (string, chooseWord(NOUN));
                strcat (string, " ");
                strcat (string, chooseWord(ADJ));
                strcat (string, "ly ");
                strcat (string, chooseWord(VERB));
                strcat (string, "s ");
                strcat (string, chooseWord(PREP));
                strcat (string, " a ");
                break;
            case 8:                 //8> [conjunction] [pronoun] [adj]ly [verb]s a [adj] [noun]
                strcat (string, capitalize(chooseWord(CONJ)));
                strcat (string, " ");
                strcat (string, chooseWord(PRO));
                strcat (string, " ");
                strcat (string, chooseWord(ADJ));
                strcat (string, "ly ");
                strcat (string, chooseWord(VERB));
                strcat (string, "s a ");
                strcat (string, chooseWord(ADJ));
                strcat (string, " ");
                break;
            case 9:                 //9> [conjunction] your [adj] [noun] is a [adj] [noun]
                strcat (string, capitalize(chooseWord(CONJ)));
                strcat (string, " your ");
                strcat (string, chooseWord(ADJ));
                strcat (string, " ");
                strcat (string, chooseWord(NOUN));
                strcat (string, " is a ");
                strcat (string, chooseWord(ADJ));
                strcat (string, " ");
                break;
            case 10:                 //10>[preposition] a [verb], [preposition] a [noun]
                strcat (string, capitalize(chooseWord(PREP)));
                strcat (string, " a ");
                strcat (string, chooseWord(NOUN));
                strcat (string, " that ");
                strcat (string, chooseWord(VERB));
                strcat (string, "s ");
                strcat (string, chooseWord(PREP));
                strcat (string, " a ");
                break;
            case 11:				//11> I bet you [verb] [noun]s, you [adj] [noun]
            	strcat (string, "I bet you ");
            	strcat (string, chooseWord(VERB));
                strcat (string, " ");
            	strcat (string, chooseWord(NOUN));
            	strcat (string, "s, you ");
            	strcat (string, chooseWord(ADJ));
                strcat (string, " ");
            	break;
            case 12:				//11> Your [noun] is [adverb] [adj]
            	strcat (string, "Your ");
            	strcat (string, chooseWord(NOUN));
            	strcat (string, " is ");
            	strcat (string, chooseWord(ADV));
            	strcat (string, " ");
            	break;
            case 13:				//12> Most [noun]s are [adverb] [adj]
            	strcat (string, "Most ");
            	strcat (string, chooseWord(NOUN));
            	strcat (string, "s are ");
            	strcat (string, chooseWord(ADV));
            	strcat (string, " ");
            	break;
            default:
                strcat(string, "Error 404: Syntax not found.");
                break;
        }
        strcat (string, rhymingWord[i].name);	//adds the rhyme to the end of the sentence
        strcat (string, "\n");
    }
}

int nameParse(wordType *word,char *s){
    int i=0;
    while(s[i]!=SPACE_SIGN){
        word->name[i]=s[i];
        i++;
    }
    word->name[i]=0;
    return i;
}

void phoneParse(wordType *word, char *s,int i){
    word->phoneNum=0;
    int k=0;
    char tempstr[MAX_PHONE_CHARS];
    
    i++;//skips extra space
    while(s[i]!=NEWLINE_SIGN){
        i++;
        while (s[i]!=SPACE_SIGN && s[i]!=NEWLINE_SIGN){
            tempstr[k]=s[i];
            i++;
            k++;
        }
        tempstr[k]=0;//null terminates
        
        for (int n=0;n<PHONES_NUM;n++){//rotates through all possible enum types until a math is found
            if (!strcmp(tempstr,PHONETYPE[n])){
                word->phone[word->phoneNum] = (phoneType)n;
                break;
            }
        }
        
        k=0;
        word->phoneNum++;
    }
    word->phoneNum--;
    
}

void wordParse(wordType *word, speechType type, int *size){
    FILE *dicFile;
    
    switch (type){          //decides which file to read from
        case NOUN : {
            dicFile = fopen("noun_dic.txt","r");
            break;
        }
        case ADJ : {
            dicFile = fopen("adj_dic.txt","r");
            break;
        }
        case ADV : {
            dicFile = fopen("adv_dic.txt","r");
            break;
        }
        case VERB : {
            dicFile = fopen("verb_dic.txt","r");
            break;
        }
        case PREP : {
            dicFile = fopen("prep_dic.txt","r");
            break;
        }
        case CONJ : {
            dicFile = fopen("conj_dic.txt","r");
            break;
        }
        case PRO : {
            dicFile = fopen("pro_dic.txt","r");
            break;
        }
    }
    int i=0;
    int nameLen=0;
    char tempstr[100];
    while(fgets (tempstr,100,dicFile) != NULL) {
        nameLen = nameParse(&word[i],tempstr);
        phoneParse(&word[i],tempstr, nameLen);      //nameLen alows the counter to skip past the name when parsing phonetics
        
        /*                                  //This part prints everything that it reads from the files
        printf("%s ",word[i].name);
        for(int n=0;n<=word[i].phoneNum;n++){
            printf("%s ",PHONETYPE[word[i].phone[n]]);
        }
        printf("\n");
        */
        i++;
        
    }
    
    (*size)=i-1;
}

void drawChar (char c, int n){
    for (int i = 0; i < n; i++)
        printf("%c", c);
}

void showMenu(){            //Main Menu
    int indent = 6;
    int titleWidth = 66;
    
    //Title
    drawChar(' ', indent);
    drawChar(201, 1);
    drawChar(205, titleWidth-2);
    drawChar(187, 1);
    printf("\n");
    printf("     %c%c    ___     __               ____   __                          %c%c \n", 201, 188, 200, 187);
    printf("     %c    /   |   / /____ _ ____   / __ \\ / /_   __  __ ____ ___   ___  %c\n", 186, 186);
    printf("     %c   / /| |  / // __ `// __ \\ / /_/ // __ \\ / / / // __ `__ \\ / _ \\ %c\n", 186, 186);
    printf("     %c  / ___ | / // /_/ // /_/ // _, _// / / // /_/ // / / / / //  __/ %c\n", 186, 186);
    printf("     %c /_/  |_|/_/ \\__, / \\____//_/ |_|/_/ /_/ \\__, //_/ /_/ /_/ \\___/  %c\n", 186, 186);
    printf("     %c%c           /____/                      /____/                   %c%c\n", 200, 187, 201, 188);
    drawChar(' ', indent);
    drawChar(200, 1);
    drawChar(205, titleWidth-2);
    drawChar(188, 1);
    
    //Credits
    printf("\n\n\n");
    printf("\t\t      By Alexandre Pana & Kenta Morris\n");
    printf("\n\n\n\n\n\n\n");
    printf("\t\t\t   Press any key to begin.\n\n");
    printf("\t\t\t\t     ");
    getch();
    system("CLS");
}

void parseDictionaries(Sentence *sentenceObject){	//Parses all the text files, sorting the words in their repective arrays 
	wordParse(sentenceObject->Noun, NOUN, &sentenceObject->nounSize);
    wordParse(sentenceObject->Adj, ADJ, &sentenceObject->adjSize);
    wordParse(sentenceObject->Adv, ADV, &sentenceObject->advSize);
    wordParse(sentenceObject->Verb, VERB, &sentenceObject->verbSize);
    wordParse(sentenceObject->Prep, PREP, &sentenceObject->prepSize);
    wordParse(sentenceObject->Conj, CONJ, &sentenceObject->conjSize);
    wordParse(sentenceObject->Pro, PRO, &sentenceObject->proSize);
}

void SaveToFile(char *s){		//Adds the current string to the text file
	FILE *saveFile;
	saveFile = fopen("saved_Poems.txt","a");
	fprintf(saveFile, s);
	fprintf(saveFile, "\n");
	fclose(saveFile);
}

int main(){
    srand(time(NULL));
    char command;
    Sentence sentenceObject;
    
    showMenu();
    parseDictionaries(&sentenceObject);
    
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ The Program Itself ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    printf("[space]\t- Generate a new verse\n  [s]\t- Save the previous verse in a text file\n"
	"  [c]\t- Clear the screen\n  [x]\t- Quit\n\n", Save_Char, Clear_Char, Quit_Char);
    
    while (command != Quit_Char){
        do{									//Get user Input
            command = getch();
        }while (command != Quit_Char && command != Gen_Char && command != Save_Char && command != Clear_Char);
        
        if (command == Gen_Char){			//Generate new String
	        sentenceObject.createString();
	        sentenceObject.print();
        }
        else if (command == Save_Char){		//Save verse to file
        	SaveToFile(sentenceObject.string);
        	printf("Verse Saved!\n\n");
        }
        else if (command == Clear_Char){	//Clear screen
        	system("CLS");
        	printf("[space]\t- Generate a new verse\n  [s]\t- Save the previous verse in a text file\n"
			"  [c]\t- Clear the screen\n  [x]\t- Quit.\n\n", Save_Char, Clear_Char, Quit_Char);
		}
    }
    
    system("CLS");
    printf("Program Over.");
    return 0;
}   
