#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N between 3 and 15
    int N = rnd.next(3, 15);

    // Hyper-parameter for card value range
    int mode = rnd.next(0, 2);
    int maxCard;
    if (mode == 0) {
        // small values
        maxCard = rnd.next(10, 50);
    } else if (mode == 1) {
        // medium values
        maxCard = rnd.next(50, 2000);
    } else {
        // large values
        maxCard = rnd.next(1000, 100000);
    }

    // Generate card values
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        a[i] = rnd.next(1, maxCard);
    }

    // Compute minimal and maximal possible triple sums
    sort(a.begin(), a.end());
    int Smin = a[0] + a[1] + a[2];
    int Smax = a[N-1] + a[N-2] + a[N-3];
    int minM = max(Smin, 10);
    int maxM = 300000;

    // Choose M to hit various edge/mid cases
    int M;
    if (Smin == Smax) {
        // all triples equal
        M = minM;
    } else {
        int kind = rnd.next(0, 4);
        if (kind == 0) {
            // minimal possible
            M = minM;
        } else if (kind == 1) {
            // just above minimal
            int up = min(minM + 5, maxM);
            M = rnd.next(minM, up);
        } else if (kind == 2) {
            // maximal possible (best sum)
            M = Smax;
        } else if (kind == 3) {
            // just below maximal
            int low = max(minM, Smax - 5);
            M = rnd.next(low, Smax);
        } else {
            // random in full range
            M = rnd.next(minM, maxM);
        }
    }

    // Shuffle cards for unpredictability
    shuffle(a.begin(), a.end());

    // Output
    println(N, M);
    println(a);

    return 0;
}
