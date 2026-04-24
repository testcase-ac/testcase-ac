#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small array size
    int N = rnd.next(1, 10);

    // Choose number of distinct values
    int dcount = rnd.next(1, N);
    double bigRatio = rnd.next(); // chance to pick large values

    // Generate distinct values, some are large to test variety
    set<int> s;
    while ((int)s.size() < dcount) {
        if (rnd.next() < bigRatio)
            s.insert(rnd.next(100000000, 1000000000));
        else
            s.insert(rnd.next(1, 100));
    }
    vector<int> distinct(s.begin(), s.end());
    shuffle(distinct.begin(), distinct.end());

    // Build the array
    vector<int> A(N);
    for (int i = 0; i < N; ++i)
        A[i] = rnd.any(distinct);

    // Number of queries
    int Q = rnd.next(1, 20);

    // Hyper-parameters for query types
    int fewSingle = rnd.next(0, Q);
    int fewWhole = rnd.next(0, Q - fewSingle);
    int rest = Q - fewSingle - fewWhole;

    vector<pair<int,int>> queries;
    // Single-element queries
    for (int i = 0; i < fewSingle; ++i) {
        int x = rnd.next(1, N);
        queries.emplace_back(x, x);
    }
    // Full-range queries
    for (int i = 0; i < fewWhole; ++i) {
        queries.emplace_back(1, N);
    }
    // Random-range queries
    for (int i = 0; i < rest; ++i) {
        int l = rnd.next(1, N);
        int r = rnd.next(l, N);
        queries.emplace_back(l, r);
    }
    shuffle(queries.begin(), queries.end());

    // Output
    println(N);
    println(A);
    println(Q);
    for (auto &qr : queries)
        println(qr.first, qr.second);

    return 0;
}
