#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> scores;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int value = rnd.next(1, 100);
        scores.assign(10, value);
    } else if (mode == 1) {
        int first = rnd.next(40, 60);
        int second = 100 - first;
        scores = {first, second};
        while ((int)scores.size() < 10) scores.push_back(rnd.next(1, 100));
    } else if (mode == 2) {
        int before = rnd.next(88, 99);
        int over = rnd.next(1, min(100, 110 - before));
        scores = {before, over};
        while ((int)scores.size() < 10) scores.push_back(rnd.next(1, 25));
    } else if (mode == 3) {
        int before = rnd.next(40, 90);
        int delta = rnd.next(1, min(before, 100 - before));
        scores = {before, 2 * delta};
        while ((int)scores.size() < 10) scores.push_back(rnd.next(1, 30));
    } else if (mode == 4) {
        int sum = 0;
        for (int i = 0; i < 10; ++i) {
            int remaining = 10 - i;
            int limit = min(20, 99 - sum - (remaining - 1));
            int value = rnd.next(1, limit);
            scores.push_back(value);
            sum += value;
        }
    } else {
        for (int i = 0; i < 10; ++i) {
            int value = (rnd.next(0, 2) == 0) ? rnd.next(1, 12) : rnd.next(70, 100);
            scores.push_back(value);
        }
    }

    for (int score : scores) println(score);

    return 0;
}
