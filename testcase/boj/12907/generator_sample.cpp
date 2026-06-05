#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> answers;

    if (mode == 0) {
        int n = rnd.next(1, 40);
        for (int i = 0; i < n; ++i) answers.push_back(i);
    } else if (mode == 1) {
        int pairs = rnd.next(1, 20);
        for (int i = 0; i < pairs; ++i) {
            answers.push_back(i);
            answers.push_back(i);
        }
    } else if (mode == 2) {
        int pairs = rnd.next(1, 13);
        int singles = rnd.next(1, 40 - 2 * pairs);
        for (int i = 0; i < pairs; ++i) {
            answers.push_back(i);
            answers.push_back(i);
        }
        for (int i = 0; i < singles; ++i) answers.push_back(pairs + i);
    } else if (mode == 3) {
        int n = rnd.next(2, 40);
        int hi = rnd.next(0, 40);
        for (int i = 0; i < n; ++i) answers.push_back(rnd.next(0, hi));
    } else if (mode == 4) {
        int n = rnd.next(2, 40);
        int repeated = rnd.next(0, 40);
        answers.assign(n, repeated);
    } else {
        int n = rnd.next(2, 40);
        int gapStart = rnd.next(0, 38);
        for (int i = 0; i < n; ++i) {
            int value = rnd.next(0, 40);
            if (value == gapStart) value = gapStart + 1;
            answers.push_back(value);
        }
    }

    shuffle(answers.begin(), answers.end());

    println(static_cast<int>(answers.size()));
    println(answers);

    return 0;
}
