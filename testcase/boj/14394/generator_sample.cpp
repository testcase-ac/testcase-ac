#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeStateFromCounts(vector<int> counts, int blankPos) {
    const string colors = "RGBY";
    string state;
    for (int i = 0; i < 4; ++i) {
        state += string(counts[i], colors[i]);
    }
    shuffle(state.begin(), state.end());
    state.insert(state.begin() + blankPos, '*');
    return state;
}

vector<int> randomCounts(int total) {
    vector<int> counts(4, 0);
    for (int i = 0; i < total; ++i) {
        ++counts[rnd.next(4)];
    }
    return counts;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int currentBlank = rnd.next(10);
    int targetBlank = rnd.next(10);

    vector<int> currentCounts = randomCounts(9);
    vector<int> targetCounts;

    if (mode == 0) {
        targetCounts = currentCounts;
    } else if (mode == 1) {
        int color = rnd.next(4);
        currentCounts.assign(4, 0);
        targetCounts.assign(4, 0);
        currentCounts[color] = 9;
        targetCounts[rnd.next(4)] = 9;
    } else if (mode == 2) {
        currentCounts.assign(4, 0);
        targetCounts.assign(4, 0);
        int first = rnd.next(4);
        int second = rnd.next(4);
        currentCounts[first] = rnd.next(4, 9);
        currentCounts[second] += 9 - currentCounts[first];
        for (int i = 0; i < 9; ++i) {
            ++targetCounts[(first + 1 + rnd.next(3)) % 4];
        }
    } else {
        targetCounts = randomCounts(9);
    }

    println(makeStateFromCounts(currentCounts, currentBlank));
    println(makeStateFromCounts(targetCounts, targetBlank));

    return 0;
}
