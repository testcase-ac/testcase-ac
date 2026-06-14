#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    long long n;
    vector<long long> credits;

    if (mode == 0) {
        n = rnd.next(1, 20);
        credits.push_back(n);
    } else if (mode == 1) {
        n = rnd.next(2, 40);
        long long a = rnd.next(1LL, n - 1);
        credits.push_back(a);
        credits.push_back(n - a);
    } else if (mode == 2) {
        n = rnd.next(5, 80);
        long long remaining = n;
        while (remaining > 0) {
            long long take = rnd.next(1LL, min(remaining, 5LL));
            credits.push_back(take);
            remaining -= take;
        }
    } else if (mode == 3) {
        n = rnd.next(3, 60);
        long long first = rnd.next(1LL, n - 1);
        long long second = rnd.next(n - first, 2 * n - first);
        credits.push_back(first);
        credits.push_back(second);
    } else if (mode == 4) {
        n = rnd.next(10, 200);
        long long sum = 0;
        while (sum < n) {
            long long value = rnd.next(1LL, min(n, 25LL));
            credits.push_back(value);
            sum += value;
        }
    } else {
        n = rnd.next(1, 100);
        int count = rnd.next(1, 12);
        long long remaining = n;
        for (int i = 0; i < count - 1; ++i) {
            long long value = rnd.next(1LL, max(1LL, remaining));
            credits.push_back(value);
            remaining = max(1LL, remaining - value);
        }
        credits.push_back(remaining);
    }

    int distractors = rnd.next(0, 8);
    for (int i = 0; i < distractors; ++i) {
        int type = rnd.next(0, 2);
        if (type == 0) {
            credits.push_back(rnd.next(1LL, min(2 * n, 100000000LL)));
        } else if (2 * n < 100000000LL) {
            credits.push_back(rnd.next(2 * n + 1, min(100000000LL, 2 * n + 1000)));
        } else {
            credits.push_back(100000000LL);
        }
    }

    shuffle(credits.begin(), credits.end());

    println(n, static_cast<int>(credits.size()));
    for (long long credit : credits) {
        println(credit);
    }

    return 0;
}
