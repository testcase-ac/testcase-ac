#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    vector<int> a;
    int u = 0;

    if (mode == 0) {
        n = rnd.next(1, 25);
        a.assign(n, 3);
        u = rnd.next(0, n);
    } else if (mode == 1) {
        n = rnd.next(1, 30);
        int c1 = rnd.next(0, n);
        int c2 = n - c1;
        a.insert(a.end(), c1, 1);
        a.insert(a.end(), c2, 2);
        u = rnd.next(0, n);
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        int c1 = rnd.next(0, n);
        int c2 = rnd.next(0, n - c1);
        int c3 = n - c1 - c2;
        a.insert(a.end(), c1, 1);
        a.insert(a.end(), c2, 2);
        a.insert(a.end(), c3, 3);
        u = rnd.next(c1, c1 + c3);
    } else if (mode == 3) {
        n = rnd.next(2, 30);
        int c1 = rnd.next(1, n);
        int c2 = rnd.next(0, n - c1);
        int c3 = n - c1 - c2;
        a.insert(a.end(), c1, 1);
        a.insert(a.end(), c2, 2);
        a.insert(a.end(), c3, 3);
        u = rnd.next(0, c1 - 1);
    } else if (mode == 4) {
        n = rnd.next(2, 30);
        int c2 = rnd.next(1, n);
        int c1 = rnd.next(0, n - c2);
        int c3 = n - c1 - c2;
        a.insert(a.end(), c1, 1);
        a.insert(a.end(), c2, 2);
        a.insert(a.end(), c3, 3);
        u = rnd.next(n - c2 + 1, n);
    } else {
        n = 1;
        int kind = rnd.next(1, 3);
        a.push_back(kind);
        if (kind == 1) {
            u = 1;
        } else if (kind == 2) {
            u = 0;
        } else {
            u = rnd.next(0, 1);
        }
    }

    shuffle(a.begin(), a.end());

    println(n);
    println(a);
    println(u, n - u);

    return 0;
}
