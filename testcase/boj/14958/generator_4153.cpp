#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small sizes
    int n = rnd.next(2, 12);
    int m = rnd.next(1, n - 1);
    // Occasionally force edge m=1 or m=n-1
    int rm = rnd.next(0, 9);
    if (rm == 0) m = 1;
    else if (rm == 1) m = n - 1;

    // Decide style for diversity
    int style = rnd.next(1, 5);

    string s1, s2;
    s1.reserve(n);
    s2.reserve(m);

    auto random_char = [&]() {
        return rnd.any(string("RPS"));
    };

    if (style == 1) {
        // uniform both
        for (int i = 0; i < n; i++) s1 += random_char();
        for (int i = 0; i < m; i++) s2 += random_char();
    } else if (style == 2) {
        // s1 biased, s2 uniform
        char major = random_char();
        for (int i = 0; i < n; i++) {
            if (rnd.next(0, 99) < 60) s1 += major;
            else s1 += random_char();
        }
        for (int i = 0; i < m; i++) s2 += random_char();
    } else if (style == 3) {
        // s2 biased, s1 uniform
        char major = random_char();
        for (int i = 0; i < n; i++) s1 += random_char();
        for (int i = 0; i < m; i++) {
            if (rnd.next(0, 99) < 60) s2 += major;
            else s2 += random_char();
        }
    } else if (style == 4) {
        // patterned both
        int k1 = rnd.next(1, min(3, n));
        string pat1;
        for (int i = 0; i < k1; i++) pat1 += random_char();
        for (int i = 0; i < n; i++) s1 += pat1[i % k1];

        int k2 = rnd.next(1, min(3, m));
        string pat2;
        for (int i = 0; i < k2; i++) pat2 += random_char();
        for (int i = 0; i < m; i++) s2 += pat2[i % k2];
    } else {
        // both same char
        char c = random_char();
        for (int i = 0; i < n; i++) s1 += c;
        for (int i = 0; i < m; i++) s2 += c;
    }

    // Output input
    println(n, m);
    println(s1);
    println(s2);

    return 0;
}
