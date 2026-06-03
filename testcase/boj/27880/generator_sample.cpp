#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int unitFor(const string& kind) {
    return kind == "Stair" ? 17 : 21;
}

int minimumDepthFrom(const vector<string>& kinds, int start) {
    int total = 0;
    for (int i = start; i < 4; ++i) {
        total += unitFor(kinds[i]);
    }
    return total;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<string> kinds(4);

    if (mode == 0) {
        kinds = {"Stair", "Stair", "Stair", "Stair"};
    } else if (mode == 1) {
        kinds = {"Es", "Es", "Es", "Es"};
    } else {
        for (string& kind : kinds) {
            kind = rnd.next(0, 1) == 0 ? "Stair" : "Es";
        }
        if (mode == 3) {
            kinds[0] = "Es";
            kinds[1] = "Stair";
        }
    }

    if (mode >= 2) {
        shuffle(kinds.begin(), kinds.end());
    }

    vector<int> values(4);
    int depth = 0;
    bool nearLimit = mode == 4 || mode == 5;

    for (int i = 0; i < 4; ++i) {
        int unit = unitFor(kinds[i]);
        int remainingMinimum = minimumDepthFrom(kinds, i + 1);
        int maxValue = (6425 - depth - remainingMinimum) / unit;

        if (nearLimit) {
            int low = max(1, maxValue - rnd.next(0, 8));
            values[i] = i == 3 ? maxValue : rnd.next(low, maxValue);
        } else if (mode == 0 || mode == 1) {
            values[i] = rnd.next(1, min(maxValue, 12));
        } else {
            int cap = min(maxValue, rnd.next(4, 80));
            values[i] = rnd.next(1, cap);
        }

        depth += unit * values[i];
    }

    for (int i = 0; i < 4; ++i) {
        println(kinds[i], values[i]);
    }

    return 0;
}
