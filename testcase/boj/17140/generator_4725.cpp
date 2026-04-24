#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int valMax = rnd.next(1, 5);      // max initial value
    int r = rnd.next(1, 3);           // target row
    int c = rnd.next(1, 3);           // target column

    // Generate 3x3 initial array with values in [1, valMax]
    vector<vector<int>> A(4, vector<int>(4));
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            A[i][j] = rnd.next(1, valMax);
        }
    }

    // Decide if trivial case (A[r][c] == k immediately)
    bool trivial = rnd.next(0, 1);
    int k;
    if (trivial) {
        k = A[r][c];
    } else {
        // Choose k != A[r][c], allow some new values up to valMax+3
        vector<int> cand;
        for (int x = 1; x <= valMax + 3; x++) {
            if (x != A[r][c] && x <= 100)
                cand.push_back(x);
        }
        k = rnd.any(cand);
    }

    // Output in required format
    println(r, c, k);
    for (int i = 1; i <= 3; i++) {
        println(A[i][1], A[i][2], A[i][3]);
    }
    return 0;
}
