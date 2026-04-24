#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // DNA length
        int n = rnd.next(1, 20);
        // decide marker length, sometimes longer than DNA
        bool longMarker = rnd.next() < 0.2;
        int m;
        if (longMarker) {
            // marker longer than DNA to force zero occurrences
            m = rnd.next(n + 1, min(n + 3, 100));
        } else {
            // normal marker length up to n or small cap
            if (n >= 1)
                m = rnd.next(1, max(1, min(n, 8)));
            else
                m = 1;
        }

        // generate random DNA
        string dna(n, 'A');
        for (int i = 0; i < n; i++) {
            dna[i] = rnd.any(string("ACGT"));
        }
        // generate random marker
        string marker(m, 'A');
        for (int i = 0; i < m; i++) {
            marker[i] = rnd.any(string("ACGT"));
        }

        // embed some mutated markers to ensure non-zero cases
        bool doEmbed = (m <= n) && (rnd.next() < 0.5);
        if (doEmbed) {
            int maxPos = n - m + 1;
            int K = rnd.next(1, min(maxPos, 3));
            for (int k = 0; k < K; k++) {
                // create a mutated version of marker
                int i = rnd.next(0, m);
                int j = rnd.next(i, m);
                string pre = marker.substr(0, i);
                string mid = marker.substr(i, j - i);
                string suf = marker.substr(j);
                reverse(mid.begin(), mid.end());
                string mutated = pre + mid + suf;
                // pick position
                int pos = rnd.next(0, n - m);
                for (int t = 0; t < m; t++) {
                    dna[pos + t] = mutated[t];
                }
            }
        }

        // output this test case
        println(n, m);
        println(dna);
        println(marker);
    }
    return 0;
}
