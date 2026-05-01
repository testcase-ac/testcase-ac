#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with bias to small, large, or uniform
    int N;
    double pN = rnd.next();
    if (pN < 0.2) {
        N = rnd.next(1, 5);
    } else if (pN < 0.6) {
        // bias towards large N
        N = rnd.wnext(50, 2) + 1;  // [1..50], biased to high
    } else {
        N = rnd.next(1, 50);
    }

    // Number of distinct cycle-classes
    int C = rnd.next(1, N);

    // Assign at least one word per class, distribute remainder
    vector<int> counts(C, 1);
    int rem = N - C;
    while (rem > 0) {
        counts[rnd.next(0, C - 1)]++;
        rem--;
    }

    vector<string> words;
    words.reserve(N);
    const string letters = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < C; i++) {
        // Choose word length L
        int L;
        double p = rnd.next();
        if (p < 0.1) {
            L = 1;
        } else if (p < 0.3) {
            L = rnd.next(2, 5);
        } else if (p < 0.6) {
            L = rnd.next(6, 15);
        } else if (p < 0.9) {
            L = rnd.next(16, 50);
        } else {
            L = rnd.next(1, 50);
        }

        // Generate base word, sometimes periodic
        string base;
        if (L > 1 && rnd.next() < 0.2) {
            // find divisors < L
            vector<int> divs;
            for (int d = 1; d * d <= L; d++) {
                if (L % d == 0) {
                    if (d < L) divs.push_back(d);
                    int d2 = L / d;
                    if (d2 != d && d2 < L) divs.push_back(d2);
                }
            }
            if (!divs.empty()) {
                int d = rnd.any(divs);
                // build a small pattern of length d
                string pat;
                for (int j = 0; j < d; j++) {
                    pat += rnd.any(letters);
                }
                // repeat pattern
                base.clear();
                for (int k = 0; k < L / d; k++) base += pat;
            }
        }
        if (base.empty()) {
            base.resize(L);
            for (int j = 0; j < L; j++) {
                base[j] = rnd.any(letters);
            }
        }

        // Generate rotated variants
        for (int t = 0; t < counts[i]; t++) {
            int k = (L == 0 ? 0 : rnd.next(0, L - 1));
            string w = base.substr(k) + base.substr(0, k);
            words.push_back(w);
        }
    }

    // Shuffle the final list
    shuffle(words.begin(), words.end());

    // Output
    println(N);
    for (auto &w : words) {
        println(w);
    }

    return 0;
}
