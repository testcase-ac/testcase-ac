#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int differentFrom(int value) {
    int candidate = rnd.next(1, 4);
    if (candidate >= value) {
        ++candidate;
    }
    return candidate;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 6);
    } else if (mode == 2) {
        n = rnd.next(7, 14);
    } else {
        n = rnd.next(15, 30);
    }

    vector<int> answer(n);
    answer[0] = rnd.next(1, 5);
    for (int i = 1; i < n; ++i) {
        if (mode == 3) {
            answer[i] = answer[i - 1] == 1 ? 2 : 1;
        } else if (mode == 4 && i % 3 == 0) {
            answer[i] = 5;
            if (answer[i] == answer[i - 1]) {
                answer[i] = 4;
            }
        } else {
            answer[i] = differentFrom(answer[i - 1]);
        }
    }

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());

    int m;
    if (mode == 0) {
        m = 1;
    } else if (mode == 1) {
        m = n;
    } else if (mode == 2) {
        m = 1;
    } else {
        m = rnd.next(1, n);
    }

    vector<bool> guessed(n, false);
    for (int i = 0; i < m; ++i) {
        guessed[order[i]] = true;
    }

    vector<int> correct(n);
    for (int i = 0; i < n; ++i) {
        correct[i] = guessed[i] ? answer[i] : differentFrom(answer[i]);
    }

    vector<int> guessedIndices;
    for (int i = 0; i < n; ++i) {
        if (guessed[i]) {
            guessedIndices.push_back(i + 1);
        }
    }
    shuffle(guessedIndices.begin(), guessedIndices.end());

    println(n, m);
    println(correct);
    println(guessedIndices);

    return 0;
}
