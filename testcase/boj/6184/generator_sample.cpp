#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampSpeed(long long x) {
    return (int)min(1000000LL, max(1LL, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int N = rnd.next(1, 45);
    int M = rnd.next(1, N);
    int D = rnd.next(0, 120);
    int L = rnd.next(1, 1000000);

    if (mode == 0) {
        N = rnd.next(1, 8);
        M = 1;
        D = rnd.next(0, 20);
        L = rnd.next(1, 80);
    } else if (mode == 1) {
        N = rnd.next(2, 20);
        M = N;
        D = rnd.next(0, 5000);
        L = rnd.next(1, 1000000);
    } else if (mode == 2) {
        N = rnd.next(5, 35);
        M = rnd.next(1, min(N, 5));
        D = 0;
        L = rnd.next(1, 1000000);
    } else if (mode == 3) {
        N = rnd.next(5, 35);
        M = rnd.next(1, min(N, 6));
        D = rnd.next(1000, 5000);
        L = rnd.next(1, 1000000);
    } else if (mode == 4) {
        N = rnd.next(10, 45);
        M = rnd.next(1, min(N, 8));
        D = rnd.next(1, 300);
        L = rnd.next(1, 2000);
    } else {
        N = rnd.next(4, 25);
        M = rnd.next(1, N);
        D = rnd.next(0, 5000);
        L = rnd.next(999000, 1000000);
    }

    vector<int> speeds;
    speeds.reserve(N);
    for (int i = 0; i < N; ++i) {
        int laneDepth = i / max(1, M);
        long long boundary = (long long)L + (long long)D * laneDepth;
        int choice = rnd.next(0, 5);

        if (choice == 0) {
            speeds.push_back(clampSpeed(boundary));
        } else if (choice == 1) {
            speeds.push_back(clampSpeed(boundary - rnd.next(1, max(1, D + 3))));
        } else if (choice == 2) {
            speeds.push_back(clampSpeed(boundary + rnd.next(1, max(1, D + 3))));
        } else if (choice == 3) {
            speeds.push_back(rnd.next(1, 1000000));
        } else if (choice == 4) {
            speeds.push_back(clampSpeed(L + rnd.next(-20, 20)));
        } else {
            speeds.push_back(rnd.any(vector<int>{1, L, 1000000}));
        }
    }

    shuffle(speeds.begin(), speeds.end());

    println(N, M, D, L);
    for (int speed : speeds) {
        println(speed);
    }

    return 0;
}
