#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Turn {
    int time;
    char action;
};

static vector<int> increasingTimes(int s, int maxStep) {
    vector<int> times;
    times.reserve(s);

    int current = 0;
    for (int i = 0; i < s; ++i) {
        int remaining = s - i - 1;
        int latest = 2000 - remaining;
        int step = rnd.next(1, min(maxStep, latest - current));
        current += step;
        times.push_back(current);
    }

    return times;
}

static vector<Turn> makeTurns(int s, int mode) {
    int maxStep = rnd.any(vector<int>{1, 2, 3, 8, 25, 100});
    vector<int> times = increasingTimes(s, maxStep);
    vector<Turn> turns;
    turns.reserve(s);

    for (int i = 0; i < s; ++i) {
        char action = 'L';
        if (mode == 0) {
            action = (i % 2 == 0 ? 'L' : 'R');
        } else if (mode == 1) {
            action = (i % 3 == 0 ? 'R' : 'L');
        } else if (mode == 2) {
            action = (i < s / 2 ? 'L' : 'R');
        } else if (mode == 3) {
            action = (rnd.next(0, 4) == 0 ? 'L' : 'R');
        } else {
            action = (rnd.next(0, 1) == 0 ? 'L' : 'R');
        }
        turns.push_back({times[i], action});
    }

    return turns;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = tc < 5 ? tc : rnd.next(0, 4);
        int s;
        int r;
        int c;

        if (mode == 0) {
            s = rnd.next(1, 6);
            r = 1;
            c = rnd.next(1, 10);
        } else if (mode == 1) {
            s = rnd.next(1, 8);
            r = rnd.next(1, 10);
            c = 1;
        } else if (mode == 2) {
            s = rnd.next(4, 16);
            r = rnd.next(2, 6);
            c = rnd.next(2, 6);
        } else if (mode == 3) {
            s = rnd.next(15, 60);
            r = rnd.next(2, 20);
            c = rnd.next(2, 20);
        } else {
            s = rnd.next(20, 100);
            r = rnd.any(vector<int>{1, 2, 3, 50, 99, 100});
            c = rnd.any(vector<int>{1, 2, 3, 50, 99, 100});
        }

        vector<Turn> turns = makeTurns(s, mode);

        println(s, r, c);
        for (const Turn& turn : turns) {
            println(turn.time, turn.action);
        }
    }

    return 0;
}
