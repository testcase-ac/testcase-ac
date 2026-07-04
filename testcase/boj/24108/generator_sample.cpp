#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int k;
    int n;
    int m;

    if (mode == 0) {
        k = rnd.next(1, 12);
        n = rnd.next(1, 30);
        m = 0;
    } else if (mode == 1) {
        k = rnd.next(1, 12);
        n = rnd.next(1, 30);
        m = n;
    } else if (mode == 2) {
        k = rnd.next(10, 36);
        n = rnd.next(2, 80);
        m = rnd.next(1, n);
    } else if (mode == 3) {
        k = rnd.next(12, 60);
        n = rnd.next(1000, 10000000);
        m = rnd.next(0, min(n, 20));
    } else if (mode == 4) {
        k = rnd.next(80, 160);
        n = rnd.next(20, 200);
        m = rnd.next(1, n);
    } else if (mode == 5) {
        k = rnd.next(2, 24);
        n = rnd.next(1000000, 10000000);
        m = rnd.next(max(0, n - 20), n);
    } else {
        k = rnd.next(95, 125);
        n = rnd.next(1, 100);
        m = rnd.next(0, n);
    }

    int maxScore = 100 * m;
    vector<int> scores(k);

    if (maxScore == 0) {
        fill(scores.begin(), scores.end(), 0);
    } else if (mode == 1) {
        for (int i = 0; i < k; ++i) {
            scores[i] = 100 * rnd.next(0, m);
        }
    } else if (mode == 2) {
        int center = rnd.next(0, maxScore);
        int radius = rnd.next(0, min(maxScore, 250));
        for (int i = 0; i < k; ++i) {
            scores[i] = rnd.next(max(0, center - radius), min(maxScore, center + radius));
        }
    } else if (mode == 3) {
        for (int i = 0; i < k; ++i) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) {
                scores[i] = rnd.next(0, min(maxScore, 100));
            } else if (bucket == 1) {
                scores[i] = rnd.next(0, maxScore);
            } else {
                scores[i] = rnd.next(max(0, maxScore - 100), maxScore);
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < k; ++i) {
            scores[i] = (i * maxScore) / max(1, k - 1);
            if (rnd.next(0, 2) == 0) {
                scores[i] = max(0, min(maxScore, scores[i] + rnd.next(-50, 50)));
            }
        }
    } else if (mode == 5) {
        int repeated = rnd.next(0, maxScore);
        for (int i = 0; i < k; ++i) {
            scores[i] = (rnd.next(0, 3) == 0) ? rnd.next(0, maxScore) : repeated;
        }
    } else {
        int step = rnd.next(1, max(1, min(maxScore, 100)));
        for (int i = 0; i < k; ++i) {
            scores[i] = min(maxScore, (i % 12) * step);
        }
    }

    shuffle(scores.begin(), scores.end());

    println(k, n, m);
    for (int score : scores) {
        println(score);
    }

    return 0;
}
