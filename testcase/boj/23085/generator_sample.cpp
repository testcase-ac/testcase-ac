#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n;
    int k;
    int heads;

    if (mode == 0) {
        n = rnd.next(1, 6);
        k = 1;
        heads = rnd.next(0, n);
    } else if (mode == 1) {
        n = rnd.next(2, 25);
        k = n;
        heads = rnd.any(vector<int>{0, 1, n - 1, n});
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        k = rnd.next(1, n);
        if (k % 2 == 0) {
            if (k == n) {
                --k;
            } else {
                ++k;
            }
        }
        heads = rnd.next(0, n);
    } else if (mode == 3) {
        n = rnd.next(2, 30);
        k = rnd.next(1, n);
        if (k % 2 == 1) {
            if (k == n) {
                --k;
            } else {
                ++k;
            }
        }
        heads = rnd.next(0, n);
    } else if (mode == 4) {
        n = rnd.next(5, 35);
        k = rnd.next(max(1, n - 4), n);
        heads = rnd.next(0, n);
    } else if (mode == 5) {
        n = rnd.next(10, 60);
        k = rnd.next(1, n);
        heads = rnd.any(vector<int>{0, 1, 2, n / 2, n - 2, n - 1, n});
    } else if (mode == 6) {
        n = rnd.next(100, 300);
        k = rnd.next(1, n);
        heads = rnd.next(0, n);
    } else {
        n = 3000;
        k = rnd.any(vector<int>{1, 2, 1499, 1500, 1501, 2999, 3000});
        heads = rnd.any(vector<int>{0, 1, 2, 1499, 1500, 1501, 2998, 2999, 3000});
    }

    vector<char> coins(n, 'T');
    for (int i = 0; i < heads; ++i) {
        coins[i] = 'H';
    }
    shuffle(coins.begin(), coins.end());

    string s(coins.begin(), coins.end());
    println(n, k);
    println(s);

    return 0;
}
