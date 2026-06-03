#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<int> cases;

    if (mode == 0) {
        int t = rnd.next(1, 8);
        for (int i = 0; i < t; ++i) cases.push_back(rnd.next(1, 6));
    } else if (mode == 1) {
        cases = {1, 2, 3, 19, 20};
        shuffle(cases.begin(), cases.end());
        cases.resize(rnd.next(2, (int)cases.size()));
    } else if (mode == 2) {
        int t = rnd.next(5, 15);
        int lo = rnd.next(1, 15);
        int hi = rnd.next(lo, 20);
        for (int i = 0; i < t; ++i) cases.push_back(rnd.next(lo, hi));
    } else if (mode == 3) {
        int t = rnd.next(10, 30);
        int a = rnd.next(1, 10);
        int b = rnd.next(11, 20);
        for (int i = 0; i < t; ++i) cases.push_back((i % 2 == 0) ? a : b);
    } else {
        int t = rnd.next(20, 60);
        for (int i = 0; i < t; ++i) {
            int bias = rnd.next(0, 2);
            if (bias == 0) cases.push_back(rnd.next(1, 4));
            else if (bias == 1) cases.push_back(rnd.next(17, 20));
            else cases.push_back(rnd.next(1, 20));
        }
    }

    println((int)cases.size());
    for (int n : cases) println(n);

    return 0;
}
