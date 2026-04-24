#include "testlib.h"
#include <vector>
#include <map>
#include <cstdint>
#include <climits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read exactly three integers in the range [-100, 100]
    vector<int> v = inf.readInts(3, -100, 100, "a_i");
    inf.readEoln();

    // Count occurrences of the input numbers
    map<int,int> cnt_in;
    for (int x : v) {
        ++cnt_in[x];
    }

    // Check that there exists an integer arithmetic progression
    // of length 4 (x, x+d, x+2d, x+3d) that contains all three input values.
    bool found = false;
    // Try all ways of mapping two distinct input values to two distinct positions
    // in the 4-term progression to determine x and d.
    for (int idx1 = 0; idx1 < 3 && !found; ++idx1) {
        for (int idx2 = 0; idx2 < 3 && !found; ++idx2) {
            if (idx1 == idx2) continue;
            long long a = v[idx1];
            long long b = v[idx2];
            for (int pos1 = 0; pos1 < 4 && !found; ++pos1) {
                for (int pos2 = pos1 + 1; pos2 < 4 && !found; ++pos2) {
                    int gap = pos2 - pos1;
                    long long diff = b - a;
                    // d must be integer
                    if (diff % gap != 0) continue;
                    long long d = diff / gap;
                    // Compute x = a - pos1 * d
                    __int128 tx = (__int128)a - (__int128)pos1 * d;
                    if (tx < LLONG_MIN || tx > LLONG_MAX) continue;
                    long long x0 = (long long)tx;
                    // Build the 4-term progression and count its elements
                    map<long long,int> cnt_prog;
                    for (int i = 0; i < 4; ++i) {
                        long long val = x0 + (long long)i * d;
                        ++cnt_prog[val];
                    }
                    // Check if all input counts are covered
                    bool ok = true;
                    for (auto &kv : cnt_in) {
                        long long val = kv.first;
                        int need = kv.second;
                        if (cnt_prog[val] < need) {
                            ok = false;
                            break;
                        }
                    }
                    if (ok) {
                        found = true;
                    }
                }
            }
        }
    }

    ensuref(found,
            "The three numbers %d, %d, %d cannot be part of any integer arithmetic progression of length 4",
            v[0], v[1], v[2]);

    inf.readEof();
    return 0;
}
