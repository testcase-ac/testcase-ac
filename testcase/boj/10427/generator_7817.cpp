#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 7);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Choose N: small, medium, large
        double p = rnd.next();
        int N;
        if (p < 0.2) N = rnd.next(1, 5);
        else if (p < 0.7) N = rnd.next(6, 15);
        else N = rnd.next(16, 30);
        // Choose max value hyperparameter
        vector<int> maxOptions = {10, 50, 100, 1000};
        int maxVal = rnd.any(maxOptions);
        // Choose pattern type
        vector<int> types = {0, 1, 2, 3, 4, 5};
        int type = rnd.any(types);
        vector<int> A(N);
        if (type == 0) {
            // random
            for (int i = 0; i < N; i++) A[i] = rnd.next(1, maxVal);
        } else if (type == 1) {
            // sorted increasing
            for (int i = 0; i < N; i++) A[i] = rnd.next(1, maxVal);
            sort(A.begin(), A.end());
        } else if (type == 2) {
            // sorted decreasing
            for (int i = 0; i < N; i++) A[i] = rnd.next(1, maxVal);
            sort(A.begin(), A.end(), greater<int>());
        } else if (type == 3) {
            // all equal
            int v = rnd.next(1, maxVal);
            for (int i = 0; i < N; i++) A[i] = v;
        } else if (type == 4) {
            // two distinct values
            int v1 = rnd.next(1, maxVal - 1);
            int v2 = rnd.next(v1 + 1, maxVal);
            for (int i = 0; i < N; i++) {
                A[i] = (rnd.next() < 0.5 ? v1 : v2);
            }
        } else {
            // one big element
            for (int i = 0; i < N; i++) {
                A[i] = rnd.next(1, maxVal / 2);
            }
            int pos = rnd.next(0, N - 1);
            A[pos] = maxVal;
        }
        // Output test case
        printf("%d ", N);
        println(A);
    }
    return 0;
}
