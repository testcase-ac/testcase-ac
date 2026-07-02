#include "testlib.h"
#include <vector>
using namespace std;

const int MAX_MOVES = 100000;

int n, k;
vector<int> capacity;
vector<vector<int>> initialStacks;

struct Answer {
    int moves;
};

void readInput() {
    n = inf.readInt();
    k = inf.readInt();

    capacity.assign(k, 0);
    initialStacks.assign(k, {});
    for (int i = 0; i < k; ++i) {
        capacity[i] = inf.readInt();
        for (int j = 0; j < capacity[i]; ++j) {
            int card = inf.readInt();
            if (card != 0) {
                initialStacks[i].push_back(card);
            }
        }
    }
}

bool isGoalState(const vector<vector<int>>& stacks) {
    int expected = 1;
    bool seenPartialOrEmpty = false;

    for (int i = 0; i < k; ++i) {
        int size = (int)stacks[i].size();
        if (size == 0) {
            seenPartialOrEmpty = true;
        } else {
            if (seenPartialOrEmpty) {
                return false;
            }
            if (size < capacity[i]) {
                seenPartialOrEmpty = true;
            }
        }

        for (int card : stacks[i]) {
            if (card != expected) {
                return false;
            }
            ++expected;
        }
    }

    return expected == n + 1;
}

Answer readAnswer(InStream& stream) {
    vector<vector<int>> stacks = initialStacks;
    int moves = 0;

    while (true) {
        int from = stream.readInt(0, k, "source stack");
        stream.readSpace();
        int to = stream.readInt(0, k, "destination stack");
        stream.readEoln();

        if (from == 0 || to == 0) {
            if (from != 0 || to != 0) {
                stream.quitf(_wa, "only 0 0 may terminate the move list");
            }
            break;
        }

        ++moves;
        if (moves > MAX_MOVES) {
            stream.quitf(_wa, "too many moves: %d exceeds %d", moves, MAX_MOVES);
        }
        if (from == to) {
            stream.quitf(_wa, "move %d uses the same source and destination stack %d", moves, from);
        }
        --from;
        --to;

        if (stacks[from].empty()) {
            stream.quitf(_wa, "move %d takes from empty stack %d", moves, from + 1);
        }
        if ((int)stacks[to].size() == capacity[to]) {
            stream.quitf(_wa, "move %d puts a card onto full stack %d", moves, to + 1);
        }

        int card = stacks[from].back();
        stacks[from].pop_back();
        stacks[to].push_back(card);
    }

    stream.readEof();

    if (!isGoalState(stacks)) {
        stream.quitf(_wa, "final stack state is not sorted in the required shape");
    }

    return {moves};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    readInput();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    quitf(_ok, "valid sequence with %d moves; jury used %d moves", participant.moves, jury.moves);
}
