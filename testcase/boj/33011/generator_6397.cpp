#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Choose N small for hand-verification
        int N = rnd.next(1, 15);
        // Decide pattern type
        int type;
        if (N == 1) type = rnd.next(0, 1);  // only odd or even
        else type = rnd.next(0, 4);
        int O = 0, E = 0;
        int n = N;
        if (type == 0) {
            // all odds
            O = n; E = 0;
        } else if (type == 1) {
            // all evens
            O = 0; E = n;
        } else if (type == 2) {
            // equal counts
            if (n % 2 == 1) n--;
            O = n / 2;
            E = n / 2;
        } else if (type == 3) {
            // odds one more than evens
            E = n / 2;
            O = n - E;
        } else {
            // evens one more than odds
            O = n / 2;
            E = n - O;
        }
        // Generate array
        vector<int> A;
        for (int i = 0; i < O; i++) {
            // odd between 1 and 99
            int x = rnd.next(1, 50) * 2 - 1;
            A.push_back(x);
        }
        for (int i = 0; i < E; i++) {
            // even between 2 and 100
            int x = rnd.next(1, 50) * 2;
            A.push_back(x);
        }
        // If we trimmed N for equal case, adjust N
        N = (int)A.size();
        shuffle(A.begin(), A.end());
        // Output test case
        println(N);
        println(A);
    }
    return 0;
}
