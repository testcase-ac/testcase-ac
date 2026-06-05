#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n;
        int m;
        vector<int> scores;

        if (mode == 0) {
            m = 1;
            scores.push_back(rnd.next(1, 20));
            n = rnd.any(vector<int>{1, 2, 3, 6, 10, 15, 16, 21, 55, 120});
        } else if (mode == 1) {
            m = rnd.next(1, 4);
            n = rnd.next(1, 80);
            for (int score = 1; score <= 20 && (int)scores.size() < m; ++score) {
                scores.push_back(score);
            }
        } else if (mode == 2) {
            m = rnd.next(2, 6);
            n = rnd.next(1, 200);
            while ((int)scores.size() < m) {
                int score = rnd.next(1, 10);
                if (find(scores.begin(), scores.end(), score) == scores.end()) {
                    scores.push_back(score);
                }
            }
        } else if (mode == 3) {
            m = rnd.next(5, 10);
            n = rnd.next(100, 1000);
            vector<int> pool;
            for (int score = 1; score <= 20; ++score) {
                pool.push_back(score);
            }
            shuffle(pool.begin(), pool.end());
            scores.assign(pool.begin(), pool.begin() + m);
        } else if (mode == 4) {
            m = rnd.next(2, 10);
            n = rnd.next(4000, 5000);
            vector<int> pool = {1, 2, 3, 4, 5, 6, 7, 8, 9, 20};
            shuffle(pool.begin(), pool.end());
            scores.assign(pool.begin(), pool.begin() + m);
        } else {
            m = rnd.next(1, 10);
            n = rnd.next(1, 5000);
            while ((int)scores.size() < m) {
                int score = rnd.next(1, 20);
                if (find(scores.begin(), scores.end(), score) == scores.end()) {
                    scores.push_back(score);
                }
            }
        }

        shuffle(scores.begin(), scores.end());
        println(n, m);
        println(scores);
    }

    return 0;
}
