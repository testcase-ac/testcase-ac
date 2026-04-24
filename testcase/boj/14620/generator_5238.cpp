#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int N = rnd.next(6, 10);            // grid size
    int Gmax = rnd.next(10, 200);       // maximum possible cost
    int skew = rnd.next(-3, 3);         // skew for weighted sampling

    // Output N
    println(N);

    // Generate grid
    for (int i = 0; i < N; ++i) {
        vector<int> row(N);
        for (int j = 0; j < N; ++j) {
            // Generate cost in [0, Gmax], skewed by 'skew'
            row[j] = rnd.wnext(Gmax + 1, skew);
        }
        // Print one row
        println(row);
    }

    return 0;
}
