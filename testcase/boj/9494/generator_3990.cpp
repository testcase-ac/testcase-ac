#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases (terminated by a 0)
    int T = rnd.next(1, 4);
    // Hyper-parameters for diversity
    vector<double> dens = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};
    vector<int> maxLens = {5, 10, 15, 20, 30, 40, 50, 80, 100};
    vector<int> biases = {-2, -1, 0, 1, 2};

    for (int tc = 0; tc < T; ++tc) {
        // Number of lines in this test case
        int n = rnd.next(1, 10);
        println(n);

        // Choose hyper-parameters for this test case
        double spDen = rnd.any(dens);
        int maxLen = rnd.any(maxLens);
        int bias = rnd.any(biases);

        for (int i = 0; i < n; ++i) {
            // Generate a line length from 1 to maxLen with bias
            int len = rnd.wnext(maxLen, bias) + 1;
            string s;
            s.reserve(len);
            // Build the line with spaces or printable ASCII
            for (int j = 0; j < len; ++j) {
                if (rnd.next() < spDen) {
                    s.push_back(' ');
                } else {
                    s.push_back(char(rnd.next(33, 126)));
                }
            }
            // Ensure at least one non-space character
            bool hasChar = false;
            for (char c : s) {
                if (c != ' ') { hasChar = true; break; }
            }
            if (!hasChar) {
                int pos = rnd.next(0, len - 1);
                s[pos] = char(rnd.next(33, 126));
            }
            println(s);
        }
    }

    // End marker
    println(0);
    return 0;
}
