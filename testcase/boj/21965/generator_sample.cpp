#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 24);
    vector<int> a;

    if (mode == 0) {
        int cur = rnd.next(1, 20);
        a.push_back(cur);
        for (int i = 1; i < n; ++i) {
            cur += rnd.next(1, 5);
            a.push_back(cur);
        }
    } else if (mode == 1) {
        int cur = rnd.next(n + 20, n + 80);
        a.push_back(cur);
        for (int i = 1; i < n; ++i) {
            cur -= rnd.next(1, 5);
            if (cur < 1) cur = 1;
            a.push_back(cur);
        }
    } else if (mode == 2) {
        n = rnd.next(3, 24);
        int peak = rnd.next(1, n);
        int cur = rnd.next(1, 20);
        a.push_back(cur);
        for (int i = 2; i <= peak; ++i) {
            cur += rnd.next(1, 5);
            a.push_back(cur);
        }
        for (int i = peak + 1; i <= n; ++i) {
            cur -= rnd.next(1, 5);
            if (cur < 1) cur = 1;
            a.push_back(cur);
        }
    } else if (mode == 3) {
        int value = rnd.next(1, 100000);
        a.assign(n, value);
    } else if (mode == 4) {
        n = rnd.next(3, 24);
        int cur = rnd.next(30, 80);
        a.push_back(cur);
        for (int i = 1; i < n / 2; ++i) {
            cur -= rnd.next(1, 4);
            a.push_back(cur);
        }
        cur += rnd.next(1, 4);
        a.push_back(cur);
        while ((int)a.size() < n) {
            cur += rnd.next(1, 4);
            a.push_back(cur);
        }
    } else if (mode == 5) {
        n = rnd.next(4, 24);
        int cur = rnd.next(1, 20);
        int peak = rnd.next(2, n - 2);
        for (int i = 1; i <= peak; ++i) {
            cur += rnd.next(1, 4);
            a.push_back(cur);
        }
        cur -= rnd.next(1, 4);
        a.push_back(cur);
        cur += rnd.next(1, 4);
        while ((int)a.size() < n) {
            a.push_back(cur);
            cur += rnd.next(1, 4);
        }
    } else {
        n = rnd.next(2, 24);
        int cur = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            if (i > 0 && rnd.next(0, 4) == 0) {
                a.push_back(cur);
            } else {
                cur += rnd.next(-3, 5);
                if (cur < 1) cur = 1;
                if (cur > 100000) cur = 100000;
                a.push_back(cur);
            }
        }
    }

    println((int)a.size());
    println(a);
    return 0;
}
