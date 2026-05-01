#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N in [1,30], biased towards smaller for readability
    int N = rnd.wnext(30, -2) + 1;

    // Decide alphabet type for variability
    bool onlySH = rnd.next(0, 9) == 0;    // ~10% chance: only S and H
    bool onlyG = !onlySH && (rnd.next(0, 19) == 0); // ~5% chance: only G
    string alph = onlySH ? "SH" : (onlyG ? "G" : "GSH");

    // Build initial random string
    vector<char> s(N);
    for (int i = 0; i < N; i++) {
        s[i] = rnd.any(alph);
    }

    // Prepare patterns for possible injection
    const char* patterns[2] = { "SSHS", "GSHS" };

    // Decide injections of patterns to create edge cases
    if (N >= 4) {
        bool forceInject = rnd.next(0, 4) == 0;  // ~20% force at least one
        int minInject = forceInject ? 1 : 0;
        int maxInject = 2;  // up to 2 injections
        int k = rnd.next(minInject, maxInject);
        for (int it = 0; it < k; it++) {
            int pos = rnd.next(0, N - 4);
            const char* pat = patterns[rnd.next(0, 1)];
            for (int j = 0; j < 4; j++) {
                s[pos + j] = pat[j];
            }
        }
    }

    // Output
    println(N);
    // Print string
    string out;
    out.reserve(N);
    for (char c : s) out.push_back(c);
    println(out);

    return 0;
}
