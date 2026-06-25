#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (rnd.next(0, 9) == 0) {
        n = rnd.next(80, 200);
    } else {
        n = rnd.next(1, 40);
    }

    vector<int> a(n);

    if (mode == 0) {
        int value = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) a[i] = value;
    } else if (mode == 1) {
        int ones = rnd.next(0, min(n, 3));
        for (int i = 0; i < ones; ++i) a[i] = 1;
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) a[i] = 1;
        int zeros = rnd.next(0, min(n, 3));
        for (int i = 0; i < zeros; ++i) a[i] = 0;
        shuffle(a.begin(), a.end());
    } else if (mode == 3) {
        int start = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) a[i] = (start + i) % 2;
    } else if (mode == 4) {
        int value = rnd.next(0, 1);
        for (int i = 0; i < n;) {
            int len = rnd.next(1, min(8, n - i));
            for (int j = 0; j < len; ++j) a[i + j] = value;
            i += len;
            value ^= 1;
        }
    } else {
        int percentOnes = rnd.any(vector<int>{20, 35, 50, 65, 80});
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 100) <= percentOnes;
    }

    println(n);
    println(a);

    return 0;
}
