#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Array size between 3 and 12 for hand-verifiable testing
    int n = rnd.next(3, 12);
    // Total operations between 1 and 5*n
    int q = rnd.next(1, n * 5);
    // Ensure at least one query
    int upds = rnd.next(0, min(q - 1, n));

    // Generate initial array with bias towards small values
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = rnd.wnext(n + 1, -1);  // biased towards smaller numbers
    }

    // Prepare operations
    vector<string> ops;
    // Add updates
    for (int i = 0; i < upds; i++) {
        int pos = rnd.next(1, n);
        int x = rnd.wnext(n + 1, -1);  // biased towards smaller values
        ops.push_back("! " + to_string(pos) + " " + to_string(x));
    }
    // Add queries
    for (int i = 0; i < q - upds; i++) {
        int type = rnd.next(0, 2);
        int l, r;
        if (type == 0) {
            // full range query
            l = 1; r = n;
        } else if (type == 1) {
            // random small subrange
            int len = rnd.next(1, n);
            l = rnd.next(1, n - len + 1);
            r = l + len - 1;
        } else {
            // single element query
            l = r = rnd.next(1, n);
        }
        ops.push_back("? " + to_string(l) + " " + to_string(r));
    }

    // Shuffle operations to interleave updates and queries
    shuffle(ops.begin(), ops.end());

    // Output
    println(n, q);
    println(a);
    for (auto &s : ops) {
        printf("%s\n", s.c_str());
    }
    return 0;
}
