#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 25);
    int mode = rnd.next(0, 3);
    vector<int> a(n);

    if (mode == 0) {
        int labels = rnd.next(1, min(n, 5));
        for (int& value : a) value = rnd.next(1, labels);
    } else if (mode == 1) {
        int dominant = rnd.next(1, n);
        int count = rnd.next((n + 1) / 2, n);
        for (int i = 0; i < count; ++i) a[i] = dominant;
        for (int i = count; i < n; ++i) {
            a[i] = rnd.next(1, n - 1);
            if (a[i] >= dominant) ++a[i];
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) a[i] = i + 1;
        shuffle(a.begin(), a.end());
    } else {
        int labels = rnd.next(1, min(n, 5));
        for (int i = 0; i < n; ++i) a[i] = i * labels / n + 1;
    }

    println(n);
    println(a);
}
