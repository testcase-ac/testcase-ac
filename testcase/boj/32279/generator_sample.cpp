#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int p;
    int q;
    int r;
    int s;
    int a1;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        n = rnd.any(vector<int>{1, 2, 3, 20});
        p = rnd.any(vector<int>{1, 10});
        q = rnd.any(vector<int>{1, 10});
        r = rnd.any(vector<int>{1, 10});
        s = rnd.any(vector<int>{1, 10});
        a1 = rnd.any(vector<int>{1, 100});
    } else if (mode == 1) {
        n = rnd.next(1, 8);
        p = q = r = s = rnd.next(1, 10);
        a1 = rnd.next(1, 100);
    } else if (mode == 2) {
        n = rnd.next(10, 20);
        p = rnd.next(1, 3);
        q = rnd.next(1, 3);
        r = rnd.next(8, 10);
        s = rnd.next(8, 10);
        a1 = rnd.next(1, 20);
    } else if (mode == 3) {
        n = rnd.next(10, 20);
        p = rnd.next(8, 10);
        q = rnd.next(8, 10);
        r = rnd.next(1, 3);
        s = rnd.next(1, 3);
        a1 = rnd.next(1, 20);
    } else if (mode == 4) {
        n = rnd.next(15, 20);
        p = rnd.next(8, 10);
        q = rnd.next(1, 10);
        r = rnd.next(8, 10);
        s = rnd.next(1, 10);
        a1 = rnd.next(80, 100);
    } else {
        n = rnd.next(1, 20);
        vector<int> coeffs;
        for (int i = 0; i < 4; ++i) coeffs.push_back(rnd.next(1, 10));
        if (rnd.next(0, 1)) sort(coeffs.begin(), coeffs.end());
        p = coeffs[0];
        q = coeffs[1];
        r = coeffs[2];
        s = coeffs[3];
        a1 = rnd.next(1, 100);
    }

    println(n);
    println(p, q, r, s);
    println(a1);

    return 0;
}
