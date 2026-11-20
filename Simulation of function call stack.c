#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 3.1 Linked Stack Node
struct Node {
    char functionName[50];
    struct Node *next;
};

//3.2 Stack Structure
struct Stack {
    struct Node *top;
};

// Initialize stack
void initStack(struct Stack *s) {
    s->top = NULL;
}

// Check empty
int isEmpty(struct Stack *s) {
    return s->top == NULL;
}

// Push function name onto stack
void push(struct Stack *s, char *funcName) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->functionName, funcName);
    newNode->next = s->top;
    s->top = newNode;
}

// Pop from stack
struct Node* pop(struct Stack *s) {
    if(isEmpty(s)){
        return NULL;
    }
    struct Node *temp = s->top;
    s->top = s->top->next;
    return temp;
}

// Peek top element
char* peek(struct Stack *s) {
    if(isEmpty(s)){
        return NULL;
    }
    return s->top->functionName;
}

// Print current call stack
void displayStack(struct Stack *s) {
    if(isEmpty(s)){
        printf("Call Stack: (empty)\n");
        return;
    }
    struct Node *cur = s->top;
    printf("Call Stack: ");
    while(cur != NULL){
        printf("[%s]", cur->functionName);
        if(cur->next != NULL){
            printf(" -> ");
        }
        cur = cur->next;
    }
    printf("\n");
}

// Simulate function CALL
void callFunction(struct Stack *s, char *funcName) {
    printf("[CALL] %s\n", funcName);
    push(s, funcName);
    displayStack(s);
}

// Simulate function RETURN
void returnFunction(struct Stack *s) {
    if(isEmpty(s)){
        printf("Trying to return from an empty stack\n");
        printf("Stack is empty. Nothing to return.\n");
        return;
    }
    struct Node *popped = pop(s);
    printf("%s returns\n", popped->functionName);
    printf("[RETURN] %s\n", popped->functionName);
    free(popped);
    displayStack(s);
}

// Free all memory of stack
void freeStack(struct Stack *s) {
    while(!isEmpty(s)){
        struct Node *temp = pop(s);
        free(temp);
    }
}

int main() {
    printf("===== Function Call Stack Simulation =====\n\n");
    struct Stack callStack;
    initStack(&callStack);

    // Simulation steps: main → functionA → functionB → functionC
    printf("main starts\n");
    callFunction(&callStack, "main");
    callFunction(&callStack, "functionA");
    callFunction(&callStack, "functionB");
    callFunction(&callStack, "functionC");

    // Return step by step
    returnFunction(&callStack); // functionC return
    returnFunction(&callStack); // functionB return
    returnFunction(&callStack); // functionA return
    returnFunction(&callStack); // main return

    // Edge case: return from empty stack
    returnFunction(&callStack);

    printf("Program ended. Memory freed.\n");
    freeStack(&callStack);
    return 0;
}
