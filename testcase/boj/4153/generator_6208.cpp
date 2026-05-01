#include "testlib.h"
#include <vector>
#include <array>
#include <algorithm>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Primitive Pythagorean triples for right cases
    vector<array<int,3>> prim = {
        {3, 4, 5}, {5,12,13}, {7,24,25}, {8,15,17},
        {9,40,41}, {11,60,61}, {12,35,37}, {20,21,29},
        {28,45,53}
    };

    // Number of test-cases
    int T = rnd.next(1, 10);
    // Probability of generating a right triangle
    double p_right = rnd.next(3, 7) / 10.0;

    vector<array<int,3>> cases;
    cases.reserve(T);

    for (int i = 0; i < T; i++) {
        if (rnd.next() < p_right) {
            // Generate a right triangle by scaling a primitive
            auto pr = rnd.any(prim);
            int mx = max({pr[0], pr[1], pr[2]});
            int maxk = 29999 / mx;
            int k = rnd.next(1, maxk);
            int a = pr[0] * k;
            int b = pr[1] * k;
            int c = pr[2] * k;
            vector<int> s = {a, b, c};
            shuffle(s.begin(), s.end());
            cases.push_back({s[0], s[1], s[2]});
        } else {
            // Generate a non-right triangle (or non-triangle)
            int a = rnd.next(1, 29999);
            int b = rnd.next(1, 29999);
            int c = rnd.next(1, 29999);
            // Avoid the unlikely event of accidental Pythagorean equality
            while (int64_t(a)*a + int64_t(b)*b == int64_t(c)*c) {
                c = rnd.next(1, 29999);
            }
            vector<int> s = {a, b, c};
            shuffle(s.begin(), s.end());
            cases.push_back({s[0], s[1], s[2]});
        }
    }

    // Output the test cases
    for (auto &t : cases) {
        println(t[0], t[1], t[2]);
    }
    // Termination line
    println(0, 0, 0);

    return 0;
}
