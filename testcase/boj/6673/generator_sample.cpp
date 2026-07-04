#include "testlib.h"

#include <vector>
using namespace std;

static int randomValue(int mode) {
    if (mode == 0) return rnd.next(0, 9);
    if (mode == 1) return rnd.any(vector<int>{0, 1, 2, 9998, 9999});
    return rnd.next(0, 9999);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(3, 8);
    for (int tc = 0; tc < cases; ++tc) {
        int mode = tc < 5 ? tc : rnd.next(0, 5);
        int k;
        int valueMode = rnd.next(0, 2);
        int index;

        if (mode == 0) {
            k = 1;
            index = rnd.any(vector<int>{0, 1, 2, rnd.next(3, 50), 999999999});
            valueMode = rnd.next(0, 1);
        } else if (mode == 1) {
            k = rnd.next(2, 6);
            index = rnd.next(0, k - 1);
            valueMode = rnd.next(0, 2);
        } else if (mode == 2) {
            k = rnd.next(2, 8);
            index = rnd.next(k, 80);
            valueMode = rnd.next(0, 1);
        } else if (mode == 3) {
            k = rnd.next(8, 20);
            index = rnd.next(1000, 1000000);
            valueMode = 2;
        } else if (mode == 4) {
            k = 100;
            index = rnd.any(vector<int>{99, 100, 101, rnd.next(1000, 1000000), 999999999});
            valueMode = rnd.next(1, 2);
        } else {
            k = rnd.next(1, 100);
            index = rnd.next(0, 999999999);
            valueMode = rnd.next(0, 2);
        }

        vector<int> initial(k);
        vector<int> coeff(k);
        for (int i = 0; i < k; ++i) {
            initial[i] = randomValue(valueMode);
            coeff[i] = randomValue(valueMode);
        }

        if (mode == 2) {
            for (int i = 0; i < k; ++i) coeff[i] = 0;
            coeff[rnd.next(0, k - 1)] = rnd.any(vector<int>{1, 9999});
        } else if (mode == 3) {
            for (int i = 0; i < k; ++i) {
                initial[i] = i % 2 == 0 ? 0 : 9999;
                coeff[i] = rnd.any(vector<int>{0, 1, 9999});
            }
        }

        printf("%d", k);
        for (int x : initial) printf(" %d", x);
        for (int x : coeff) printf(" %d", x);
        printf(" %d\n", index);
    }

    println(0);
    return 0;
}
