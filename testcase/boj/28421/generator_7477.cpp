#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(2, 12);
    int Q = rnd.next(1, 12);
    vector<int> options = {10, 50, 100, 1000};
    int maxVal = rnd.any(options);
    vector<int> A(N), curA;
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(1, maxVal);
    }
    curA = A;
    int maxProd = maxVal * maxVal;
    double pType1 = rnd.next() * 0.5 + 0.3;
    int countType1 = 0;
    vector<pair<int,int>> queries;
    for (int qi = 0; qi < Q; qi++) {
        if (rnd.next() < pType1) {
            int x;
            if (rnd.next() < 0.1) {
                x = 0;
            } else if (rnd.next() < 0.5 && N >= 2) {
                int i = rnd.next(0, N-1);
                int j = rnd.next(0, N-2);
                if (j >= i) j++;
                x = curA[i] * curA[j];
            } else {
                x = rnd.next(0, maxProd);
            }
            queries.emplace_back(1, x);
            countType1++;
        } else {
            int idx = rnd.next(1, N);
            queries.emplace_back(2, idx);
            curA[idx-1] = 0;
        }
    }
    if (countType1 == 0) {
        int x = rnd.next(0, maxProd);
        queries.back() = make_pair(1, x);
    }
    println(N, Q);
    println(A);
    for (auto &q : queries) {
        println(q.first, q.second);
    }
    return 0;
}
