#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N
    int sizeType = rnd.next(0, 3);
    int N;
    if (sizeType == 0) N = rnd.next(2, 5);
    else if (sizeType == 1) N = rnd.next(6, 10);
    else if (sizeType == 2) N = rnd.next(11, 15);
    else N = rnd.next(16, 25);

    // Choose Q
    int maxQ = min(25, 2 * N);
    int Q = rnd.next(1, maxQ);

    vector<int> A(N + 1);

    auto maxH = [&](int i) -> int {
        return min(N - i, i);
    };

    // Scenario for initial A
    int scen = rnd.next(0, 5); // 0..5

    if (scen == 0) {
        // All zeros (subtask 2 style)
        for (int i = 0; i <= N; i++) A[i] = 0;
    } else if (scen == 1) {
        // All positive for internal positions (subtask 3 style)
        A[0] = A[N] = 0;
        for (int i = 1; i <= N - 1; i++) {
            int mh = maxH(i);
            if (mh <= 0) A[i] = 0;
            else A[i] = rnd.next(1, mh);
        }
    } else if (scen == 2) {
        // Fully random within bounds
        for (int i = 0; i <= N; i++) {
            int mh = maxH(i);
            A[i] = rnd.next(0, mh);
        }
    } else if (scen == 3) {
        // Mountain-like profile
        int mid = rnd.next(0, N);
        int mh_mid = maxH(mid);
        int H = (mh_mid > 0 ? rnd.next(1, mh_mid) : 0);
        for (int i = 0; i <= N; i++) {
            int mh = maxH(i);
            if (H == 0) {
                A[i] = 0;
                continue;
            }
            int dist = abs(i - mid);
            int base = max(0, H - dist);
            int delta = rnd.next(-1, 1);
            int val = base + delta;
            if (val < 0) val = 0;
            if (val > mh) val = mh;
            A[i] = val;
        }
        A[0] = 0;
        A[N] = 0;
    } else if (scen == 4) {
        // Sparse spikes
        for (int i = 0; i <= N; i++) A[i] = 0;
        if (N > 1) {
            int numSpikes = rnd.next(1, min(5, N - 1));
            vector<int> positions;
            for (int i = 1; i <= N - 1; i++) positions.push_back(i);
            shuffle(positions.begin(), positions.end());
            for (int k = 0; k < numSpikes; k++) {
                int i = positions[k];
                int mh = maxH(i);
                if (mh > 0) {
                    int makeMax = rnd.next(0, 1);
                    if (makeMax) A[i] = mh;
                    else A[i] = rnd.next(1, mh);
                }
            }
        }
    } else {
        // scen == 5: checker / extremes
        A[0] = A[N] = 0;
        for (int i = 1; i <= N - 1; i++) {
            int mh = maxH(i);
            if (i % 2 == 0) {
                A[i] = mh;
            } else {
                if (mh == 0) A[i] = 0;
                else {
                    int upTo = max(0, mh - 1);
                    A[i] = rnd.next(0, upTo);
                }
            }
        }
    }

    // Generate queries
    vector<int> xs(Q), ys(Q);
    int updKind = rnd.next(0, 4); // 0..4
    int commonX = rnd.next(0, N);
    int pos = 0;

    for (int qi = 0; qi < Q; qi++) {
        int x, y;
        if (updKind == 0) {
            // Fully random updates
            x = rnd.next(0, N);
            y = rnd.next(0, maxH(x));
        } else if (updKind == 1) {
            // Focus on a single index
            x = commonX;
            int mh = maxH(x);
            if (mh == 0) {
                y = 0;
            } else {
                if (qi % 2 == 0) y = 0;
                else {
                    int chooseMax = rnd.next(0, 1);
                    if (chooseMax) y = mh;
                    else y = rnd.next(0, mh);
                }
            }
        } else if (updKind == 2) {
            // Sweep through positions cyclically
            x = pos;
            pos++;
            if (pos > N) pos = 0;
            y = rnd.next(0, maxH(x));
        } else if (updKind == 3 && scen == 0) {
            // Maintain all zeros
            x = rnd.next(0, N);
            y = 0;
        } else if (updKind == 4 && scen == 1) {
            // Maintain positive internal heights
            x = rnd.next(0, N);
            if (x == 0 || x == N) {
                y = 0;
            } else {
                int mh = maxH(x);
                if (mh == 0) y = 0;
                else y = rnd.next(1, mh);
            }
        } else {
            // Fallback random
            x = rnd.next(0, N);
            y = rnd.next(0, maxH(x));
        }
        xs[qi] = x;
        ys[qi] = y;
    }

    // Output
    println(N, Q);
    println(A);
    for (int i = 0; i < Q; i++) {
        println(xs[i], ys[i]);
    }

    return 0;
}
