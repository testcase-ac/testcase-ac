#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 25);
    if (mode == 5) n = rnd.next(70, 100);

    vector<int> candies(n, 1);
    int sum = n;

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            candies[i] = rnd.next(1, 10);
            sum += candies[i] - 1;
        }
    } else if (mode == 1) {
        int target = rnd.next(n, min(1000, 10 * n));
        int remaining = target - n;
        for (int i = 0; i < n && remaining > 0; ++i) {
            int add = rnd.next(0, min(9, remaining));
            candies[i] += add;
            remaining -= add;
        }
        for (int i = 0; i < n && remaining > 0; ++i) {
            int add = min(10 - candies[i], remaining);
            candies[i] += add;
            remaining -= add;
        }
        sum = target;
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            candies[i] = rnd.next(1, 3);
            sum += candies[i] - 1;
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            candies[i] = rnd.next(8, 10);
            sum += candies[i] - 1;
        }
    } else {
        for (int i = 0; i < n; ++i) {
            candies[i] = (i % 2 == 0) ? rnd.next(1, 2) : rnd.next(9, 10);
            sum += candies[i] - 1;
        }
    }

    int t;
    if (mode == 0) {
        t = rnd.next(1, 1000);
    } else if (mode == 1) {
        t = sum;
    } else if (mode == 2) {
        t = min(1000, sum + rnd.next(1, 30));
    } else if (mode == 3) {
        t = max(1, sum - rnd.next(1, min(30, sum)));
    } else if (mode == 4) {
        int delta = rnd.any(vector<int>{-1, 0, 1});
        t = min(1000, max(1, sum + delta));
    } else {
        t = rnd.next(900, 1000);
    }

    shuffle(candies.begin(), candies.end());

    println(t);
    println(n);
    println(candies);
    return 0;
}
