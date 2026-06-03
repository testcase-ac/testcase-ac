#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    if (mode == 5) n = rnd.next(40, 120);

    vector<int> a;
    a.reserve(n);

    auto addRandomMixed = [&]() {
        int bucket = rnd.next(0, 99);
        if (bucket < 20) return rnd.next(-1000000, -2);
        if (bucket < 35) return -1;
        if (bucket < 50) return 0;
        if (bucket < 70) return 1;
        if (bucket < 90) return rnd.next(2, 30);
        return rnd.next(31, 1000000);
    };

    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            a.push_back(rnd.next(-10, 10));
        } else if (mode == 1) {
            a.push_back(rnd.next(0, 1) ? 1 : rnd.next(2, 1000000));
        } else if (mode == 2) {
            a.push_back(rnd.next(0, 1) ? 0 : rnd.next(-1000000, -1));
        } else if (mode == 3) {
            a.push_back(rnd.any(vector<int>{-1000000, -2, -1, 0, 1, 2, 1000000}));
        } else {
            a.push_back(addRandomMixed());
        }
    }

    shuffle(a.begin(), a.end());

    println(n);
    for (int x : a) println(x);

    return 0;
}
