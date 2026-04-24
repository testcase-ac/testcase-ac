#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const int MAXV = 1000000000;
    vector<int> S = {36, 1225, 41616, 1413721, 48024900};
    int K = S.size();
    int T = rnd.next(3, 7);
    for (int ti = 0; ti < T; ti++) {
        int mode = rnd.next(0, 3);
        int a, b;
        if (mode == 0) {
            // no special in (a, b)
            int idx = rnd.next(0, K - 2);
            int low = S[idx] + 1;
            int high = S[idx + 1] - 1;
            a = rnd.next(low, min(low + 10, high - 1));
            b = rnd.next(a + 1, min(low + 20, high));
        }
        else if (mode == 1) {
            // exactly one special inside
            int idx = rnd.next(0, K - 1);
            int prev = (idx == 0 ? 0 : S[idx - 1]);
            int nextv = (idx + 1 < K ? S[idx + 1] : MAXV + 1);
            int low = prev + 1;
            int high = nextv - 1;
            int a_low = max(low, S[idx] - 10);
            int a_high = S[idx] - 1;
            a = rnd.next(a_low, a_high);
            int b_low = S[idx] + 1;
            int b_high = min(high, S[idx] + 10);
            b = rnd.next(b_low, b_high);
        }
        else if (mode == 2) {
            // multiple specials inside
            int i = rnd.next(0, K - 2);
            int j = rnd.next(i + 1, K - 1);
            int low = max(1, S[i] - rnd.next(1, 10));
            int high = min(MAXV, S[j] + rnd.next(1, 10));
            a = rnd.next(low, min(S[i], low + 5));
            int b_low = max(S[j], a + 1);
            int b_high = high;
            b = rnd.next(b_low, b_high);
        }
        else {
            // random small
            a = rnd.next(1, 50);
            b = rnd.next(a + 1, a + rnd.next(1, 50));
        }
        println(a, b);
    }
    println(0, 0);
    return 0;
}
