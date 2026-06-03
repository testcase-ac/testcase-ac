#include "testlib.h"
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct Turn {
    char op1;
    int v1;
    char op2;
    int v2;
};

Turn randomTurn() {
    return {rnd.any(string("+*")), rnd.next(1, 9), rnd.any(string("+*")), rnd.next(1, 9)};
}

Turn sameOpTurn(char op) {
    return {op, rnd.next(1, 9), op, rnd.next(1, 9)};
}

Turn targetSevenTurn() {
    vector<Turn> turns = {
        {'+', 6, '*', 7},
        {'*', 7, '+', 6},
        {'+', 3, '+', 6},
        {'*', 1, '*', 7},
        {'+', 9, '*', 7},
    };
    return rnd.any(turns);
}

Turn neutralTurn() {
    vector<Turn> turns = {
        {'+', 7, '*', 1},
        {'*', 8, '+', 7},
        {'+', 1, '*', 1},
        {'*', 1, '+', 8},
    };
    return rnd.any(turns);
}

vector<Turn> makeCase(int mode) {
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode <= 2) {
        n = rnd.next(2, 6);
    } else if (mode <= 4) {
        n = rnd.next(4, 12);
    } else {
        n = rnd.next(10, 30);
    }

    vector<Turn> turns;
    turns.reserve(n);

    if (mode == 0) {
        turns.push_back(rnd.next(2) == 0 ? targetSevenTurn() : randomTurn());
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) turns.push_back(sameOpTurn('+'));
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) turns.push_back(sameOpTurn('*'));
    } else if (mode == 3) {
        turns.push_back(targetSevenTurn());
        for (int i = 1; i < n; ++i) turns.push_back(rnd.next(3) == 0 ? neutralTurn() : randomTurn());
        shuffle(turns.begin(), turns.end());
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            turns.push_back(rnd.next(2) == 0 ? neutralTurn() : randomTurn());
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(5);
            if (pick == 0) turns.push_back(targetSevenTurn());
            else if (pick == 1) turns.push_back(neutralTurn());
            else turns.push_back(randomTurn());
        }
    }

    return turns;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    vector<vector<Turn>> cases;
    cases.reserve(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = tc < 6 ? tc : rnd.next(0, 5);
        cases.push_back(makeCase(mode));
    }
    shuffle(cases.begin(), cases.end());

    println(t);
    for (const auto& turns : cases) {
        println(static_cast<int>(turns.size()));
        for (const Turn& turn : turns) {
            println(string(1, turn.op1), turn.v1, string(1, turn.op2), turn.v2);
        }
    }

    return 0;
}
