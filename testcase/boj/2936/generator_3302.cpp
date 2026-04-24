#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const int L = 250;
    // Choose an edge: 0 = bottom (y=0), 1 = left (x=0), 2 = hypotenuse (x+y=L)
    vector<int> edges = {0, 1, 2};
    int edge = rnd.any(edges);
    // Hyper-parameter: occasionally pick an extreme endpoint (corners)
    bool extreme = rnd.next() < 0.3;
    int x, y;
    vector<int> ends = {0, L};
    vector<pair<int,int>> hyp_ends = {{0, L}, {L, 0}};
    
    if (extreme) {
        if (edge == 0) {
            x = rnd.any(ends);
            y = 0;
        } else if (edge == 1) {
            x = 0;
            y = rnd.any(ends);
        } else {
            auto p = rnd.any(hyp_ends);
            x = p.first;
            y = p.second;
        }
    } else {
        if (edge == 0) {
            x = rnd.next(0, L);
            y = 0;
        } else if (edge == 1) {
            x = 0;
            y = rnd.next(0, L);
        } else {
            x = rnd.next(0, L);
            y = L - x;
        }
    }

    // Output one endpoint (integers)
    println(x, y);
    return 0;
}
