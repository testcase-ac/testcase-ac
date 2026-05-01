#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int A, B, C, T;

    int scenario = rnd.next(0, 8);

    switch (scenario) {
        case 0: {
            // Fully random within constraints
            A = rnd.next(0, 5000);
            B = rnd.next(1, 60);
            C = rnd.next(1, 2000);
            T = rnd.next(1, 2000);
            break;
        }
        case 1: {
            // T <= 30 (no extra charge region)
            A = rnd.next(0, 5000);
            B = rnd.next(1, 60);
            C = rnd.next(1, 2000);
            T = rnd.next(1, 30);
            break;
        }
        case 2: {
            // Exactly T = 30 boundary
            A = rnd.next(0, 5000);
            B = rnd.next(1, 60);
            C = rnd.next(1, 2000);
            T = 30;
            break;
        }
        case 3: {
            // Just over 30: minimal extra time
            A = rnd.next(0, 5000);
            B = rnd.next(1, 60);
            C = rnd.next(1, 2000);
            T = 31;
            break;
        }
        case 4: {
            // 30 < T < 30 + B (but not multiple of B)
            A = rnd.next(0, 5000);
            B = rnd.next(2, 60); // need B >= 2
            C = rnd.next(1, 2000);
            int extra = rnd.next(1, B - 1); // strictly between 0 and B
            T = 30 + extra;
            break;
        }
        case 5: {
            // T = 30 + k * B to catch mistakes using T/B instead of (T-30)/B
            A = rnd.next(0, 5000);
            B = rnd.next(1, 60);
            C = rnd.next(1, 2000);
            int maxK = min(10, (2000 - 30) / B);
            int k = rnd.next(1, maxK);
            T = 30 + k * B;
            break;
        }
        case 6: {
            // Extreme low A and C, various T around boundaries and large T
            A = 0;
            B = rnd.next(1, 60);
            C = 1;
            int tChoice = rnd.next(0, 3);
            if (tChoice == 0) T = 1;
            else if (tChoice == 1) T = 30;
            else if (tChoice == 2) T = 31;
            else T = 2000;
            break;
        }
        case 7: {
            // Extreme high A and C and special B values, tricky T values
            A = 5000;
            B = rnd.any(vector<int>{1, 30, 60});
            C = 2000;
            vector<int> candidates;
            candidates.push_back(1);
            candidates.push_back(29);
            candidates.push_back(30);
            candidates.push_back(31);
            if (30 + B <= 2000) candidates.push_back(30 + B);
            if (30 + B - 1 >= 1 && 30 + B - 1 <= 2000) candidates.push_back(30 + B - 1);
            candidates.push_back(2000);
            T = rnd.any(candidates);
            break;
        }
        case 8: {
            // Subtask 2 style: B = 1 (per-minute additional charge)
            A = rnd.next(0, 5000);
            B = 1;
            C = rnd.next(1, 2000);
            T = rnd.next(1, 2000);
            break;
        }
    }

    println(A, B, C);
    println(T);

    return 0;
}
