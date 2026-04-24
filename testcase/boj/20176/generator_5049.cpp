#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sizes of each barrier's holes
    int nu = rnd.next(1, 7);
    int nm = rnd.next(1, 7);
    int nl = rnd.next(1, 7);

    // Coordinate range hyper-parameter
    int maxRange = rnd.next(5, 20);
    int L = -maxRange;
    int R =  maxRange;

    // Generate distinct x-coordinates for the upper barrier
    set<int> upSet;
    while ((int)upSet.size() < nu) {
        upSet.insert(rnd.next(L, R));
    }
    vector<int> up(upSet.begin(), upSet.end());

    // Generate distinct x-coordinates for the lower barrier
    set<int> lowSet;
    while ((int)lowSet.size() < nl) {
        lowSet.insert(rnd.next(L, R));
    }
    vector<int> low(lowSet.begin(), lowSet.end());

    // Generate the middle barrier's holes, possibly including some exact midpoints
    vector<int> mid;
    bool alignCase = rnd.next(0, 1) == 1;
    if (alignCase) {
        // Try to force some alignments: pick k pairs and include their integer midpoints
        int k = rnd.next(0, min({nu, nl, nm}));
        set<int> midSet;
        int attempts = 0;
        while ((int)midSet.size() < k && attempts < k * 10) {
            int xu = up[rnd.next(0, nu - 1)];
            int xl = low[rnd.next(0, nl - 1)];
            // only integer midpoint
            if (((xu + xl) & 1) == 0) {
                midSet.insert((xu + xl) / 2);
            }
            attempts++;
        }
        // Fill the rest randomly
        while ((int)midSet.size() < nm) {
            midSet.insert(rnd.next(L, R));
        }
        mid.assign(midSet.begin(), midSet.end());
    } else {
        // Purely random distinct distribution
        set<int> midSet;
        while ((int)midSet.size() < nm) {
            midSet.insert(rnd.next(L, R));
        }
        mid.assign(midSet.begin(), midSet.end());
    }

    // Shuffle each list to avoid sorted order
    shuffle(up.begin(), up.end());
    shuffle(mid.begin(), mid.end());
    shuffle(low.begin(), low.end());

    // Output in the required format
    println(nu);
    println(up);
    println(nm);
    println(mid);
    println(nl);
    println(low);

    return 0;
}
