#include "testlib.h"
#include <vector>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of queries
    int N = rnd.next(2, 30);
    // Probability of magic query
    double magicDensity = rnd.next(0.1, 0.6);
    // Maximum increment for new log lengths
    int deltaMax = rnd.next(1, 50);

    // Decide types: 1 = add log, 2 = magic
    vector<int> type(N);
    int cnt1 = 0;
    for (int i = 0; i < N; i++) {
        if (rnd.next() < magicDensity) {
            type[i] = 2;
        } else {
            type[i] = 1;
            cnt1++;
        }
    }
    // Ensure at least one add-log query
    if (cnt1 == 0) {
        int idx = rnd.next(0, N - 1);
        type[idx] = 1;
    }

    vector<pair<int,long long>> qs;
    long long lastLog = 0;
    for (int i = 0; i < N; i++) {
        if (type[i] == 1) {
            // Add a new log longer than any before
            long long x;
            if (lastLog == 0) {
                x = rnd.next(1, 100);
            } else {
                x = lastLog + rnd.next(1, deltaMax);
            }
            lastLog = x;
            qs.emplace_back(1, x);
        } else {
            // Magic with power m
            int hi = (lastLog > 0 ? lastLog + rnd.next(1, 50) : rnd.next(1, 50));
            long long m = rnd.next(1, hi);
            qs.emplace_back(2, m);
        }
    }

    // Output
    println(N);
    for (auto &q : qs) {
        println(q.first, q.second);
    }
    return 0;
}
