#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 3;
    } else if (mode == 1) {
        n = rnd.next(4, 8);
    } else if (mode == 2) {
        n = rnd.next(9, 25);
    } else if (mode == 3) {
        n = rnd.next(26, 80);
    } else {
        n = rnd.next(3, 40);
    }

    int penguin;
    if (mode == 0) {
        penguin = 2;
    } else if (mode == 1) {
        penguin = rnd.any(vector<int>{2, n - 1});
    } else {
        penguin = rnd.next(2, n - 1);
    }

    int upper = rnd.any(vector<int>{10, 100, 1000, 1000000000});
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (i == penguin) {
            a[i] = -1;
            continue;
        }
        a[i] = rnd.next(1, upper);
    }

    if (mode >= 2) {
        int leftMin = rnd.next(1, penguin - 1);
        int rightMin = rnd.next(penguin + 1, n);
        a[leftMin] = rnd.next(1, min(upper, 7));
        a[rightMin] = rnd.next(1, min(upper, 7));

        for (int i = 1; i <= n; ++i) {
            if (i == penguin || i == leftMin || i == rightMin) continue;
            if (rnd.next(0, 3) == 0) {
                a[i] = rnd.next(max(1, upper / 2), upper);
            }
        }
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) printf(" ");
        printf("%lld", a[i]);
    }
    printf("\n");

    return 0;
}
