#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 0) {
        n = 5;
        m = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(5, 12);
        m = rnd.next(1, 20);
    } else if (mode == 2) {
        n = rnd.next(20, 80);
        m = rnd.next(20, 120);
    } else if (mode == 3) {
        n = rnd.next(100, 500);
        m = rnd.next(1, 200);
    } else if (mode == 4) {
        n = rnd.next(7000, 7400);
        m = rnd.next(1, 80);
    } else {
        n = rnd.next(5, 7400);
        m = rnd.next(7000, 7400);
    }

    vector<int> answers;
    answers.reserve(m);

    int pattern = rnd.next(0, 5);
    for (int i = 0; i < m; ++i) {
        int answer;
        if (pattern == 0) {
            answer = rnd.next(1, n - 1);
        } else if (pattern == 1) {
            answer = rnd.any(vector<int>{1, n - 1});
        } else if (pattern == 2) {
            answer = 1 + (i % (n - 1));
        } else if (pattern == 3) {
            answer = n - 1 - (i % (n - 1));
        } else if (pattern == 4) {
            int center = max(1, (n - 1) / 2);
            answer = rnd.next(max(1, center - 2), min(n - 1, center + 2));
        } else {
            answer = rnd.next(1, min(n - 1, 10));
        }
        answers.push_back(answer);
    }

    println(n, m);
    for (int answer : answers) {
        println(answer);
    }

    return 0;
}
