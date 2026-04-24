#include "testlib.h"
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Precompute powers of 3 up to 10
    vector<int> pw(11, 1);
    for (int i = 1; i <= 10; i++) pw[i] = pw[i-1] * 3;

    vector<pair<int,int>> tests;
    // Some fixed small cases
    tests.emplace_back(0, 1);    // 0 in all C_n
    tests.emplace_back(1, 1);    // 1 in all C_n
    tests.emplace_back(1, 2);    // 0.5 fails at C1
    tests.emplace_back(1, 6);    // ~0.1666 fails at C2
    tests.emplace_back(5, 18);   // ~0.2777 fails at C3
    
    // Random failure cases: introduce first '1' digit at pos k in base-3
    int cntFail = rnd.next(2, 4);
    vector<int> two = {0,2};
    vector<int> tri = {0,1,2};
    for (int it = 0; it < cntFail; it++) {
        int k = rnd.next(1, 10); // first position of digit '1'
        vector<int> d(10, 0);
        for (int i = 0; i < 10; i++) {
            if (i < k-1) d[i] = rnd.any(two);
            else if (i == k-1) d[i] = 1;
            else d[i] = rnd.any(tri);
        }
        int num = 0;
        for (int i = 0; i < 10; i++) {
            num += d[i] * pw[10-1-i];
        }
        tests.emplace_back(num, pw[10]);
    }
    // Random success cases: all digits in {0,2}, so in C_10
    int cntSucc = rnd.next(2, 4);
    for (int it = 0; it < cntSucc; it++) {
        vector<int> d(10, 0);
        for (int i = 0; i < 10; i++) {
            d[i] = rnd.any(two);
        }
        int num = 0;
        for (int i = 0; i < 10; i++) {
            num += d[i] * pw[10-1-i];
        }
        tests.emplace_back(num, pw[10]);
    }

    // Shuffle to mix cases
    shuffle(tests.begin(), tests.end());
    // Output
    println((int)tests.size());
    for (auto &pr : tests) {
        println(pr.first, pr.second);
    }
    return 0;
}
