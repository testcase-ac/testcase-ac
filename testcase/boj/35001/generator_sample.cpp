#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        m = 1;
        a = {rnd.next(1, 100)};
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        m = rnd.next(1, n);
        int value = rnd.next(1, 100);
        a.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        m = rnd.next(1, n);
        a.assign(n, rnd.next(1, 12));
        a[0] = rnd.next(70, 100);
        for (int i = 1; i < n; ++i) a[i] = rnd.next(1, 20);
    } else if (mode == 3) {
        n = rnd.next(2, 20);
        m = rnd.next(1, n);
        a.assign(n, rnd.next(1, 8));
        a[0] = rnd.next(1, 15);
        int dominantCount = rnd.next(1, n - 1);
        vector<int> idx;
        for (int i = 1; i < n; ++i) idx.push_back(i);
        shuffle(idx.begin(), idx.end());
        for (int i = 0; i < dominantCount; ++i) a[idx[i]] = rnd.next(75, 100);
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        m = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 2);
            if (bucket == 0) a.push_back(rnd.next(1, 5));
            else if (bucket == 1) a.push_back(rnd.next(6, 25));
            else a.push_back(rnd.next(80, 100));
        }
    } else {
        n = 20;
        int mMode = rnd.next(0, 2);
        if (mMode == 0) m = 1;
        else if (mMode == 1) m = n;
        else m = rnd.next(8, 13);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) a.push_back(rnd.next(90, 100));
            else a.push_back(rnd.next(1, 30));
        }
    }

    println(n, m);
    println(a);

    return 0;
}
