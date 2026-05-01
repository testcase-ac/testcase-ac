#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int TC = rnd.next(2, 4);
    for (int tc = 0; tc < TC; tc++) {
        int B = rnd.next(1, 8);
        int P = rnd.next(1, 20);
        println(-B, P);

        int pattern = rnd.next(0, 3);
        vector<int> C(B), T(B);

        if (pattern == 0) {
            // Fully random capacities and times
            for (int i = 0; i < B; i++) {
                C[i] = rnd.next(1, 5);
                T[i] = rnd.next(1, 100);
            }
        } else if (pattern == 1) {
            // Capacities ascending, times descending
            if (B == 1) {
                C[0] = rnd.next(1, 5);
            } else {
                for (int i = 0; i < B; i++)
                    C[i] = 1 + (i * 4) / (B - 1);
            }
            vector<int> times(B);
            for (int i = 0; i < B; i++)
                times[i] = rnd.next(20, 100);
            sort(times.begin(), times.end(), greater<int>());
            T = times;
        } else if (pattern == 2) {
            // Capacities descending, times ascending
            if (B == 1) {
                C[0] = rnd.next(1, 5);
            } else {
                for (int i = 0; i < B; i++)
                    C[i] = 5 - (i * 4) / (B - 1);
            }
            vector<int> times(B);
            for (int i = 0; i < B; i++)
                times[i] = rnd.next(5, 80);
            sort(times.begin(), times.end());
            T = times;
        } else {
            // Alternating small/large capacities, random times
            for (int i = 0; i < B; i++) {
                C[i] = (i % 2 == 0 ? 1 : 5);
                T[i] = rnd.next(1, 100);
            }
        }

        for (int i = 0; i < B; i++) {
            println(C[i], T[i]);
        }
    }
    println(0, 0);
    return 0;
}
