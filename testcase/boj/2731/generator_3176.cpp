#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);
    // Possible weights for biasing length distribution
    vector<int> weights = {-2, -1, 0, 1, 2};
    string last_digits = "1379";
    for (int ti = 0; ti < T; ti++) {
        // Choose length L in [1,10] with some bias
        int w = rnd.any(weights);
        int raw = rnd.wnext(10, w);  // in [0,9]
        int L = raw + 1;             // shift to [1,10]
        // Choose last digit among allowed endings
        char d = rnd.any(last_digits);
        string s;
        if (L == 1) {
            // Single-digit case
            s = string(1, d);
        } else {
            // Prefix of length L-1
            s.resize(L);
            // First digit cannot be '0'
            s[0] = char('1' + rnd.next(0, 8));
            // Middle digits
            for (int i = 1; i < L-1; i++) {
                s[i] = char('0' + rnd.next(0, 9));
            }
            // Last digit
            s[L-1] = d;
        }
        // Output the test case
        println(s);
    }
    return 0;
}
