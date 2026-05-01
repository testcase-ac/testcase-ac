#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N between 3 and 20 for hand-verifiable size
    int N = rnd.next(3, 20);

    // Choose a pattern type for variability
    int pattern = rnd.next(0, 4);
    vector<int> a(N);

    if (pattern == 0) {
        // Pure random
        for (int i = 0; i < N; i++)
            a[i] = rnd.next(1, 20);
    }
    else if (pattern == 1) {
        // Mountain: increases then decreases
        int peak = rnd.next(1, N - 2);
        for (int i = 0; i <= peak; i++)
            a[i] = rnd.next(1, 5) + i * 2;
        for (int i = peak + 1; i < N; i++)
            a[i] = rnd.next(1, 5) + (N - i) * 2;
    }
    else if (pattern == 2) {
        // Valley: decreases then increases
        int mid = rnd.next(1, N - 2);
        for (int i = 0; i <= mid; i++)
            a[i] = rnd.next(1, 5) + (mid - i) * 2;
        for (int i = mid + 1; i < N; i++)
            a[i] = rnd.next(1, 5) + (i - mid) * 2;
    }
    else if (pattern == 3) {
        // Block-constant segments
        int i = 0;
        while (i < N) {
            int len = rnd.next(1, min(3, N - i));
            int val = rnd.next(1, 20);
            for (int j = 0; j < len; j++)
                a[i++] = val;
        }
    }
    else {
        // Periodic-like pattern
        int period = rnd.next(2, min(5, N - 1));
        vector<int> base(period);
        for (int i = 0; i < period; i++)
            base[i] = rnd.next(1, 20);
        for (int i = 0; i < N; i++)
            a[i] = base[i % period] + rnd.next(0, 5);
    }

    // Occasionally sprinkle a big spike or dip
    if (rnd.next(0, 1)) {
        int pos = rnd.next(0, N - 1);
        if (rnd.next(0, 1))
            a[pos] = rnd.next(50, 100); // spike
        else
            a[pos] = rnd.next(1, 3);    // dip
    }

    // Output
    println(N);
    println(a);
    return 0;
}
