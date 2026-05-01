#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = rnd.next(0, 5);
    int N;
    vector<long long> P;
    switch (type) {
        case 0:
            // Single heap of size 1 (losing position)
            N = 1;
            P.push_back(1LL);
            break;
        case 1:
            // Single heap, small winning size
            N = 1;
            P.push_back(rnd.next(2LL, 10LL));
            break;
        case 2:
            // Multiple heaps all size 1 (misère Nim trivial)
            N = rnd.next(2, 10);
            P.assign(N, 1LL);
            break;
        case 3:
            // Multiple heaps all size >=2, small values
            N = rnd.next(2, 10);
            for (int i = 0; i < N; i++)
                P.push_back(rnd.next(2LL, 10LL));
            break;
        case 4:
            // Mix of ones and small heaps
            N = rnd.next(2, 10);
            for (int i = 0; i < N; i++) {
                if (rnd.next() < 0.5)
                    P.push_back(1LL);
                else
                    P.push_back(rnd.next(2LL, 10LL));
            }
            shuffle(P.begin(), P.end());
            break;
        case 5:
            // Larger number of heaps with big values and some ones
            N = rnd.next(10, 100);
            for (int i = 0; i < N; i++) {
                if (rnd.next() < 0.3)
                    P.push_back(1LL);
                else
                    P.push_back(rnd.next(2LL, 2000000000LL));
            }
            shuffle(P.begin(), P.end());
            break;
    }
    println(N);
    println(P);
    return 0;
}
