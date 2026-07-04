#include "testlib.h"

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

int roundedAverage(const vector<int>& scores) {
    long long sum = 0;
    for (int score : scores) {
        sum += score;
    }
    return int((2 * sum + int(scores.size())) / (2 * int(scores.size())));
}

void printScore(int score) {
    printf("%d.%02d", score / 100, score % 100);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(4, 6);
    } else if (mode == 1) {
        n = rnd.next(17, 20);
    } else {
        n = rnd.next(7, 16);
    }

    int k;
    if (mode == 2) {
        k = 0;
    } else if (mode == 3) {
        k = n - 3;
    } else {
        k = rnd.next(0, n - 3);
    }

    int keptCount = n - k - 2;
    int lowBound = 100;
    int highBound = 600;
    if (mode == 4) {
        lowBound = rnd.next(100, 350);
        highBound = rnd.next(max(lowBound, 350), 600);
    }

    vector<int> kept;
    kept.reserve(keptCount);
    for (int i = 0; i < keptCount; ++i) {
        int score;
        if (mode == 1 && i % 5 == 0) {
            score = rnd.any(vector<int>{100, 600});
        } else if (mode == 3 && i > 0 && rnd.next(0, 1) == 0) {
            score = kept.back();
        } else {
            score = rnd.next(lowBound, highBound);
        }
        kept.push_back(score);
    }

    int minKept = *min_element(kept.begin(), kept.end());
    int maxKept = *max_element(kept.begin(), kept.end());

    vector<int> allScores = kept;
    allScores.push_back(rnd.next(100, minKept));
    allScores.push_back(rnd.next(maxKept, 600));
    for (int i = 0; i < k; ++i) {
        if (mode == 0 && rnd.next(0, 1) == 0) {
            allScores.push_back(rnd.any(vector<int>{100, 600}));
        } else {
            allScores.push_back(rnd.next(100, 600));
        }
    }
    shuffle(allScores.begin(), allScores.end());

    printf("%d %d\n", n, k);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            printf(" ");
        }
        printScore(allScores[i]);
    }
    printf("\n");
    printScore(roundedAverage(kept));
    printf("\n");

    return 0;
}
