#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of melons per 1m^2
    int K = rnd.next(1, 20);

    // Four rotations of the concave hexagon pattern
    vector<vector<int>> patterns = {
        {4, 2, 3, 1, 3, 1},
        {2, 3, 1, 4, 1, 4},
        {3, 1, 4, 2, 4, 2},
        {1, 4, 2, 3, 2, 3}
    };

    // Pick a random orientation
    auto pat = patterns[rnd.next(0, (int)patterns.size() - 1)];

    // Find indices of horizontal and vertical edges
    vector<int> Hplus, Hminus, Vplus, Vminus;
    for (int i = 0; i < 6; i++) {
        if (pat[i] == 1) Hplus.push_back(i);   // East
        else if (pat[i] == 2) Hminus.push_back(i); // West
        else if (pat[i] == 4) Vplus.push_back(i);  // North
        else if (pat[i] == 3) Vminus.push_back(i); // South
    }

    // Identify the "big" edge index and two "small" edges for each axis
    int bigH, bigV;
    vector<int> smallH(2), smallV(2);

    if ((int)Hplus.size() == 1) {
        bigH = Hplus[0];
        smallH[0] = Hminus[0];
        smallH[1] = Hminus[1];
    } else {
        bigH = Hminus[0];
        smallH[0] = Hplus[0];
        smallH[1] = Hplus[1];
    }
    if ((int)Vplus.size() == 1) {
        bigV = Vplus[0];
        smallV[0] = Vminus[0];
        smallV[1] = Vminus[1];
    } else {
        bigV = Vminus[0];
        smallV[0] = Vplus[0];
        smallV[1] = Vplus[1];
    }

    // Generate two random small segments for each axis so sums fit within [1,500]
    int sh1 = rnd.next(1, 499);
    int sh2 = rnd.next(1, 500 - sh1);
    int sv1 = rnd.next(1, 499);
    int sv2 = rnd.next(1, 500 - sv1);

    // Randomize assignment of which minor edge gets which length
    if (rnd.next(0, 1)) swap(smallH[0], smallH[1]);
    if (rnd.next(0, 1)) swap(smallV[0], smallV[1]);

    // Build lengths array
    vector<int> L(6);
    L[smallH[0]] = sh1;
    L[smallH[1]] = sh2;
    L[bigH]       = sh1 + sh2;
    L[smallV[0]] = sv1;
    L[smallV[1]] = sv2;
    L[bigV]       = sv1 + sv2;

    // Output the test case
    println(K);
    for (int i = 0; i < 6; i++) {
        println(pat[i], L[i]);
    }

    return 0;
}
