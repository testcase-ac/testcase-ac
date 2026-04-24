#include "testlib.h"
#include <vector>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Size hyper-parameter: small but varied
    int N = rnd.next(2, 10);
    // Scenario hyper-parameter for diverse sequences
    int scenario = rnd.next(4); // 0,1,2,3

    vector<int> ds(N);
    if (scenario == 0) {
        // Uniform random decimals [0.0, 9.9]
        for (int i = 0; i < N; i++) {
            ds[i] = rnd.next(0, 99);
        }
    } else if (scenario == 1) {
        // Mix low (<1) and high (>=1)
        for (int i = 0; i < N; i++) {
            if (rnd.next() < 0.6)
                ds[i] = rnd.next(0, 9);    // 0.0 to 0.9
            else
                ds[i] = rnd.next(10, 99);  // 1.0 to 9.9
        }
    } else if (scenario == 2) {
        // Ensure one good run of >1.0 values
        int st = rnd.next(0, N - 2);
        int len = rnd.next(2, N - st);
        for (int i = 0; i < N; i++) {
            if (i >= st && i < st + len)
                ds[i] = rnd.next(11, 99);  // 1.1 to 9.9
            else
                ds[i] = rnd.next(0, 99);
        }
    } else {
        // Include zeros to reset products
        for (int i = 0; i < N; i++) {
            if (rnd.next() < 0.2)
                ds[i] = 0;
            else
                ds[i] = rnd.next(1, 99);  // 0.1 to 9.9
        }
    }

    // Output
    println(N);
    for (int d : ds) {
        printf("%.1f\n", d / 10.0);
    }
    return 0;
}
