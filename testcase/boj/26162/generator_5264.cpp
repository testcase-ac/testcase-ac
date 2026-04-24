#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of queries
    int N = rnd.next(1, 10);

    // Define two cut points for splitting the domain [1..118]
    int c1 = rnd.next(1, 50);
    int c2 = rnd.next(c1 + 1, 117);  // ensure c2 < 118 so region3 is non-empty

    // Collect N distinct atom numbers from three regions for diversity
    set<int> S;
    while ((int)S.size() < N) {
        int region = rnd.next(0, 2);
        int val;
        if (region == 0) {
            val = rnd.next(1, c1);
        } else if (region == 1) {
            val = rnd.next(c1 + 1, c2);
        } else {
            val = rnd.next(c2 + 1, 118);
        }
        S.insert(val);
    }

    // Randomize order
    vector<int> a(S.begin(), S.end());
    shuffle(a.begin(), a.end());

    // Output
    println(N);
    for (int x : a) {
        println(x);
    }

    return 0;
}
