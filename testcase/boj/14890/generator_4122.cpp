#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size and slope length
    int N = rnd.next(2, 10);
    int L = rnd.next(1, N);

    // Hyper-parameters for diversity
    double p_flat = rnd.next();   // probability a row is perfectly flat
    double p_step = rnd.next();   // probability to step +/-1 from previous height
    double p_reset = rnd.next();  // probability to reset to a random height

    vector<vector<int>> a(N, vector<int>(N));
    vector<int> dirs = {-1, 1};

    // Generate each row
    for (int i = 0; i < N; i++) {
        if (rnd.next() < p_flat) {
            // Entire row has the same height
            int h = rnd.next(1, 10);
            for (int j = 0; j < N; j++)
                a[i][j] = h;
        } else {
            // Random-walk style row
            a[i][0] = rnd.next(1, 10);
            for (int j = 1; j < N; j++) {
                double r = rnd.next();
                if (r < p_step) {
                    // Try to step up or down by 1
                    int d = rnd.any(dirs);
                    int prev = a[i][j-1];
                    int cand = prev + d;
                    if (cand >= 1 && cand <= 10)
                        a[i][j] = cand;
                    else
                        a[i][j] = rnd.next(1, 10);
                } else if (r < p_step + p_reset) {
                    // Reset to a random height
                    a[i][j] = rnd.next(1, 10);
                } else {
                    // Stay at the same height
                    a[i][j] = a[i][j-1];
                }
            }
        }
    }

    // Output in the required format
    println(N, L);
    for (int i = 0; i < N; i++)
        println(a[i]);

    return 0;
}
