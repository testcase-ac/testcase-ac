#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: small for hand-checking
    int T = rnd.next(1, 10);
    vector<pair<int,int>> cases;
    cases.reserve(T);

    for (int tc = 0; tc < T; ++tc) {
        // Hyper-parameter for A distribution (1 to 1000)
        int w = rnd.next(-3, 3);
        int A = rnd.wnext(1000, w) + 1; // in [1,1000]

        // Compute divisors of A
        vector<int> divs;
        for (int i = 1; i * i <= A; ++i) {
            if (A % i == 0) {
                divs.push_back(i);
                if (i * i != A) divs.push_back(A / i);
            }
        }
        // Hyper-parameter for choosing B
        int mode = rnd.next(0, 2);
        int B;
        if (mode == 0) {
            B = 1; // smallest divisor
        } else if (mode == 1) {
            B = A; // largest divisor
        } else {
            B = rnd.any(divs); // random divisor
        }
        cases.emplace_back(A, B);
    }

    // Optional shuffle to mix cases
    shuffle(cases.begin(), cases.end());

    // Output
    println(T);
    for (auto &p : cases) {
        println(p.first, p.second);
    }

    return 0;
}
