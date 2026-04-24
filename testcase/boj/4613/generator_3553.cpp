#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of packets
    int L = rnd.next(1, 10);
    // Weight options for varying line lengths
    vector<int> tvals = { -2, -1, 0, 1, 2 };

    for (int i = 0; i < L; i++) {
        // Choose a weight parameter to skew lengths small or large
        int t = rnd.any(tvals);
        // Base length between 0 and 19, skewed by t, then +1 => [1,20]
        int raw = rnd.wnext(20, t);
        int len = raw + 1;
        // Probability of a space in middle positions
        double spaceProb = rnd.next();

        string s;
        s.reserve(len);
        for (int j = 0; j < len; j++) {
            if (j == 0 || j == len - 1) {
                // Must be a letter at start and end
                char c = char('A' + rnd.next(0, 25));
                s.push_back(c);
            } else {
                // Middle chars: space with probability spaceProb, else letter
                if (rnd.next() < spaceProb) {
                    s.push_back(' ');
                } else {
                    char c = char('A' + rnd.next(0, 25));
                    s.push_back(c);
                }
            }
        }
        println(s);
    }

    // Termination line
    println("#");
    return 0;
}
