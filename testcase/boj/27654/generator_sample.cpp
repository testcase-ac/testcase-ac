#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Score = pair<int, int>;

Score makeScore(int mode) {
    if (mode == 0) return {0, rnd.next(1, 100000)};
    if (mode == 1) {
        int q = rnd.next(1, 100000);
        return {q, q};
    }
    if (mode == 2) {
        int q = rnd.next(2, 100000);
        return {rnd.next(max(0, q - 5), q), q};
    }
    if (mode == 3) {
        int q = rnd.next(2, 100000);
        return {rnd.next(0, min(q, 5)), q};
    }

    int q = rnd.next(1, 100000);
    return {rnd.next(0, q), q};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;
    vector<Score> scores;

    if (mode == 0) {
        n = 1;
        k = 1;
        scores.push_back(makeScore(rnd.next(0, 4)));
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        k = n;
        for (int i = 0; i < n; ++i) scores.push_back(makeScore(rnd.next(0, 4)));
    } else if (mode == 2) {
        n = rnd.next(2, 18);
        k = 1;
        for (int i = 0; i < n; ++i) scores.push_back(makeScore(rnd.next(0, 4)));
    } else if (mode == 3) {
        n = rnd.next(4, 20);
        k = rnd.next(2, n - 1);
        int baseQ = rnd.next(20, 100000);
        int baseP = rnd.next(0, baseQ);
        for (int i = 0; i < n; ++i) {
            int q = max(1, min(100000, baseQ + rnd.next(-10, 10)));
            int p = max(0, min(q, baseP + rnd.next(-10, 10)));
            scores.push_back({p, q});
        }
    } else {
        n = rnd.next(5, 30);
        k = rnd.next(1, n);
        for (int i = 0; i < n; ++i) scores.push_back(makeScore(rnd.next(0, 4)));
    }

    shuffle(scores.begin(), scores.end());

    println(n, k);
    for (const auto& score : scores) println(score.first, score.second);

    return 0;
}
