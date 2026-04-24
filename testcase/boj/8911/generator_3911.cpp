#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Fixed interesting patterns from problem statement
    vector<string> fixed_cases = {
        "FFRRFF",      // straight line back and forth
        "FLFRFLBRBLB"  // sample zig-zag
    };

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);

    // Shuffle and possibly include up to first two fixed cases
    shuffle(fixed_cases.begin(), fixed_cases.end());
    int use_fixed = min((int)fixed_cases.size(), T);
    for (int i = 0; i < use_fixed; i++) {
        println(fixed_cases[i]);
    }

    // Generate the rest randomly
    for (int i = use_fixed; i < T; i++) {
        // length of this command string
        int len = rnd.next(1, 20);

        // mode: 0 = uniform, 1 = forward-heavy, 2 = turn-heavy
        int mode = rnd.next(0, 2);

        string s;
        s.reserve(len);
        for (int j = 0; j < len; j++) {
            if (mode == 0) {
                // uniform among F, B, L, R
                s.push_back(rnd.any(string("FBLR")));
            }
            else if (mode == 1) {
                // forward-heavy: 50% F, 25% B, 12.5% L, 12.5% R
                int x = rnd.next(1, 100);
                if (x <= 50) s.push_back('F');
                else if (x <= 75) s.push_back('B');
                else if (x <= 87) s.push_back('L');
                else s.push_back('R');
            }
            else {
                // turn-heavy: 45% L, 45% R, 5% F, 5% B
                int x = rnd.next(1, 100);
                if (x <= 45) s.push_back('L');
                else if (x <= 90) s.push_back('R');
                else if (x <= 95) s.push_back('F');
                else s.push_back('B');
            }
        }
        println(s);
    }

    return 0;
}
