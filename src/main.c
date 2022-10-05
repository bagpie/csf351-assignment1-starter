#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

#include "nfa.h"
// Include any other libraries that you might use. 

// All your imports go here. 
// For example if you have a file: `src/nfa.h`
// import it as: #include "nfa.h"

int *isSatisfied = NULL;

void solve(NFA_state *state, char *s){
    
    if(*s == '\0'){
        if(isFinalState(state) == 1){
            int success = 1;
            isSatisfied = &success;
        }
        // print_state(state);
        return;
    }

    // printf("%p\n", isSatisfied);

    NFA_state *newState1 = nextState(state, s, 1);
    NFA_state *newState2 = nextState(state, s, -1);

    if(newState1 == NULL && newState2 == NULL)
        return;
    
    else if(newState1 == NULL){
        solve(newState2, s+1);
        return;
    }

    else if(newState2 == NULL){
        solve(newState1, s+1);
        return;
    }

    isSatisfied = mmap(NULL, sizeof *isSatisfied, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    pid_t pid = fork();

    if(pid == 0){
        solve(newState1, s+1);
    }

    else{
        solve(newState2, s+1);
        wait(NULL);
        munmap(isSatisfied, sizeof *isSatisfied);
    }

}

int main(int argc, char *argv[])
{
    // Read all input from stdin and write all output to stdout.

    // in = fopen("input.txt", "r");
    // out = fopen("output.txt", "w");

    // // Your code goes here...

    pid_t root_id = getpid();

    int n;
    scanf("%d", &n);

    char str[100];
    scanf("%s", str);

    isSatisfied = NULL;
    NFA_state *initialState = newState(0,0,n);

    solve(initialState, str);

    wait(NULL);

    if(getpid() == root_id){
        printf(isSatisfied != NULL ? "Satisfied\n" : "Not Satisfied\n");
    }

    return 0;
}