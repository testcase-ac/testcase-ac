#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(3, 20);
    int type = rnd.next(0, 2);
    if (N < 4 && type == 2) type = rnd.next(0, 1);
    vector<int> a;
    if (type == 0) {
        // no triangle: Fibonacci-like growth
        a.resize(N);
        a[0] = 1;
        a[1] = rnd.next(2, 3);
        for (int i = 2; i < N; i++) {
            a[i] = a[i-1] + a[i-2] + rnd.next(0, 5);
        }
    } else if (type == 1) {
        // random but ensure a simple triangle
        a.resize(N);
        for (int i = 0; i < N; i++) a[i] = rnd.next(1, 100);
        int v = rnd.next(1, 50);
        a[0] = v; a[1] = v; a[2] = v;
    } else {
        // tricky: largest triple fails, next works
        a = {100, 60, 35, 30};
        for (int i = 4; i < N; i++) a.push_back(rnd.next(1, 30));
    }
    shuffle(a.begin(), a.end());
    println(N);
    for (int x : a) println(x);
    return 0;
}
