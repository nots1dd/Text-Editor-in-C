#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_LENGTH 1000
#define MAX_STACK_SIZE 100

// Stack structure
typedef struct {
    char text[MAX_TEXT_LENGTH];
    int length;
} State;

typedef struct {
    State items[MAX_STACK_SIZE];
    int top;
} Stack;

// Function prototypes
void initializeStack(Stack *s);
int isEmpty(Stack *s);
int isFull(Stack *s);
void push(Stack *s, State state);
State pop(Stack *s);
void undo(Stack *undo_stack, Stack *redo_stack);
void redo(Stack *undo_stack, Stack *redo_stack);

int main() {
    Stack undo_stack, redo_stack;
    initializeStack(&undo_stack);
    initializeStack(&redo_stack);

    char input[MAX_TEXT_LENGTH];
    while (1) {
        fgets(input, MAX_TEXT_LENGTH, stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove trailing newline

        if (strcmp(input, "exit") == 0) {
            break;
        } else if (strcmp(input, "undo") == 0) {
            undo(&undo_stack, &redo_stack);
        } else if (strcmp(input, "redo") == 0) {
            redo(&undo_stack, &redo_stack);
        } else {
            // Typing text or deleting text
            State current_state;
            strcpy(current_state.text, input);
            current_state.length = strlen(input);
            push(&undo_stack, current_state);
            initializeStack(&redo_stack);

        }
    }

    return 0;
}

void initializeStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX_STACK_SIZE - 1;
}

void push(Stack *s, State state) {
    if (!isFull(s)) {
        s->items[++(s->top)] = state;
    } else {
        printf("Stack overflow!\n");
    }
}

State pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    } else {
        printf("Stack underflow!\n");
        State empty_state;
        empty_state.length = 0;
        return empty_state;
    }
}

void undo(Stack *undo_stack, Stack *redo_stack) {
    if (!isEmpty(undo_stack)) {
        State undone_state = pop(undo_stack);
        push(redo_stack, undone_state);
        printf("Undone: %s\n", undone_state.text);
    } else {
        printf("Nothing to undo.\n");
    }
}

void redo(Stack *undo_stack, Stack *redo_stack) {
    if (!isEmpty(redo_stack)) {
        State redone_state = pop(redo_stack);
        push(undo_stack, redone_state);
        printf("Redone: %s\n", redone_state.text);
    } else {
        printf("Nothing to redo.\n");
    }
}
