#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIM = 1LL << 30;

    vector<long long> values;
    values.push_back(0);

    int powerCount = rnd.next(4, 12);
    long long p = 1;
    for (int i = 0; i < powerCount; ++i) {
        long long delta = rnd.next(-2, 2);
        for (long long sign : {-1LL, 1LL}) {
            long long x = sign * (p + delta);
            if (-LIM <= x && x <= LIM) values.push_back(x);
        }
        if (p <= LIM / 3) p *= 3;
    }

    int carryCases = rnd.next(4, 12);
    for (int i = 0; i < carryCases; ++i) {
        int k = rnd.next(0, 18);
        long long base = 1;
        for (int j = 0; j < k; ++j) base *= 3;

        long long x = (base - 1) / 2;
        long long offset = rnd.next(-3, 3);
        for (long long sign : {-1LL, 1LL}) {
            long long y = sign * (x + offset);
            if (-LIM <= y && y <= LIM) values.push_back(y);
        }
    }

    int randomCases = rnd.next(5, 25);
    for (int i = 0; i < randomCases; ++i) {
        int mode = rnd.next(0, 3);
        if (mode == 0) {
            values.push_back(rnd.next(-20, 20));
        } else if (mode == 1) {
            values.push_back(rnd.next(-100000, 100000));
        } else {
            values.push_back(rnd.next(-LIM, LIM));
        }
    }

    shuffle(values.begin(), values.end());
    int t = rnd.next(1, min<int>(40, values.size()));

    println(t);
    for (int i = 0; i < t; ++i) println(values[i]);

    return 0;
}
