#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000;
    vector<int> special = {
        2, 3, 4, 5, 6, 7, 8, 9, 10,
        16, 27, 32, 64, 81, 121, 128, 243, 256, 512, 729, 1024,
        999983, 999999, 1000000
    };

    int T = rnd.next(1, 20);
    vector<int> values;
    values.reserve(T);

    while ((int)values.size() < T) {
        int mode = rnd.next(0, 6);
        int n = 2;

        if (mode == 0) {
            n = rnd.next(2, 40);
        } else if (mode == 1) {
            n = rnd.any(special);
        } else if (mode == 2) {
            int base = rnd.next(2, 20);
            long long x = base;
            int exponent = rnd.next(2, 6);
            for (int i = 1; i < exponent && x * base <= maxN; ++i) x *= base;
            n = (int)x;
        } else if (mode == 3) {
            int a = rnd.next(2, 1000);
            int b = rnd.next(2, maxN / a);
            n = a * b;
        } else if (mode == 4) {
            n = maxN - rnd.next(0, 1000);
        } else if (mode == 5) {
            int p = rnd.any(vector<int>{97, 101, 997, 1009, 7919, 99991});
            int mult = rnd.next(1, maxN / p);
            n = p * mult;
        } else {
            n = rnd.next(2, maxN);
        }

        values.push_back(n);
    }

    shuffle(values.begin(), values.end());

    println(T);
    for (int n : values) println(n);
    return 0;
}
