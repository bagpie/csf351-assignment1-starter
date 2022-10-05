#include <stdio.h>
#include <stdlib.h>
#include "nfa.h"


NFA_state* newState(int i, int j, int n){

    NFA_state *state = malloc(sizeof(NFA_state));

    state -> i = i;
    state -> j = j;
    state -> n = n;

    return state;
}

NFA_state* nextState(NFA_state *state, char *s, int dir){

    if(*s == '0'){
        if(state -> j + dir <= state -> n && state -> j + dir >= 0){
            return newState(state -> i, state -> j + dir, state -> n);
        }
    }

    else if(*s == '1'){
        if(state -> i + dir <= state -> n && state -> i + dir >= 0){
            return newState(state -> i + dir, state -> j, state -> n);
        }
    }

    return NULL;
}

int isFinalState(NFA_state *state){
    return state -> i == state -> n && state -> j == state -> n ? 1 : 0;
}

void print_state(NFA_state *state){
    printf("i -> %d j -> %d\n", state -> i, state -> j);
}