#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Weighted options for biasing towards extremes or center
    vector<int> w_opts = {-1, 0, 1};
    int t1 = rnd.any(w_opts);
    int t2 = rnd.any(w_opts);
    // Generate R1 and S in [-1000,1000] with weighted randomness
    int R1 = rnd.wnext(2001, t1) - 1000;
    int S  = rnd.wnext(2001, t2) - 1000;
    // Occasionally pick corner values for extra edge coverage
    vector<int> corners = {-1000, -1, 0, 1, 1000};
    if (rnd.next(0, 9) == 0) R1 = rnd.any(corners);
    if (rnd.next(0, 9) == 0) S  = rnd.any(corners);
    // Output the test case
    println(R1, S);
    return 0;
}
