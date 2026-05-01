#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int pattern = rnd.next(0, 7);
    vector<int> a;
    int N = 0;

    switch (pattern) {
        case 0: { // Single element
            N = 1;
            a.resize(1);
            if (rnd.next(0, 1) == 0) {
                a[0] = 1; // answer should be 2
            } else {
                a[0] = rnd.next(2, 20); // answer should be 1
            }
            break;
        }
        case 1: { // All ones
            N = rnd.next(2, 20);
            a.assign(N, 1);
            break;
        }
        case 2: { // Random small, unsorted
            N = rnd.next(2, 10);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = rnd.next(1, 10);
            shuffle(a.begin(), a.end());
            break;
        }
        case 3: { // Random medium/large values
            N = rnd.next(5, 20);
            a.resize(N);
            for (int i = 0; i < N; ++i) {
                if (rnd.next(0, 3) == 0)
                    a[i] = rnd.next(1, 100000); // occasionally large
                else
                    a[i] = rnd.next(1, 200);    // usually small/medium
            }
            shuffle(a.begin(), a.end());
            break;
        }
        case 4: { // Sorted with an internal gap (classic greedy case)
            N = rnd.next(3, 10);
            a.clear();
            long long cur = 0;
            a.push_back(1);
            cur += 1;
            int gapPos = rnd.next(2, N); // 1-based position where gap is introduced

            for (int i = 2; i <= N; ++i) {
                if (i == gapPos) {
                    int val = (int)min(100000LL, cur + 2 + rnd.next(0, 3)); // create a gap
                    a.push_back(val);
                    cur += val;
                } else if (i < gapPos) {
                    int hi = (int)min(20LL, cur + 1);
                    int val = rnd.next(1, hi); // maintain continuity [1..cur+1]
                    a.push_back(val);
                    cur += val;
                } else {
                    int val = rnd.next(1, 50); // arbitrary tail
                    a.push_back(val);
                    cur += val;
                }
            }

            if (rnd.next(0, 1) == 1) {
                shuffle(a.begin(), a.end()); // maybe break sorting to catch missing sort
            }
            break;
        }
        case 5: { // First element > 1 (answer must be 1)
            N = rnd.next(2, 10);
            a.resize(N);
            a[0] = rnd.next(2, 20);
            for (int i = 1; i < N; ++i)
                a[i] = rnd.next(1, 30);
            if (rnd.next(0, 1) == 1)
                shuffle(a.begin(), a.end());
            break;
        }
        case 6: { // 1..k chain then a large jump
            N = rnd.next(3, 8);
            a.clear();
            long long cur = 0;
            for (int i = 0; i < N - 1; ++i) {
                a.push_back(1 + i); // 1,2,3,...
                cur += a.back();
            }
            int big = (int)min(100000LL, cur + rnd.next(2, 10)); // ensure jump > cur+1
            a.push_back(big);
            if (rnd.next(0, 1) == 1)
                shuffle(a.begin(), a.end());
            break;
        }
        case 7: { // Hand-crafted interesting examples
            int which = rnd.next(0, 3);
            if (which == 0) {
                a = {5, 1, 2};          // example from statement
            } else if (which == 1) {
                a = {2, 1, 4};          // unsorted variant critical for missing sort
            } else if (which == 2) {
                a = {2, 1, 2, 7};       // another statement example
            } else {
                a = {1, 1, 3, 4, 10};   // custom with several gaps
            }
            N = (int)a.size();
            if (rnd.next(0, 1) == 1)
                shuffle(a.begin(), a.end());
            break;
        }
    }

    println(N);
    println(a);

    return 0;
}
