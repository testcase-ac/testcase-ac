#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 35);
    vector<int> a;
    a.reserve(n);

    if (mode == 0) {
        int start = rnd.next(-10000, 10000 - n + 1);
        for (int i = 0; i < n; ++i) a.push_back(start + i);
    } else if (mode == 1) {
        int start = rnd.next(-10000 + n - 1, 10000);
        for (int i = 0; i < n; ++i) a.push_back(start - i);
    } else if (mode == 2) {
        int lo = rnd.next(-10000, -9990);
        int hi = rnd.next(9990, 10000);
        for (int i = 0; i < n; ++i) a.push_back(i % 2 == 0 ? lo : hi);
    } else if (mode == 3) {
        int value = rnd.next(-10000, 10000);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                a.push_back(rnd.next(-3, 3));
            } else {
                a.push_back(value);
            }
        }
    } else if (mode == 4) {
        int lo = rnd.next(-20, 0);
        int hi = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, hi));
    } else {
        vector<int> choices = {-10000, -9999, -1, 0, 1, 9999, 10000};
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(choices));
        shuffle(a.begin(), a.end());
    }

    println(n);
    for (int value : a) println(value);

    return 0;
}
