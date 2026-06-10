#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> randomBoundedSum(int count, int target) {
    vector<int> values;
    int remaining = target;

    for (int i = 0; i < count; ++i) {
        int left = count - i - 1;
        int lo = max(-100, remaining - 100 * left);
        int hi = min(100, remaining + 100 * left);
        int value = rnd.next(lo, hi);
        values.push_back(value);
        remaining -= value;
    }

    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int answer;

    if (mode == 0) {
        n = 2;
        answer = rnd.next(-100, 100);
    } else if (mode == 1) {
        n = rnd.next(3, 8);
        answer = 0;
    } else if (mode == 2) {
        n = rnd.next(3, 20);
        answer = rnd.any(vector<int>{-100, -99, 99, 100});
    } else if (mode == 3) {
        n = rnd.next(20, 100);
        answer = rnd.next(-20, 20);
    } else {
        n = rnd.next(3, 30);
        answer = rnd.next(-100, 100);
    }

    vector<int> cards = randomBoundedSum(n - 1, answer);
    cards.push_back(answer);
    shuffle(cards.begin(), cards.end());

    println(n);
    println(cards);

    return 0;
}
