#include "testlib.h"
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases (excluding the final 0 0)
    int T = rnd.next(3, 7);

    vector<pair<long long, long long>> cases;
    // Always include some edge cases
    cases.emplace_back(1LL, 1LL);              // smallest equal case
    cases.emplace_back(1LL, 1000000000LL);     // extreme range

    // Generate the rest randomly with diverse scales
    while ((int)cases.size() < T) {
        double p = rnd.next();
        long long A, B;
        if (p < 0.33) {
            // small values
            A = rnd.next(1LL, 100LL);
            B = rnd.next(A, 100LL);
        } else if (p < 0.66) {
            // medium values
            A = rnd.next(1LL, 1000000LL);
            B = rnd.next(A, 1000000LL);
        } else {
            // large values
            A = rnd.next(1LL, 1000000000LL);
            B = rnd.next(A, 1000000000LL);
        }
        cases.emplace_back(A, B);
    }

    // Shuffle to avoid fixed positions
    shuffle(cases.begin(), cases.end());

    // Output all cases then the terminator
    for (auto &pr : cases) {
        println(pr.first, pr.second);
    }
    println(0, 0);

    return 0;
}
