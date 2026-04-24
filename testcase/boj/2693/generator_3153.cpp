#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases (small for hand-checking)
    int T = rnd.next(1, 10);
    println(T);

    for (int tc = 0; tc < T; tc++) {
        vector<int> a;
        a.reserve(10);

        // Hyper-parameter: choose distribution type
        int dist = rnd.next(0, 3);
        if (dist == 0) {
            // Uniform random over full range
            for (int i = 0; i < 10; i++)
                a.push_back(rnd.next(1, 1000));
        } else if (dist == 1) {
            // Few distinct values case
            int D = rnd.next(1, 3);
            set<int> s;
            while ((int)s.size() < D)
                s.insert(rnd.next(1, 1000));
            vector<int> vals(s.begin(), s.end());
            for (int i = 0; i < 10; i++)
                a.push_back(rnd.any(vals));
        } else if (dist == 2) {
            // Skewed to lower values mostly
            for (int i = 0; i < 10; i++) {
                if (rnd.next() < 0.7)
                    a.push_back(rnd.next(1, 100));
                else
                    a.push_back(rnd.next(1, 1000));
            }
        } else {
            // Boundary heavy: many 1's and 1000's
            vector<int> bounds = {1, 1000};
            for (int i = 0; i < 10; i++) {
                if (rnd.next() < 0.5)
                    a.push_back(rnd.any(bounds));
                else
                    a.push_back(rnd.next(1, 1000));
            }
        }

        // Output one test case
        println(a);
    }

    return 0;
}
