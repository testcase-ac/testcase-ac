#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases between 3 and 7 to include a variety but stay hand-checkable
    int P = rnd.next(3, 7);

    vector<string> tests;
    // Always include all-H and all-T cases to catch trivial patterns
    tests.push_back(string(40, 'H'));
    tests.push_back(string(40, 'T'));

    // Predefined lengths for periodic patterns
    vector<int> periodLens = {2, 3, 4, 5};

    for (int i = 2; i < P; i++) {
        int tp = rnd.next(0, 4);
        string s;
        if (tp == 0) {
            // Uniform random 50-50
            for (int j = 0; j < 40; j++)
                s += rnd.next(0, 1) ? 'H' : 'T';
        } else if (tp == 1) {
            // H-heavy (70-90% H)
            int hprob = rnd.next(70, 90);
            for (int j = 0; j < 40; j++)
                s += (rnd.next(0, 99) < hprob ? 'H' : 'T');
        } else if (tp == 2) {
            // T-heavy (70-90% T)
            int tprob = rnd.next(70, 90);
            for (int j = 0; j < 40; j++)
                s += (rnd.next(0, 99) < tprob ? 'T' : 'H');
        } else if (tp == 3) {
            // Periodic pattern
            int k = rnd.any(periodLens);
            string pat;
            for (int j = 0; j < k; j++)
                pat += rnd.any(string("HT"));
            for (int j = 0; j < 40; j++)
                s += pat[j % k];
        } else {
            // Block pattern: 2-5 blocks of constant flips
            int b = rnd.next(2, 5);
            int rem = 40;
            vector<int> sizes;
            for (int j = 0; j < b - 1; j++) {
                int x = rnd.next(1, rem - (b - j - 1));
                sizes.push_back(x);
                rem -= x;
            }
            sizes.push_back(rem);
            for (int sz : sizes) {
                char c = rnd.any(string("HT"));
                s.append(sz, c);
            }
        }
        tests.push_back(s);
    }

    // Shuffle order so trivial cases aren't always first
    shuffle(tests.begin(), tests.end());

    // Output
    println(P);
    for (auto &t : tests) {
        printf("%s\n", t.c_str());
    }

    return 0;
}
