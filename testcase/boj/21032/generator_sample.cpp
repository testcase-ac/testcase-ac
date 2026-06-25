#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int makeOdd(int oddFactor) {
    int value = oddFactor;
    if (value % 2 == 0) --value;
    value = max(1, min(value, 999999));
    return value;
}

int makeEven(int oddFactor, int twos) {
    int value = makeOdd(oddFactor);
    for (int i = 0; i < twos && value <= 500000; ++i) value *= 2;
    if (value % 2 == 1) value *= 2;
    return min(value, 1000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 30);
    if (mode == 6) n = rnd.next(60, 180);
    if (mode == 7) n = rnd.next(2, 200);

    vector<int> a;
    a.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) a.push_back(makeOdd(rnd.next(1, 999)));
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) a.push_back(makeEven(rnd.next(1, 999), rnd.next(1, 8)));
    } else if (mode == 2) {
        int oddCount = rnd.next(0, n);
        for (int i = 0; i < oddCount; ++i) a.push_back(makeOdd(rnd.next(1, 4999)));
        for (int i = oddCount; i < n; ++i) a.push_back(makeEven(rnd.next(1, 4999), rnd.next(1, 6)));
    } else if (mode == 3) {
        int baseOdd = rnd.any(vector<int>{3, 5, 7, 9, 15, 21, 25, 45});
        for (int i = 0; i < n; ++i) {
            int oddPart = baseOdd * rnd.next(1, 99);
            a.push_back(rnd.next(0, 1) ? makeOdd(oddPart) : makeEven(oddPart, rnd.next(1, 5)));
        }
    } else if (mode == 4) {
        vector<int> values = {1, 2, 3, 4, 6, 8, 12, 16, 999983, 1000000};
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(values));
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            int twos = i % 10;
            int oddPart = rnd.next(1, 97);
            a.push_back(makeEven(oddPart, twos + 1));
        }
        if (n > 1) a[rnd.next(0, n - 1)] = makeOdd(rnd.next(1, 999));
    } else if (mode == 6) {
        int oddCount = rnd.next(max(0, n / 2 - 5), min(n, n / 2 + 5));
        for (int i = 0; i < oddCount; ++i) a.push_back(makeOdd(rnd.next(1, 999999)));
        for (int i = oddCount; i < n; ++i) a.push_back(makeEven(rnd.next(1, 999999), rnd.next(1, 3)));
    } else {
        for (int i = 0; i < n; ++i) {
            int oddPart = rnd.next(1, 500000) * 2 - 1;
            if (rnd.next(0, 2) == 0) {
                a.push_back(oddPart);
            } else {
                int multiplier = rnd.any(vector<int>{2, 4, 8, 16, 32});
                while (oddPart * multiplier > 1000000) multiplier /= 2;
                a.push_back(oddPart * multiplier);
            }
        }
    }

    shuffle(a.begin(), a.end());
    println(static_cast<int>(a.size()));
    println(a);

    return 0;
}
