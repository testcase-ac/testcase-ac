#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

long long lcmLimited(long long a, long long b) {
    return a / gcd(a, b) * b;
}

vector<long long> boxSizes(int a, int b) {
    vector<long long> sizes;
    for (int cut = 1; 2 * cut < a && 2 * cut < b; ++cut) {
        sizes.push_back(1LL * cut * (a - 2 * cut) * (b - 2 * cut));
    }
    sort(sizes.begin(), sizes.end(), greater<long long>());
    return sizes;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int a;
    int b;

    if (mode == 0) {
        a = 7;
        b = rnd.next(7, 12);
    } else if (mode == 1) {
        a = rnd.next(7, 16);
        b = rnd.next(a, 24);
    } else if (mode == 2) {
        a = rnd.next(25, 60);
        b = rnd.next(a, 100);
    } else if (mode == 3) {
        a = rnd.next(70, 100);
        b = rnd.next(a, 100);
    } else if (mode == 4) {
        a = rnd.next(7, 100);
        b = a;
    } else {
        a = rnd.next(7, 100);
        b = rnd.next(a, 100);
    }

    vector<long long> sizes = boxSizes(a, b);
    long long s1 = sizes[0];
    long long s2 = sizes[1];
    long long s3 = sizes[2];
    long long period = lcmLimited(lcmLimited(s1, s2), s3);

    long long n;
    do {
        if (mode == 0) {
            n = rnd.next(1, 5000);
        } else if (mode == 3) {
            n = rnd.next(900000000, 1000000000);
        } else {
            n = rnd.next(1, 1000000000);
        }
    } while (n % s1 == 0 || n % s2 == 0 || n % s3 == 0);

    long long leftLimit = min(n - 1, period - 1);
    long long rightLimit = min(1000000000LL - n, period - 1);
    long long left = rnd.next(0LL, leftLimit);
    long long right = rnd.next(0LL, rightLimit);

    if (left == 0 && right == 0) {
        if (rightLimit > 0) {
            right = 1;
        } else {
            left = 1;
        }
    }

    long long f = n - left;
    long long g = n + right;

    println(a, b, n % s1, n % s2, n % s3, f, g);
    return 0;
}
