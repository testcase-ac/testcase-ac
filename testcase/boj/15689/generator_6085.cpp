#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of stations
    int n = rnd.next(2, 6);
    // Number of buses
    int maxM = min(15, n * (n - 1));
    int m = rnd.next(n, maxM);
    // Deadline time
    long long k = rnd.next(10LL, 200LL);

    // Output m, n and k
    println(m, n);
    println(k);

    for (int i = 0; i < m; i++) {
        // pick distinct stations a -> b
        int a = rnd.next(0, n - 1);
        int b = rnd.next(0, n - 2);
        if (b >= a) b++;
        // departure time s in [0, k-1], arrival t in (s, k]
        long long s = rnd.next(0LL, k - 1);
        long long d = rnd.next(1LL, k - s);
        long long t = s + d;
        // probability p: some 0, some 1, others from {0.1..0.9}
        double r = rnd.next();
        double p;
        if (r < 0.1) p = 0.0;
        else if (r < 0.3) p = 1.0;
        else {
            int num = rnd.next(1, 9);
            p = num / 10.0;
        }
        // print bus
        printf("%d %d %lld %lld %.6f\n", a, b, s, t, p);
    }
    return 0;
}
