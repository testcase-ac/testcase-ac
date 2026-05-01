#include "testlib.h"
#include <vector>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(5, 15);
    println(T);
    for (int ti = 0; ti < T; ti++) {
        int X = rnd.next(1, 100);
        vector<int> avail(10, 0);
        int mode = rnd.next(0, 3);
        if (mode == 0) {
            // all digits available
            for (int d = 0; d <= 9; d++) avail[d] = 1;
        } else {
            int k;
            if (mode == 1) k = rnd.next(1, 3);
            else if (mode == 2) k = rnd.next(4, 7);
            else k = rnd.next(8, 9);
            int count = 0;
            bool usedDiv = (mode == 2 && rnd.next(0, 1) == 1);
            if (usedDiv) {
                vector<int> ds;
                for (int d = 1; d <= 9; d++) if (X % d == 0) ds.push_back(d);
                if (!ds.empty()) {
                    int d = rnd.any(ds);
                    avail[d] = 1;
                    count = 1;
                }
            }
            vector<int> digits(10);
            iota(digits.begin(), digits.end(), 0);
            shuffle(digits.begin(), digits.end());
            for (int i = 0; i < 10 && count < k; i++) {
                int d = digits[i];
                if (!avail[d]) {
                    avail[d] = 1;
                    count++;
                }
            }
            if (count == 0) {
                // ensure at least one digit
                int d = rnd.next(0, 9);
                avail[d] = 1;
            }
        }
        // output availability
        for (int d = 0; d <= 9; d++) {
            printf("%d", avail[d]);
            if (d < 9) printf(" ");
        }
        printf("\n");
        // output target
        println(X);
    }

    return 0;
}
