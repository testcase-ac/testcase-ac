#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int T = 10;
    println(T);

    vector<int> baseK = {1, 2, 3, 4, 5, 10, 50, 997, 100000, 1000000};
    shuffle(baseK.begin(), baseK.end());

    for (int caseIndex = 0; caseIndex < T; ++caseIndex) {
        int mode = rnd.next(0, 5);
        int K = baseK[caseIndex];

        if (mode == 0) {
            K = rnd.next(1, 12);
        } else if (mode == 1) {
            K = rnd.next(13, 200);
        } else if (mode == 2) {
            K = rnd.next(900, 1200);
        } else if (mode == 3) {
            K = rnd.next(90000, 110000);
        } else if (mode == 4) {
            K = rnd.next(999000, 1000000);
        }

        vector<int> queries;
        queries.push_back(1);
        if (K > 1) queries.push_back(K);
        if (K > 2) queries.push_back((K + 1) / 2);

        int targetN = rnd.next(1, 100);
        int pattern = rnd.next(0, 3);
        while ((int)queries.size() < targetN) {
            int value;
            if (pattern == 0) {
                value = rnd.next(1, K);
            } else if (pattern == 1) {
                int width = min(K, rnd.next(1, 20));
                value = rnd.next(1, width);
            } else if (pattern == 2) {
                int width = min(K, rnd.next(1, 20));
                value = K - rnd.next(0, width - 1);
            } else {
                value = queries[rnd.next((int)queries.size())];
            }
            queries.push_back(value);
        }

        shuffle(queries.begin(), queries.end());
        println(K);
        println((int)queries.size(), queries);
    }

    return 0;
}
