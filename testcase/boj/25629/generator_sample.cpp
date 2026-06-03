#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(9, 20);
    } else if (mode == 2) {
        n = rnd.next(21, 40);
    } else if (mode == 3) {
        n = rnd.next(95, 100);
    } else if (mode == 4) {
        n = 1;
    } else {
        n = rnd.next(2, 100);
    }

    int neededOdds = (n + 1) / 2;
    int oddCount;
    if (mode == 0 || mode == 3 || mode == 4) {
        oddCount = neededOdds;
    } else if (mode == 1) {
        oddCount = max(0, neededOdds - rnd.next(1, min(neededOdds, 3)));
    } else if (mode == 2) {
        oddCount = min(n, neededOdds + rnd.next(1, min(n - neededOdds, 3)));
    } else {
        oddCount = rnd.next(0, n);
    }

    vector<int> values;
    values.reserve(n);

    int oddStyle = rnd.next(0, 2);
    int evenStyle = rnd.next(0, 2);

    for (int i = 0; i < oddCount; ++i) {
        int x;
        if (oddStyle == 0) {
            x = rnd.next(0, 49) * 2 + 1;
        } else if (oddStyle == 1) {
            x = rnd.any(vector<int>{1, 3, 5, 95, 97, 99});
        } else {
            x = rnd.next(1, 7) * 2 - 1;
        }
        values.push_back(x);
    }

    for (int i = oddCount; i < n; ++i) {
        int x;
        if (evenStyle == 0) {
            x = rnd.next(1, 50) * 2;
        } else if (evenStyle == 1) {
            x = rnd.any(vector<int>{2, 4, 6, 96, 98, 100});
        } else {
            x = rnd.next(1, 8) * 2;
        }
        values.push_back(x);
    }

    shuffle(values.begin(), values.end());

    println(n);
    println(values);

    return 0;
}
