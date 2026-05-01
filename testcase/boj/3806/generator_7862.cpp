#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int C = rnd.next(5, 8);
    println(C);
    for (int tc = 0; tc < C; ++tc) {
        // Length hyper-parameter: small, medium, or larger
        int N;
        int r = rnd.next(1, 10);
        if (r <= 3) N = rnd.next(1, 3);
        else if (r <= 7) N = rnd.next(4, 10);
        else N = rnd.next(11, 30);
        // Weights for S characters ('?', '0', '1')
        int wq = rnd.next(0, 3);
        int w0 = rnd.next(0, 3);
        int w1 = rnd.next(0, 3);
        if (wq + w0 + w1 == 0) wq = 1;
        string alpha;
        alpha.append(wq, '?');
        alpha.append(w0, '0');
        alpha.append(w1, '1');
        // Build S and T
        string S, T;
        S.reserve(N);
        T.reserve(N);
        for (int i = 0; i < N; ++i) {
            S.push_back(rnd.any(alpha));
            // T only '0' or '1'
            T.push_back(rnd.next(0, 1) ? '1' : '0');
        }
        println(S);
        println(T);
    }
    return 0;
}
