#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const long long LIMIT = 1000000000LL;

pair<long long, long long> applyMove(pair<long long, long long> fraction, char move) {
    long long a = fraction.first;
    long long b = fraction.second;
    if (move == 'L') {
        return {b, a + b};
    }
    return {a + b, a};
}

bool canApply(pair<long long, long long> fraction, char move) {
    pair<long long, long long> next = applyMove(fraction, move);
    return next.first <= LIMIT && next.second <= LIMIT;
}

pair<long long, long long> fractionFromPath(const string& path) {
    pair<long long, long long> fraction = {1, 1};
    for (char move : path) {
        fraction = applyMove(fraction, move);
    }
    return fraction;
}

string alternatingPath(int length) {
    string path;
    path.reserve(length);
    char move = rnd.next(2) == 0 ? 'L' : 'R';
    for (int i = 0; i < length; ++i) {
        path.push_back(move);
        move = move == 'L' ? 'R' : 'L';
    }
    return path;
}

string runPath(int length) {
    pair<long long, long long> fraction = {1, 1};
    string path;
    path.reserve(length);
    while ((int)path.size() < length) {
        char move = rnd.next(2) == 0 ? 'L' : 'R';
        int runLength = rnd.next(1, min(12, length - (int)path.size()));
        for (int i = 0; i < runLength; ++i) {
            if (!canApply(fraction, move)) {
                return path;
            }
            path.push_back(move);
            fraction = applyMove(fraction, move);
        }
    }
    return path;
}

string boundedRandomWalk(int targetLength) {
    pair<long long, long long> fraction = {1, 1};
    string path;
    path.reserve(targetLength);

    for (int i = 0; i < targetLength; ++i) {
        vector<char> choices;
        if (canApply(fraction, 'L')) {
            choices.push_back('L');
        }
        if (canApply(fraction, 'R')) {
            choices.push_back('R');
        }
        if (choices.empty()) {
            break;
        }

        char move = rnd.any(choices);
        path.push_back(move);
        fraction = applyMove(fraction, move);
    }

    return path;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string path;

    if (mode == 0) {
        path = string(rnd.next(1, 29), rnd.next(2) == 0 ? 'L' : 'R');
    } else if (mode == 1) {
        path = alternatingPath(rnd.next(2, 43));
    } else if (mode == 2) {
        path = runPath(rnd.next(3, 45));
    } else if (mode == 3) {
        path = boundedRandomWalk(rnd.next(20, 120));
    } else if (mode == 4) {
        vector<string> nearLimit = {
            string(29, 'L'),
            string(29, 'R'),
            alternatingPath(43),
            boundedRandomWalk(120),
        };
        path = rnd.any(nearLimit);
    } else {
        path = boundedRandomWalk(rnd.next(1, 45));
    }

    pair<long long, long long> fraction = fractionFromPath(path);
    printf("%lld/%lld\n", fraction.first, fraction.second);

    return 0;
}
