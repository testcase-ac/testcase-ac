#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(0, 2);
    int N;
    vector<int> A;

    if (type == 0) {
        // Minimal impossible case
        N = 7;
        for (int i = 1; i <= 7; i++) A.push_back(i);
    }
    else if (type == 1) {
        // Guaranteed valid with a crafted 7-tuple
        N = rnd.next(7, 15);
        // Build a descending sequence P1 >= ... >= P7 satisfying constraints
        int P7 = rnd.next(1, 10);
        int P6 = P7 + rnd.next(0, 5);
        int P5 = P6 + rnd.next(0, 5);
        int P4 = P5 + rnd.next(0, 5);
        int sumLast4 = P4 + P5 + P6 + P7;
        int maxP3 = (sumLast4 - 1) / 2;
        if (maxP3 < P4) maxP3 = P4;
        int P3 = rnd.next(P4, maxP3);
        int maxd2 = sumLast4 - 2 * P3 - 1;
        if (maxd2 < 0) maxd2 = 0;
        int d2 = rnd.next(0, maxd2);
        int P2 = P3 + d2;
        int d1 = rnd.next(0, P3 - 1);
        int P1 = P2 + d1;
        vector<int> seeds = {P1, P2, P3, P4, P5, P6, P7};
        sort(seeds.begin(), seeds.end(), greater<int>());
        A = seeds;
        // Fill the rest with values <= P7 so that the crafted ones remain top-7
        for (int i = 0; i < N - 7; i++)
            A.push_back(rnd.next(1, P7));
        shuffle(A.begin(), A.end());
    }
    else {
        // Tricky case: one huge outlier that must be skipped
        N = rnd.next(8, 15);
        int huge = rnd.next(1000, 2000);
        A.push_back(huge);
        for (int i = 1; i < N; i++)
            A.push_back(rnd.next(1, 100));
        shuffle(A.begin(), A.end());
    }

    println(N);
    println(A);

    return 0;
}
