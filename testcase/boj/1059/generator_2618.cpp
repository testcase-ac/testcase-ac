/* generator code */
#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // size of S
    int L = rnd.next(1, 10);
    // ensure at least one gap in [1, max(S)]
    int highVal = rnd.next(L + 2, 3 * L + 2);
    // build all candidates 1..highVal-1
    vector<int> all;
    for (int i = 1; i < highVal; ++i)
        all.push_back(i);
    // random order
    shuffle(all.begin(), all.end());
    // pick L-1 values for S, reserve one slot for highVal
    vector<int> S;
    for (int i = 0; i < L - 1; ++i)
        S.push_back(all[i]);
    S.push_back(highVal);
    // collect missing numbers (gaps)
    vector<int> missing;
    for (int i = L - 1; i < (int)all.size(); ++i)
        missing.push_back(all[i]);
    // choose n from missing so n ∉ S and n ≤ max(S)
    int n = rnd.any(missing);
    // shuffle S so it's not sorted in input
    shuffle(S.begin(), S.end());
    // output
    println(L);
    // print set S
    if (!S.empty()) {
        printf("%d", S[0]);
        for (int i = 1; i < L; ++i)
            printf(" %d", S[i]);
    }
    printf("\n");
    // print n
    println(n);
    return 0;
}
