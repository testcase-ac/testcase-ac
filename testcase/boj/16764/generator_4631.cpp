#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cows
    int N = rnd.next(2, 10);

    // Domain size for flavor IDs: sometimes small, sometimes medium
    int maxF;
    if (rnd.next(0, 1) == 0) {
        // small domain to force many overlaps
        maxF = rnd.next(5, 20);
    } else {
        // larger domain for fewer overlaps
        maxF = rnd.next(20, 100);
    }

    // Probability to copy one flavor from a previous cow
    double pCopy = rnd.next();

    vector<vector<int>> cows;
    cows.reserve(N);

    for (int i = 0; i < N; i++) {
        set<int> s;
        // Optionally copy exactly one flavor from a random previous cow
        if (i > 0 && rnd.next() < pCopy) {
            int j = rnd.next(0, i - 1);
            int f = rnd.any(cows[j]);
            s.insert(f);
        }
        // Fill up to 5 distinct flavors
        while ((int)s.size() < 5) {
            s.insert(rnd.next(1, maxF));
        }
        // Convert to vector and shuffle order
        vector<int> v(s.begin(), s.end());
        shuffle(v.begin(), v.end());
        cows.push_back(v);
    }

    // Output
    println(N);
    for (auto &v : cows) {
        println(v);
    }
    return 0;
}
