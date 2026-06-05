#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static void printSequence(const vector<int>& values) {
    println((int)values.size());
    for (int i = 0; i < (int)values.size(); ++i) {
        if (i % 10) {
            printf(" ");
        }
        printf("%d", values[i]);
        if (i % 10 == 9 || i + 1 == (int)values.size()) {
            printf("\n");
        }
    }
}

static vector<int> randomSequence(int n, int lo, int hi) {
    vector<int> values(n);
    for (int& value : values) {
        value = rnd.next(lo, hi);
    }
    return values;
}

static vector<int> partitionableSequence(int groups, int targetSum) {
    vector<int> values;
    for (int group = 0; group < groups; ++group) {
        int remaining = targetSum;
        while (remaining > 0) {
            int take = remaining;
            if (remaining > 1 && rnd.next(0, 99) < 65) {
                take = rnd.next(1, remaining);
            }
            values.push_back(take);
            remaining -= take;
        }
    }
    return values;
}

static vector<int> repeatedPatternSequence() {
    int period = rnd.next(2, 6);
    int repeats = rnd.next(2, 8);
    vector<int> pattern(period);
    for (int& value : pattern) {
        value = rnd.next(1, 7);
    }

    vector<int> values;
    for (int i = 0; i < repeats; ++i) {
        values.insert(values.end(), pattern.begin(), pattern.end());
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);
    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int mode = rnd.next(0, 4);
        vector<int> values;

        if (mode == 0) {
            values = randomSequence(rnd.next(1, 30), 1, 30);
        } else if (mode == 1) {
            int groups = rnd.next(2, 10);
            int targetSum = rnd.next(2, 40);
            values = partitionableSequence(groups, targetSum);
        } else if (mode == 2) {
            int n = rnd.next(10, 60);
            values.assign(n, rnd.next(1, 9));
        } else if (mode == 3) {
            values = repeatedPatternSequence();
        } else {
            int n = rnd.next(1, 80);
            values = randomSequence(n, 9000, 10000);
        }

        printSequence(values);
    }

    return 0;
}
