#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

static long long minMovesToState(const string& state) {
    long long moves = 0;
    char source = 'A';

    for (int disk = static_cast<int>(state.size()) - 1; disk >= 0; --disk) {
        char pos = state[disk];
        if (pos != source) {
            moves += 1LL << disk;
            source = static_cast<char>('A' + 'B' + 'C' - source - pos);
        }
    }

    return moves;
}

static string randomState(int n) {
    string state;
    state.reserve(n);
    for (int i = 0; i < n; ++i) {
        state.push_back("ABC"[rnd.next(0, 2)]);
    }
    return state;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    string state;

    if (mode == 0) {
        n = rnd.next(1, 5);
        state = randomState(n);
    } else if (mode == 1) {
        n = rnd.next(6, 15);
        state = randomState(n);
    } else if (mode == 2) {
        n = rnd.next(16, 30);
        state = randomState(n);
    } else if (mode == 3) {
        n = rnd.next(1, 30);
        state.assign(n, rnd.any(string("ABC")));
    } else if (mode == 4) {
        n = rnd.next(1, 30);
        string pattern = rnd.any(vector<string>{"ABC", "ACB", "BAC", "BCA", "CAB", "CBA"});
        for (int i = 0; i < n; ++i) {
            state.push_back(pattern[i % static_cast<int>(pattern.size())]);
        }
    } else {
        n = rnd.next(1, 30);
        state.assign(n, 'A');
        int changed = rnd.next(1, n);
        for (int i = 0; i < changed; ++i) {
            state[i] = rnd.any(string("BC"));
        }
    }

    long long requiredMoves = minMovesToState(state);
    long long m = rnd.next(0LL, requiredMoves);

    println(n, m);
    println(state);

    return 0;
}
