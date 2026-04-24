#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 3);
    for (int tc = 0; tc < T; ++tc) {
        // Grid size
        int N = rnd.next(2, 5);
        println(N);

        // Hyper-parameters for value distribution
        int maxSmall = rnd.next(0, 4);
        int minLarge = rnd.next(maxSmall + 1, 9);
        double pLarge = rnd.next(0.0, 1.0);

        // Generate grid
        for (int i = 0; i < N; ++i) {
            vector<int> row;
            for (int j = 0; j < N; ++j) {
                if (rnd.next() < pLarge) {
                    // large value
                    row.push_back(rnd.next(minLarge, 9));
                } else {
                    // small value
                    row.push_back(rnd.next(0, maxSmall));
                }
            }
            println(row);
        }
    }

    // Termination
    println(0);
    return 0;
}
