#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of seminars
    int N = rnd.next(1, 10);
    // Duration T: small or potentially large
    int T;
    if (rnd.next() < 0.5)
        T = rnd.next(1, 10);
    else
        T = rnd.next(1, 1000000000);
    // Generate a_i with either clustered or uniform strategy
    vector<int> a(N);
    if (rnd.next() < 0.5) {
        // Clustered generation
        int K = rnd.next(1, N);
        int maxRange = (T < 100 ? 100 : T);
        vector<int> centers(K);
        for (int i = 0; i < K; i++)
            centers[i] = rnd.next(1, maxRange);
        int spread = (T > 1 ? min(T - 1, 5) : 0);
        for (int i = 0; i < N; i++) {
            if (rnd.next() < 0.8) {
                int c = rnd.any(centers);
                int d = rnd.next(0, spread);
                if (rnd.next() < 0.5) a[i] = c + d;
                else a[i] = c - d;
                if (a[i] < 1) a[i] = 1;
                if (a[i] > 1000000000) a[i] = 1000000000;
            } else {
                a[i] = rnd.next(1, 1000000000);
            }
        }
    } else {
        // Fully uniform generation
        for (int i = 0; i < N; i++)
            a[i] = rnd.next(1, 1000000000);
    }
    // Output
    println(N, T);
    println(a);
    return 0;
}
