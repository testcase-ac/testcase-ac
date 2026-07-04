#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    int x;
    if (mode == 4) {
        n = rnd.next(60, 80);
        x = rnd.next(150, 200);
    } else {
        n = rnd.next(1, 14);
        x = rnd.next(1, 40);
    }

    int k;
    if (mode == 0) {
        k = rnd.any(vector<int>{1, n});
    } else if (mode == 4) {
        k = rnd.next(max(1, n - 20), n);
    } else {
        k = rnd.next(1, n);
    }

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            a[i] = rnd.any(vector<int>{0, x});
        } else if (mode == 1) {
            int center = x / 2;
            int radius = min(x, rnd.next(0, max(1, x / 5)));
            a[i] = rnd.next(max(0, center - radius), min(x, center + radius));
        } else if (mode == 2) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) a[i] = rnd.next(0, min(x, 3));
            else if (bucket == 1) a[i] = rnd.next(max(0, x - 3), x);
            else a[i] = rnd.next(0, x);
        } else if (mode == 3) {
            vector<int> choices;
            int choiceCount = rnd.next(1, min(5, x + 1));
            for (int j = 0; j < choiceCount; ++j) choices.push_back(rnd.next(0, x));
            a[i] = rnd.any(choices);
        } else {
            a[i] = rnd.next(0, x);
        }
    }

    shuffle(a.begin(), a.end());

    println(n, k, x);
    for (int value : a) {
        println(value, x - value);
    }

    return 0;
}
