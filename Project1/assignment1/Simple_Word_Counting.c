#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 1000

//type all the functions we have declared
void SWC(char filename[100]);
void print_anwer(char filename[100]);

int main(){
    //converge two char array
    char filename_prefix_input[100] = "tests/input/sample";
    char filename_surfix_input[100] = ".txt";
    char temp_input[100];

    char filename_prefix_answer[100] = "tests/answer/sample";
    char filename_surfix_answer[100] = ".stdout";
    char temp_answer[100];
    
    char numberString[3];

    for(int i=0; i<12; i++){
        sprintf(numberString, "%02d", i+1);

        //copy filenmae_prefix to temp_input
        strcpy(temp_input, filename_prefix_input);
        strcat(temp_input, numberString);
        strcat(temp_input, filename_surfix_input);

        strcpy(temp_answer, filename_prefix_answer);
        strcat(temp_answer, numberString);
        strcat(temp_answer, filename_surfix_answer);

        printf("sample %d\n", i+1);
        SWC(temp_input); //Simple Word Counting
        print_anwer(temp_answer);
    }


    return 0;
}

void SWC(char filename[100]){
    FILE *file;
    char line[MAX_SIZE];
    int newline = 0;
    int words = 0;
    int characters = 0;

    file = fopen(filename, "r");


    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    int flag = 0;

    while (fgets(line, MAX_SIZE, file) != NULL) {
        //count new line
        //read each char in line and increase new line if there is newline
        for(int i=0; i<strlen(line); i++){
            if(line[i] == '\n'){
                newline++;
            }
        }

        if(!flag){
            //count words
            //read each char in line and increase words if there is space
            for(int i=0; i<strlen(line); i++){
                if(line[i] == ' '){
                    if(i==0 || i==strlen(line)-1)
                        continue;    
                    if(line[i+1] == ' ')
                        continue;
                    if(line[i+1] == '/' && line[i+2] == '*')
                        continue;
                    words++;
                }
            }
        }
        
        //count '/* */' in a line
        //read each char in line and increase words if there is space
        for(int i=0; i<strlen(line); i++){
            if(line[i] == '/' && line[i+1] == '*'){
                flag = !flag;
                for(int j=i+2; j<strlen(line); j++){
                    if(line[j] == '*' && line[j+1] == '/'){
                        flag = !flag;
                        if(line[j+2] == ' '){
                            continue;
                        }
                        words++;
                    }
                }
            }
        }

        if(!flag){
            //if line is not impty and the last char is not space, increase words
            if(strlen(line) != 0 && line[strlen(line)-1] != ' '){
                words++;
            }
        }
        

        //count characters
        characters += strlen(line);
        //count characters inside '/* */'
        for(int i=0; i<strlen(line); i++){
            if(line[i] == '/' && line[i+1] == '*'){
                for(int j=i+2; j<strlen(line); j++){
                    if(line[j] == '*' && line[j+1] == '/'){
                        characters -= j-i+1;
                        break;
                    }
                }
            }
        }
        // count character between '//' and newline
        for(int i=0; i<strlen(line); i++){
            if(line[i] == '/' && line[i+1] == '/'){
                for(int j=i+2; j<strlen(line); j++){
                    if(line[j] == '\n'){
                        characters -= j-i;
                        break;
                    }
                    if(j == strlen(line)-1){
                        characters -= j-i+1;
                        break;
                    }
                }
            }
        }
    }
    // 0123456789
    // a//bcd
    printf("result: %d %d %d\n", newline, words, characters);
    fclose(file);
}

void print_anwer(char filename[100]){
    FILE *file;
    file = fopen(filename, "r");
    //print file contents, file include one line
    char line[MAX_SIZE];
    while (fgets(line, MAX_SIZE, file) != NULL) {
        printf("answer: %s\n", line);
    }

}