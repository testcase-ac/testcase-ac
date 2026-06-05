#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int randomA(int mode) {
    constexpr int MAX_A = (1 << 20) - 1;

    if (mode == 0) return rnd.next(2, 80);
    if (mode == 1) return rnd.next(2, 2000);
    if (mode == 2) return rnd.next(MAX_A - 2000, MAX_A);
    if (mode == 3) return 1 << rnd.next(1, 19);
    if (mode == 4) return rnd.next(1, (MAX_A - 1) / 2) * 2 + 1;

    int value = 1;
    int factors = rnd.next(2, 6);
    for (int i = 0; i < factors; ++i) {
        int p = rnd.any(vector<int>{2, 3, 5, 7, 11, 13});
        if (value > MAX_A / p) break;
        value *= p;
    }
    return max(2, value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    constexpr int MAX_A = (1 << 20) - 1;

    int target = rnd.next(8, 35);
    set<int> values;

    vector<int> anchors = {2, 3, 4, 5, 12, MAX_A - 1, MAX_A};
    shuffle(anchors.begin(), anchors.end());
    for (int a : anchors) {
        if ((int)values.size() >= target) break;
        if (rnd.next(0, 1)) values.insert(a);
    }

    while ((int)values.size() < target) {
        values.insert(randomA(rnd.next(0, 5)));
    }

    vector<int> output(values.begin(), values.end());
    shuffle(output.begin(), output.end());

    for (int a : output) println(a);
    println(0);

    return 0;
}
