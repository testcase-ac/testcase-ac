#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    bool medium = (rnd.next(0, 9) == 0);
    int N = medium ? rnd.next(20, 50) : rnd.next(1, 10);
    int M = medium ? rnd.next(200, 1000) : rnd.next(10, 100);
    vector<int> A(N), B(N);
    int type = rnd.next(0, 4);
    switch (type) {
        case 0:
            for (int i = 0; i < N; i++) {
                int v = rnd.next(0, M);
                A[i] = v;
                B[i] = v;
            }
            break;
        case 1:
            for (int i = 0; i < N; i++) {
                A[i] = rnd.next(0, M/5);
                B[i] = rnd.next(M/2, M);
            }
            break;
        case 2:
            for (int i = 0; i < N; i++) {
                A[i] = rnd.next(M/2, M);
                B[i] = rnd.next(0, M/5);
            }
            break;
        case 3:
            for (int i = 0; i < N; i++) {
                A[i] = rnd.next(0, M);
                B[i] = rnd.next(0, M);
            }
            break;
        case 4: {
            int half = N / 2;
            for (int i = 0; i < half; i++) {
                A[i] = rnd.next(0, M/5);
                B[i] = rnd.next(0, M);
            }
            for (int i = half; i < N; i++) {
                A[i] = rnd.next(0, M);
                B[i] = rnd.next(0, M/5);
            }
            vector<int> ids(N);
            iota(ids.begin(), ids.end(), 0);
            shuffle(ids.begin(), ids.end());
            vector<int> A2(N), B2(N);
            for (int i = 0; i < N; i++) {
                A2[i] = A[ids[i]];
                B2[i] = B[ids[i]];
            }
            A.swap(A2);
            B.swap(B2);
            break;
        }
    }
    println(N);
    println(A);
    println(B);
    return 0;
}
