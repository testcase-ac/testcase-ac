#include "testlib.h"

#include <vector>

using namespace std;

vector<int> applyMove(vector<int> state, int move) {
    vector<int> next = state;

    if (move == 0) {
        for (int i = 0; i < 8; ++i) {
            next[i] = state[7 - i];
        }
    } else if (move == 1) {
        next = {state[3], state[0], state[1], state[2],
                state[5], state[6], state[7], state[4]};
    } else if (move == 2) {
        next = {state[0], state[2], state[5], state[3],
                state[4], state[6], state[1], state[7]};
    } else {
        next = {state[4], state[1], state[2], state[3],
                state[0], state[5], state[6], state[7]};
    }

    return next;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> state = {1, 2, 3, 4, 5, 6, 7, 8};
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        int steps = rnd.next(0, 2);
        for (int i = 0; i < steps; ++i) {
            state = applyMove(state, rnd.next(0, 3));
        }
    } else if (mode == 1) {
        int steps = rnd.next(3, 8);
        int lastMove = -1;
        for (int i = 0; i < steps; ++i) {
            int move = rnd.next(0, 3);
            if (move == lastMove && rnd.next(0, 1) == 0) {
                move = (move + rnd.next(1, 3)) % 4;
            }
            state = applyMove(state, move);
            lastMove = move;
        }
    } else if (mode == 2) {
        int steps = rnd.next(9, 24);
        for (int i = 0; i < steps; ++i) {
            state = applyMove(state, rnd.wnext(4, 2));
        }
    } else {
        shuffle(state.begin(), state.end());
    }

    println(state);
    return 0;
}
