#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of queries
    int N = rnd.next(1, 10);

    // Hyper-parameter: choose a maximum digit length
    vector<int> maxChoices = {1, 2, 3, 5, 10, 20};
    int maxLen = rnd.any(maxChoices);

    // Hyper-parameter: skew for digit length distribution
    // t>0 biases to larger, t<0 to smaller
    int t = rnd.next(-2, 2);

    // Output N
    println(N);

    // Generate each big integer K
    for (int i = 0; i < N; i++) {
        // digit count d in [1, maxLen], biased by wnext
        int d = rnd.wnext(maxLen, t) + 1;

        // first digit non-zero
        string s;
        s.reserve(d);
        s.push_back(char('1' + rnd.next(0, 8))); // '1'..'9'

        // remaining digits
        for (int j = 1; j < d; j++) {
            s.push_back(char('0' + rnd.next(0, 9)));
        }

        println(s);
    }

    return 0;
}
