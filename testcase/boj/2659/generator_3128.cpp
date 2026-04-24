#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Pattern type: 0=uniform, 1=two-pairs, 2=palindrome, 3=distinct-incr, 4=random
    int pat = rnd.next(0, 4);
    vector<int> v(4);

    if (pat == 0) {
        int x = rnd.next(1, 9);
        fill(v.begin(), v.end(), x);
    } else if (pat == 1) {
        int x = rnd.next(1, 9), y;
        do { y = rnd.next(1, 9); } while (y == x);
        v = {x, x, y, y};
    } else if (pat == 2) {
        int x = rnd.next(1, 9), y = rnd.next(1, 9);
        v = {x, y, y, x};
    } else if (pat == 3) {
        vector<int> nums;
        while ((int)nums.size() < 4) {
            int t = rnd.next(1, 9);
            if (!binary_search(nums.begin(), nums.end(), t))
                nums.push_back(t);
        }
        sort(nums.begin(), nums.end());
        v = nums;
    } else {
        for (int i = 0; i < 4; i++)
            v[i] = rnd.next(1, 9);
    }

    // Sometimes shuffle patterned vectors for more diversity
    if (pat != 4 && rnd.next() < 0.5) {
        shuffle(v.begin(), v.end());
    }

    // Output the four corners in clockwise order
    println(v);

    return 0;
}
