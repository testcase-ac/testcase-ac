#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 3);
    println(T);

    // Possible faces and directions
    string faces = "UDFBLR";
    string dirs = "+-";
    vector<int> tpars = {-2, -1, 0, 1, 2};

    for (int tc = 0; tc < T; tc++) {
        // Hyper-parameter to bias move count distribution
        int tp = rnd.any(tpars);
        int n = max(1, rnd.wnext(20, tp));

        // Choose a pattern type for variability
        int pattern = rnd.next(0, 2);
        vector<string> moves;

        if (pattern == 0) {
            // Fully random moves
            for (int i = 0; i < n; i++) {
                char f = rnd.any(faces);
                char d = rnd.any(dirs);
                moves.push_back(string(1, f) + d);
            }
        } else if (pattern == 1) {
            // Many cancelling pairs: X+ X- ...
            int half = n / 2;
            for (int i = 0; i < half; i++) {
                char f = rnd.any(faces);
                char d = rnd.any(dirs);
                moves.push_back(string(1, f) + d);
                moves.push_back(string(1, f) + (d == '+' ? '-' : '+'));
            }
            if (n % 2 == 1) {
                char f = rnd.any(faces);
                char d = rnd.any(dirs);
                moves.push_back(string(1, f) + d);
            }
        } else {
            // Blocked segments: repeat same face+dir for small blocks
            int i = 0;
            int maxBlock = max(1, n / 5);
            while (i < n) {
                int blk = rnd.next(1, maxBlock);
                char f = rnd.any(faces);
                char d = rnd.any(dirs);
                for (int j = 0; j < blk && i < n; j++, i++) {
                    moves.push_back(string(1, f) + d);
                }
            }
        }

        // Output this test case
        println(n);
        println(moves);
    }
    return 0;
}
