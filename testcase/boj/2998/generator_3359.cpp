#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: skew length distribution toward small or large
    vector<int> weights = {-1, 0, 1};
    int t = rnd.any(weights);
    int L = rnd.wnext(10, t) + 1;  // length in [1,10]

    string s;
    double specialRate = 0.3;
    if (rnd.next() < specialRate) {
        // Generate one of a few special patterns
        vector<int> patterns = {0, 1, 2};
        int pat = rnd.any(patterns);
        s.resize(L);
        if (pat == 0) {
            // all ones
            for (int i = 0; i < L; i++) s[i] = '1';
        } else if (pat == 1) {
            // one followed by zeros
            s[0] = '1';
            for (int i = 1; i < L; i++) s[i] = '0';
        } else {
            // alternating starting with 1
            for (int i = 0; i < L; i++) s[i] = (i % 2 ? '0' : '1');
        }
    } else {
        // Random bits with random density, ensuring first bit is 1
        double p = rnd.next();  // probability of '1'
        s.resize(L);
        s[0] = '1';
        for (int i = 1; i < L; i++)
            s[i] = (rnd.next() < p ? '1' : '0');
    }

    // Output a single binary string
    println(s);

    return 0;
}
