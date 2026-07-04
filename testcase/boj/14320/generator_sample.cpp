#include "testlib.h"
#include <vector>

using namespace std;

int pickN() {
    int mode = rnd.next(0, 4);
    if (mode == 0) return rnd.next(1, 5);
    if (mode == 1) return rnd.next(6, 20);
    if (mode == 2) return rnd.next(21, 60);
    if (mode == 3) return rnd.next(61, 100);
    return rnd.any(vector<int>{1, 2, 3, 99, 100});
}

int pickM() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return 1;
    if (mode == 1) return rnd.next(2, 10);
    if (mode == 2) return rnd.next(11, 1000);
    if (mode == 3) return rnd.next(1001, 1000000);
    if (mode == 4) return rnd.next(1000001, 1000000000);
    return rnd.any(vector<int>{2, 7, 1000000007 - 7, 1000000000});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 100);
    println(t);

    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int n = pickN();
        int m = pickM();
        println(n, m);
    }

    return 0;
}
