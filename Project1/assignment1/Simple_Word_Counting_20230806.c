#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 1000
#define MAX_SIZE_STACK 1000

typedef struct{
    int stack[MAX_SIZE_STACK];
    int top;
} Stack;

//type all the functions we have declared
void SWC(char filename[100]);
void print_anwer(char filename[100]);
void initialize(Stack* s);
void push(Stack* s, int value);
int pop(Stack* s);
int peek(Stack* s);
int isEmpty(Stack* s);
void print_count(Stack* s);
void printStack(Stack* s);

Stack stack;

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
        SWC(temp_input);
        print_anwer(temp_answer);
    }


    return 0;
}

void SWC(char filename[100]){
    FILE *file;
    char line[MAX_SIZE];
    int index=0;

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    int flag_comment_1 = 0; //
    int flag_comment_2 = 0; /**/

    while (fgets(line, MAX_SIZE, file) != NULL) {
        // 0: char
        // 1: space
        // 2: newline
        // 3: comment /**/

        printf("input line: %s\n", line);
        index = 0;
        while(index<strlen(line)){    
            if(index==strlen(line)) break;
            if(flag_comment_1){
                if(line[index] == '\n'){
                    flag_comment_1 = 0;
                    index++;
                }
                else index++;
            }
            
            else if(flag_comment_2){
                if(line[index] == '*' && line[index+1] == '/'){
                    flag_comment_2 = 0;
                    push(&stack, 1);
                    index += 2;
                }
                else index++;
            }

            else{
                if(line[index] == ' '){
                    push(&stack, 1);
                    index++;
                }
                else if(line[index] == '\n'){
                    push(&stack, 2);
                    index++;
                }
                else if(line[index] == '/' && line[index+1] == '/'){
                    index++;
                    flag_comment_1 = 1;
                }
                else if(line[index] == '/' && line[index+1] == '*'){
                    flag_comment_2 = 1;
                    index += 2;
                }
                else{
                    push(&stack, 0);
                    index++;
                }
            } 
        }
    }
    
    printStack(&stack);
    print_count(&stack);
    fclose(file);
}

void initialize(Stack* s) {
    s->top = -1;
}

void push(Stack* s, int value) {
    s->top++;
    s->stack[s->top] = value;
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return -1;
    }
    int value = s->stack[s->top];
    s->top--;
    return value;
}

int peek(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->stack[s->top];
}
int isEmpty(Stack* s) {
    return (s->top == -1);
}

//function that counts the number of each number in stack
void print_count(Stack* s) {
    int newline = 0;
    int words = 0;
    int characters = 0;
    // 0: char
    // 1: space
    // 2: newline
    // 3: comment /**/
    if(peek(s)==1) pop(s);

    while(!isEmpty(s)){
        switch (pop(s)){
        case 0:
            characters++;
            break;
        case 1:
            words++;
            break;
        case 2:
            newline++;
            break;
        default:
            break;
        }
    }
    printf("result: %d %d %d\n", newline, words, characters);
}

void printStack(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack elements: ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->stack[i]);
    }
    printf("\n");
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