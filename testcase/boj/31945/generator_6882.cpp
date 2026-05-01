#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Predefined faces of the cube (sorted)
    vector<vector<int>> faces = {
        {0,1,2,3}, // z=0 face
        {4,5,6,7}, // z=1 face
        {0,1,4,5}, // y=0 face
        {2,3,6,7}, // y=1 face
        {0,2,4,6}, // x=0 face
        {1,3,5,7}  // x=1 face
    };
    // Hyperparameter for number of test cases
    int mode = rnd.next(0, 2);
    int T;
    if (mode == 0) {
        T = 1;
    } else if (mode == 1) {
        T = rnd.next(2, 6);
    } else {
        T = rnd.next(7, 15);
    }
    println(T);
    // Probability of generating a face-case
    double p_face = rnd.next();
    for (int tc = 0; tc < T; ++tc) {
        vector<int> quad;
        if (rnd.next() < p_face) {
            // Generate a face-case
            int f = rnd.next(0, (int)faces.size() - 1);
            quad = faces[f];
        } else {
            // Generate a non-face-case
            vector<int> cand(8);
            iota(cand.begin(), cand.end(), 0);
            while (true) {
                shuffle(cand.begin(), cand.end());
                quad.assign(cand.begin(), cand.begin() + 4);
                vector<int> s = quad;
                sort(s.begin(), s.end());
                bool isFace = false;
                for (auto &fset : faces) {
                    if (s == fset) {
                        isFace = true;
                        break;
                    }
                }
                if (!isFace) break;
            }
        }
        // Permute order for variability
        shuffle(quad.begin(), quad.end());
        println(quad);
    }
    return 0;
}
