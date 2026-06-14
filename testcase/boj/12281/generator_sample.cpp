#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int randomValueWithParity(int parity) {
    if (parity == 0) return rnd.next(-500, 500) * 2;
    return rnd.next(-499, 499) * 2 + 1;
}

int randomBoundedValue() {
    return rnd.next(-1000, 1000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(6, 14);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(6);
        int N = rnd.next(1, 35);
        vector<int> s;

        if (mode == 0) {
            N = rnd.next(1, 25);
            for (int i = 0; i < N; ++i) s.push_back(randomValueWithParity(1));
        } else if (mode == 1) {
            N = rnd.next(1, 25);
            for (int i = 0; i < N; ++i) s.push_back(randomValueWithParity(0));
        } else if (mode == 2) {
            N = rnd.next(2, 35);
            int startParity = rnd.next(2);
            for (int i = 0; i < N; ++i) {
                s.push_back(randomValueWithParity((startParity + i) % 2));
            }
        } else if (mode == 3) {
            N = rnd.next(5, 30);
            vector<int> pool = {-1000, -999, -2, -1, 0, 1, 2, 999, 1000};
            for (int i = 0; i < N; ++i) s.push_back(rnd.any(pool));
        } else if (mode == 4) {
            N = rnd.next(5, 35);
            int oddA = randomValueWithParity(1);
            int oddB = randomValueWithParity(1);
            int evenA = randomValueWithParity(0);
            int evenB = randomValueWithParity(0);
            vector<int> pool = {oddA, oddB, evenA, evenB};
            for (int i = 0; i < N; ++i) s.push_back(rnd.any(pool));
        } else {
            N = rnd.next(1, 35);
            for (int i = 0; i < N; ++i) s.push_back(randomBoundedValue());
            if (rnd.next(2)) sort(s.begin(), s.end());
            if (rnd.next(2)) reverse(s.begin(), s.end());
        }

        if (rnd.next(2)) shuffle(s.begin(), s.end());

        println(N);
        println(s);
    }

    return 0;
}
