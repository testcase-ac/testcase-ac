#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int k;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 12);
        k = rnd.next(1, 10);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = i + 1;
        shuffle(a.begin(), a.end());
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        k = rnd.next(1, 10);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            int target = i + 1;
            int steps = rnd.next(0, (target - 1) / k);
            a[i] = target - steps * k;
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        n = rnd.next(2, 18);
        k = rnd.next(1, 10);
        int value = rnd.next(1, 50);
        a.assign(n, value);
    } else if (mode == 3) {
        n = rnd.next(3, 20);
        k = rnd.next(2, 10);
        a.resize(n);
        int residue = rnd.next(0, k - 1);
        for (int i = 0; i < n; ++i) {
            int lo = residue == 0 ? k : residue;
            int maxStep = (50 - lo) / k;
            a[i] = lo + k * rnd.next(0, maxStep);
        }
    } else if (mode == 4) {
        n = rnd.next(20, 50);
        k = rnd.next(1, 10);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 50);
    } else if (mode == 5) {
        n = rnd.next(1, 50);
        k = rnd.next(1, 10);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(max(1, n - 5), 50);
    } else {
        n = rnd.any(vector<int>{1, 2, 49, 50});
        k = rnd.any(vector<int>{1, 2, 9, 10});
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                a[i] = rnd.next(1, min(50, n));
            } else {
                a[i] = rnd.next(1, 50);
            }
        }
    }

    println(n, k);
    println(a);
    return 0;
}
