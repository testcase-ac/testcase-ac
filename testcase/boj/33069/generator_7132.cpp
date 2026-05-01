#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of appliances to choose
    int N = rnd.next(2, 10);
    // Total types in store
    int K = N + rnd.next(0, 5);
    // Minimum preferred by each
    int M = rnd.next(1, N);
    // Sizes of preference lists
    int A = rnd.next(M, N);
    int B = rnd.next(M, N);
    // Determine overlap bounds to ensure disjoint assignment pools
    int OLmin = max(0, A + B - K);
    int OLmax = min(A, B);
    int OL;
    if (OLmin == OLmax) {
        OL = OLmin;
    } else {
        int choice = rnd.next(0, 2);
        if (choice == 0) OL = OLmin;
        else if (choice == 1) OL = OLmax;
        else OL = rnd.next(OLmin, OLmax);
    }
    // Prepare shuffled type IDs
    vector<int> ids(K);
    for (int i = 0; i < K; ++i) ids[i] = i + 1;
    shuffle(ids.begin(), ids.end());
    // Build common, A-only, B-only sets
    vector<int> common(ids.begin(), ids.begin() + OL);
    vector<int> Aonly(ids.begin() + OL, ids.begin() + OL + (A - OL));
    vector<int> Bonly(ids.begin() + OL + (A - OL), ids.begin() + OL + (A - OL) + (B - OL));
    // Random costs
    vector<long long> costs(K);
    for (int i = 0; i < K; ++i) costs[i] = rnd.next(1, 100);
    // Final preference lists
    vector<int> Alist = common;
    Alist.insert(Alist.end(), Aonly.begin(), Aonly.end());
    vector<int> Blist = common;
    Blist.insert(Blist.end(), Bonly.begin(), Bonly.end());
    shuffle(Alist.begin(), Alist.end());
    shuffle(Blist.begin(), Blist.end());
    // Output
    println(N, K);
    println(M, A, B);
    println(costs);
    println(Alist);
    println(Blist);
    return 0;
}
