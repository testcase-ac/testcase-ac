#include "testlib.h"
#include <bitset>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    // Read N
    int N = inf.readInt(1, 500, "N");
    inf.readEoln();
    
    // Read the reachability matrix
    vector< bitset<500> > mat(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Name entries as a_i_j for clearer error messages
            string name = "a_" + to_string(i+1) + "_" + to_string(j+1);
            int x = inf.readInt(0, 1, name.c_str());
            if (x) mat[i].set(j);
            if (j + 1 < N)
                inf.readSpace();
        }
        inf.readEoln();
    }
    
    // Check reflexivity: diagonal must be 1
    for (int i = 0; i < N; i++) {
        ensuref(mat[i].test(i),
                "Diagonal element a_%d_%d must be 1, but found 0", i+1, i+1);
    }
    
    // Check transitivity:
    // For all i,j: if a[i][j] == 1 then mat[j] must be subset of mat[i].
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!mat[i].test(j)) continue;
            // compute those k where mat[j][k]=1 but mat[i][k]=0
            bitset<500> diff = mat[j] & (~mat[i]);
            if (diff.none()) continue;
            // find a witness k
            int k = -1;
            for (int t = 0; t < N; t++) {
                if (diff.test(t)) { k = t; break; }
            }
            // report violation
            ensuref(false,
                    "Transitivity violated: a_%d_%d = 1 and a_%d_%d = 1 but a_%d_%d = 0",
                    i+1, j+1, j+1, k+1, i+1, k+1);
        }
    }
    
    inf.readEof();
    return 0;
}
