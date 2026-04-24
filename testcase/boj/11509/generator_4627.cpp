#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for hand-checkability
    int N = rnd.next(1, 10);
    int maxH = rnd.next(1, 20);

    // Diversity in patterns
    int type = rnd.next(0, 4);
    vector<int> H(N);

    if (type == 0) {
        // Fully random
        for (int i = 0; i < N; i++)
            H[i] = rnd.next(1, maxH);

    } else if (type == 1) {
        // Strictly increasing if possible
        if (maxH >= N) {
            int start = rnd.next(1, maxH - N + 1);
            for (int i = 0; i < N; i++)
                H[i] = start + i;
        } else {
            for (int i = 0; i < N; i++)
                H[i] = rnd.next(1, maxH);
        }

    } else if (type == 2) {
        // Strictly decreasing if possible
        if (maxH >= N) {
            int start = rnd.next(N, maxH);
            for (int i = 0; i < N; i++)
                H[i] = start - i;
        } else {
            for (int i = 0; i < N; i++)
                H[i] = rnd.next(1, maxH);
        }

    } else if (type == 3) {
        // Peak or valley shape
        int mid = rnd.next(0, N - 1);
        int leftLen = mid + 1;
        int rightLen = N - mid - 1;
        int minPeak = max(leftLen, rightLen + 1);
        if (maxH >= minPeak) {
            int peak = rnd.next(minPeak, maxH);
            for (int i = 0; i < N; i++) {
                if (i <= mid)
                    H[i] = peak - (mid - i);
                else
                    H[i] = peak - (i - mid);
            }
        } else {
            for (int i = 0; i < N; i++)
                H[i] = rnd.next(1, maxH);
        }

    } else {
        // Plateau-heavy sequence
        double p = rnd.next();
        H[0] = rnd.next(1, maxH);
        for (int i = 1; i < N; i++) {
            if (rnd.next() < p)
                H[i] = H[i - 1];
            else
                H[i] = rnd.next(1, maxH);
        }
    }

    // Output the test case
    println(N);
    println(H);

    return 0;
}
