#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Predefined pools of known YES and NO cases
    vector<vector<int>> yesPool = {
        {4,7,8,8}, // (7-8/8)*4 = 24
        {1,3,4,6}, // 6/(1-3/4) = 24
        {3,3,8,8}, // 8/(3-8/3) = 24
        {5,5,5,1}  // (5-1/5)*5 = 24
    };
    vector<vector<int>> noPool = {
        {1,1,1,1},
        {1,1,2,4},
        {2,2,2,2},
        {3,3,3,3},
        {4,4,4,4}
    };
    // Number of test cases
    int T = rnd.next(5, 12);
    println(T);
    for (int i = 0; i < T; i++) {
        double p = rnd.next();
        vector<int> v(4);
        if (p < 0.3) {
            // Known YES case
            v = rnd.any(yesPool);
        } else if (p < 0.6) {
            // Known NO case
            v = rnd.any(noPool);
        } else {
            // Random case
            for (int j = 0; j < 4; j++) v[j] = rnd.next(1, 9);
        }
        // Shuffle order to vary positions
        shuffle(v.begin(), v.end());
        println(v);
    }
    return 0;
}
