#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

const int MAX_ID = 1000000 - 1;

void gen_case(int pattern, int Gmax, vector<int>& ids);

void gen_case(int pattern, int Gmax, vector<int>& ids) {
    ids.clear();

    if (Gmax <= 0) return;

    switch (pattern) {
        case 0: { // single student
            ids.push_back(rnd.next(0, MAX_ID));
            return;
        }
        case 1: { // small random numbers
            if (Gmax == 1) {
                gen_case(0, Gmax, ids);
                return;
            }
            int upperG = min(6, Gmax);
            int G = rnd.next(2, upperG);
            set<int> used;
            while ((int)used.size() < G) {
                int x = rnd.next(0, 50);
                used.insert(x);
            }
            for (int x : used) ids.push_back(x);
            shuffle(ids.begin(), ids.end());
            return;
        }
        case 2: { // gcd-trap triple like (0,6,10) scaled and shifted
            if (Gmax < 3) {
                if (Gmax == 1) gen_case(0, Gmax, ids);
                else gen_case(1, Gmax, ids);
                return;
            }
            int baseArr[3] = {0, 6, 10};
            vector<int> scales = {1, 2, 3, 5, 7};
            int s = rnd.any(scales);
            int maxBase = baseArr[2] * s;
            int maxShift = MAX_ID - maxBase;
            int shift = rnd.next(0, maxShift);
            for (int i = 0; i < 3; ++i) {
                ids.push_back(baseArr[i] * s + shift);
            }
            shuffle(ids.begin(), ids.end());
            return;
        }
        case 3: { // LCM-based pattern with 360360
            if (Gmax == 1) {
                gen_case(0, Gmax, ids);
                return;
            }
            const int L = 360360;
            int K;
            if (Gmax == 2) {
                K = 2;
            } else {
                vector<int> choices = {2, 3};
                K = rnd.any(choices);
                if (K > Gmax) K = 2;
            }
            int maxA = MAX_ID - (K - 1) * L;
            if (maxA < 0) { // very unlikely, but just in case
                gen_case(1, Gmax, ids);
                return;
            }
            int a = rnd.next(0, maxA);
            for (int i = 0; i < K; ++i) {
                ids.push_back(a + i * L);
            }
            shuffle(ids.begin(), ids.end());
            return;
        }
        case 4: { // parity-based, answer likely 2 (two students, odd difference)
            if (Gmax < 2) {
                gen_case(0, Gmax, ids);
                return;
            }
            int a = rnd.next(0, MAX_ID);
            int b;
            if (a % 2 == 0) {
                // need odd
                int lo = 1;
                int hi = (MAX_ID % 2 == 1 ? MAX_ID : MAX_ID - 1);
                b = rnd.next(lo / 2, hi / 2) * 2 + 1; // random odd
            } else {
                // need even
                int lo = 0;
                int hi = (MAX_ID % 2 == 0 ? MAX_ID : MAX_ID - 1);
                b = rnd.next(lo / 2, hi / 2) * 2; // random even
            }
            if (b == a) {
                b ^= 1; // ensure different and parity conditions preserved
            }
            ids.push_back(a);
            ids.push_back(b);
            shuffle(ids.begin(), ids.end());
            return;
        }
        case 5: { // random big numbers near the upper limit
            if (Gmax == 1) {
                gen_case(0, Gmax, ids);
                return;
            }
            int upperG = min(10, Gmax);
            int G = rnd.next(2, upperG);
            set<int> used;
            while ((int)used.size() < G) {
                int x = rnd.next(MAX_ID / 2, MAX_ID);
                used.insert(x);
            }
            for (int x : used) ids.push_back(x);
            shuffle(ids.begin(), ids.end());
            return;
        }
    }

    // Fallback (should not reach)
    gen_case(0, Gmax, ids);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide number of test cases with some variability
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) N = rnd.next(1, 2);
    else if (mode == 1) N = rnd.next(3, 5);
    else N = rnd.next(6, 7);

    // Total number of students across all cases, keep small (<=40)
    int totalBudget = rnd.next(N, 40);
    int remaining = totalBudget;

    println(N);

    for (int t = 0; t < N; ++t) {
        int testsLeft = N - t - 1;
        int Gmax = remaining - testsLeft; // ensure at least 1 per remaining test
        if (Gmax < 1) Gmax = 1;

        int pattern = rnd.next(0, 5);
        vector<int> ids;
        gen_case(pattern, Gmax, ids);

        // Safety: ensure at least 1 id and not exceeding Gmax
        if (ids.empty() || (int)ids.size() > Gmax) {
            ids.clear();
            gen_case(0, Gmax, ids);
        }

        int G = (int)ids.size();
        remaining -= G;

        println(G);
        for (int x : ids) {
            println(x);
        }
    }

    return 0;
}
