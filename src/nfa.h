#ifndef NFA_H
#define NFA_H

typedef struct NFA_state{
    int i;
    int j;
    int n;

} NFA_state;


NFA_state* newState(int i, int j, int n);

NFA_state* nextState(NFA_state *state, char *s, int dir);

int isFinalState(NFA_state *state);

void print_state(NFA_state *state);

#endif