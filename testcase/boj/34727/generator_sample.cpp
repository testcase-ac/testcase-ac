#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MIN_N = 3;
    const int MAX_N = 100000;

    vector<int> values;
    int mode = rnd.next(5);

    if (mode == 0) {
        int caseCount = rnd.next(1, 8);
        for (int i = 0; i < caseCount; ++i) {
            values.push_back(rnd.next(MIN_N, 30));
        }
    } else if (mode == 1) {
        int caseCount = rnd.next(2, 12);
        int parity = rnd.next(0, 1);
        for (int i = 0; i < caseCount; ++i) {
            int n = rnd.next(MIN_N, 200);
            if (n % 2 != parity) {
                ++n;
            }
            if (n > 200) {
                n -= 2;
            }
            values.push_back(n);
        }
    } else if (mode == 2) {
        vector<int> anchors = {MIN_N, 4, 5, 6, 7, 99, 100, 101, 99999, MAX_N};
        shuffle(anchors.begin(), anchors.end());
        int caseCount = rnd.next(2, 8);
        for (int i = 0; i < caseCount; ++i) {
            values.push_back(anchors[i]);
        }
    } else if (mode == 3) {
        int caseCount = rnd.next(4, 20);
        for (int i = 0; i < caseCount; ++i) {
            values.push_back(rnd.next(MAX_N - 1000, MAX_N));
        }
    } else {
        int caseCount = rnd.next(5, 25);
        vector<int> anchors = {MIN_N, 4, 5, 99999, MAX_N};
        for (int i = 0; i < caseCount; ++i) {
            if (rnd.next(0, 2) == 0) {
                values.push_back(rnd.any(anchors));
            } else {
                values.push_back(rnd.next(MIN_N, MAX_N));
            }
        }
    }

    println((int)values.size());
    for (int n : values) {
        println(n);
    }

    return 0;
}
