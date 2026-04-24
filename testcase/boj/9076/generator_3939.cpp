#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);

    // Probability of KIN-case
    double kinProb = rnd.next();

    for (int t = 0; t < T; t++) {
        bool isKin = rnd.next() < kinProb;
        int low_rem, high_rem;
        vector<int> mids(3);

        if (!isKin) {
            // Ensure remaining three scores diff <= 3
            low_rem = rnd.next(1, 10);
            int hrmax = min(10, low_rem + 3);
            high_rem = rnd.next(low_rem, hrmax);
            for (int i = 0; i < 3; i++) {
                mids[i] = rnd.next(low_rem, high_rem);
            }
        } else {
            // Ensure remaining three scores diff >= 4
            low_rem = rnd.next(1, 6); // so low_rem+4 <= 10
            high_rem = rnd.next(low_rem + 4, 10);
            for (int i = 0; i < 3; i++) {
                mids[i] = rnd.next(low_rem, high_rem);
            }
        }

        // Choose one extra low and one extra high to be removed
        int min_ext = rnd.next(1, low_rem);
        int max_ext = rnd.next(high_rem, 10);

        // Assemble and shuffle
        vector<int> scores = mids;
        scores.push_back(min_ext);
        scores.push_back(max_ext);
        shuffle(scores.begin(), scores.end());

        // Output one test case
        println(scores);
    }

    return 0;
}
