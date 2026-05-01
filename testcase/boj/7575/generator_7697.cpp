#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of programs
    int N = rnd.next(2, 8);
    vector<int> M(N);
    for (int i = 0; i < N; i++) {
        M[i] = rnd.next(10, 30);
    }
    int minM = *min_element(M.begin(), M.end());
    int K = rnd.next(4, minM);

    // Decide if we embed a common segment (YES case) or not (NO case)
    bool hasCommon = rnd.next(0, 3) > 0; // ~75% YES, ~25% NO

    // Output N and K
    println(N, K);

    if (hasCommon) {
        // Generate the virus segment
        int L = rnd.next(K, minM);
        vector<int> virus(L);
        for (int i = 0; i < L; i++) {
            virus[i] = rnd.next(1, 10000);
        }
        // For each program, embed the segment (possibly reversed) with random padding
        for (int i = 0; i < N; i++) {
            int pre = rnd.next(0, M[i] - L);
            int suf = M[i] - L - pre;
            println(M[i]);
            vector<int> seq;
            // prefix padding
            for (int j = 0; j < pre; j++) {
                seq.push_back(rnd.next(1, 10000));
            }
            // embedded segment (forward or reversed)
            if (rnd.next(0,1) == 0) {
                seq.insert(seq.end(), virus.begin(), virus.end());
            } else {
                vector<int> rev = virus;
                reverse(rev.begin(), rev.end());
                seq.insert(seq.end(), rev.begin(), rev.end());
            }
            // suffix padding
            for (int j = 0; j < suf; j++) {
                seq.push_back(rnd.next(1, 10000));
            }
            // output sequence
            println(seq);
        }
    } else {
        // NO case: use disjoint code ranges to avoid any common subarray
        for (int i = 0; i < N; i++) {
            println(M[i]);
            vector<int> seq(M[i]);
            int base = i * 1000;
            for (int j = 0; j < M[i]; j++) {
                seq[j] = rnd.next(base + 1, base + 500);
            }
            println(seq);
        }
    }

    return 0;
}
