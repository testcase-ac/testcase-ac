#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Upper barrier
    int n_u = inf.readInt(1, 50000, "n_u");
    inf.readEoln();
    vector<int> x_u = inf.readInts(n_u, -30000, 30000, "x_u_i");
    inf.readEoln();
    {
        vector<int> tmp = x_u;
        sort(tmp.begin(), tmp.end());
        for (int i = 1; i < (int)tmp.size(); i++) {
            ensuref(tmp[i] != tmp[i-1],
                    "Duplicate x-coordinate in upper barrier at indices %d and %d: %d",
                    i-1, i, tmp[i]);
        }
    }

    // Middle barrier
    int n_m = inf.readInt(1, 50000, "n_m");
    inf.readEoln();
    vector<int> x_m = inf.readInts(n_m, -30000, 30000, "x_m_i");
    inf.readEoln();
    {
        vector<int> tmp = x_m;
        sort(tmp.begin(), tmp.end());
        for (int i = 1; i < (int)tmp.size(); i++) {
            ensuref(tmp[i] != tmp[i-1],
                    "Duplicate x-coordinate in middle barrier at indices %d and %d: %d",
                    i-1, i, tmp[i]);
        }
    }

    // Lower barrier
    int n_l = inf.readInt(1, 50000, "n_l");
    inf.readEoln();
    vector<int> x_l = inf.readInts(n_l, -30000, 30000, "x_l_i");
    inf.readEoln();
    {
        vector<int> tmp = x_l;
        sort(tmp.begin(), tmp.end());
        for (int i = 1; i < (int)tmp.size(); i++) {
            ensuref(tmp[i] != tmp[i-1],
                    "Duplicate x-coordinate in lower barrier at indices %d and %d: %d",
                    i-1, i, tmp[i]);
        }
    }

    // No extra input
    inf.readEof();
    return 0;
}
