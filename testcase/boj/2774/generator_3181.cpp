#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 20);

    vector<long long> xs;
    xs.reserve(T);

    for (int i = 0; i < T; i++) {
        int type = rnd.next(0, 4);
        long long x;
        if (type == 0) {
            // Single digit
            x = rnd.next(1, 9);
        } else if (type == 1) {
            // Repeated same digit (length 2..9)
            int d = rnd.next(1, 9);
            int len = rnd.next(2, 9);
            string s(len, char('0' + d));
            x = stoll(s);
        } else if (type == 2) {
            // Large random near boundary
            x = rnd.next(100000000, 1000000000);
        } else if (type == 3) {
            // Random small multi-digit
            int len = rnd.next(2, 9);
            string s;
            s.push_back(char('1' + rnd.next(0, 8))); // first digit 1..9
            for (int j = 1; j < len; j++)
                s.push_back(char('0' + rnd.next(0, 9)));
            x = stoll(s);
        } else {
            // Exact maximum
            x = 1000000000;
        }
        xs.push_back(x);
    }

    // Shuffle testcases for diversity
    shuffle(xs.begin(), xs.end());

    // Output
    println(T);
    for (auto v : xs) println(v);

    return 0;
}
