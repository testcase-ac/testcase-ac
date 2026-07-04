#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string makeAlternating(int n, char first) {
    string turns;
    turns.reserve(n);
    for (int i = 0; i < n; ++i) {
        turns.push_back((i % 2 == 0) ? first : (first == 'L' ? 'R' : 'L'));
    }
    return turns;
}

string makeRuns(int n) {
    string turns;
    turns.reserve(n);
    char current = rnd.next(2) == 0 ? 'L' : 'R';
    while (static_cast<int>(turns.size()) < n) {
        int remaining = n - static_cast<int>(turns.size());
        int runLength = rnd.next(1, min(remaining, rnd.next(2, 12)));
        turns.append(runLength, current);
        if (rnd.next(100) < 80) {
            current = (current == 'L' ? 'R' : 'L');
        }
    }
    return turns;
}

string makeBiased(int n, int leftPercent) {
    string turns;
    turns.reserve(n);
    for (int i = 0; i < n; ++i) {
        turns.push_back(rnd.next(100) < leftPercent ? 'L' : 'R');
    }
    return turns;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int W = 1;
    int H = 1;
    int N = 1;
    string turns;

    if (mode == 0) {
        W = rnd.next(1, 4);
        H = rnd.next(1, 4);
        N = rnd.next(1, 8);
        turns = makeBiased(N, rnd.next(25, 75));
    } else if (mode == 1) {
        W = rnd.next(1, 20);
        H = rnd.next(1, 20);
        N = rnd.next(1, 30);
        turns = makeAlternating(N, rnd.next(2) == 0 ? 'L' : 'R');
    } else if (mode == 2) {
        W = rnd.next(1, 12);
        H = rnd.next(50, 1000);
        N = rnd.next(2, 60);
        turns = makeRuns(N);
    } else if (mode == 3) {
        W = rnd.next(50, 1000);
        H = rnd.next(1, 12);
        N = rnd.next(2, 60);
        turns = makeRuns(N);
    } else if (mode == 4) {
        W = rnd.next(900, 1000);
        H = rnd.next(900, 1000);
        N = rnd.next(1, 80);
        turns = makeBiased(N, rnd.next(10, 90));
    } else if (mode == 5) {
        W = rnd.next(1, 1000);
        H = rnd.next(1, 1000);
        N = rnd.next(200, 800);
        turns = makeRuns(N);
    } else if (mode == 6) {
        W = rnd.next(1, 1000);
        H = rnd.next(1, 1000);
        N = rnd.next(9000, 10000);
        turns = makeBiased(N, rnd.any(vector<int>{5, 20, 50, 80, 95}));
    } else {
        W = rnd.any(vector<int>{1, 2, 999, 1000});
        H = rnd.any(vector<int>{1, 2, 999, 1000});
        N = rnd.any(vector<int>{1, 2, 3, 9999, 10000});
        turns = rnd.next(2) == 0 ? makeAlternating(N, 'L') : makeRuns(N);
    }

    println(W, H);
    println(N);
    println(turns);
    return 0;
}
