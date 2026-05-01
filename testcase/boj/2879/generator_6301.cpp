#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of lines
    int tN = rnd.any(vector<int>{-1, 0, 1});
    int N = rnd.wnext(12, tN) + 1;  // N in [1,12], skewed by tN
    // Initial maximum tabs
    int tA = rnd.any(vector<int>{-1, 0, 1});
    int maxInit = rnd.wnext(6, tA); // max initial tabs in [0,5]
    vector<int> A(N), B(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(0, maxInit);
        B[i] = A[i];
    }
    // Apply a few group operations to build target B
    int segCnt = rnd.next(1, min(N, 3));
    for (int s = 0; s < segCnt; s++) {
        int tL = rnd.any(vector<int>{-1, 0, 1});
        int segLen = rnd.wnext(N, tL) + 1;      // segment length in [1,N]
        int l = rnd.next(0, N - segLen);
        int r = l + segLen - 1;
        int op = rnd.next(0, 1);                // 0 = add, 1 = delete
        int cnt = rnd.next(1, 3);               // number of tabs to add/delete
        for (int j = l; j <= r; j++) {
            if (op == 0)
                B[j] += cnt;
            else
                B[j] = max(0, B[j] - cnt);
        }
    }
    // Output
    println(N);
    println(A);
    println(B);
    return 0;
}
