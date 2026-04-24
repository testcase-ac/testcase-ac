#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of people
    int N = rnd.next(1, 10);

    // Hyper-parameter for max books per person
    vector<int> aChoices = {1, 2, 3, 5};
    int maxA = rnd.any(aChoices);

    // Books wanted by each person
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(1, maxA);
    }
    int sumA = accumulate(A.begin(), A.end(), 0);

    // Number of stores
    int maxStores = min(sumA, 10);
    int M = rnd.next(1, maxStores);

    // Books available at each store, sum = sumA, all >= 1
    vector<int> B;
    if (M == 1) {
        B = {sumA};
    } else {
        B.assign(M, 1);
        int rem = sumA - M;
        if (rem > 0) {
            // distribute rem into M parts (possibly zero) via random cuts
            vector<int> cuts;
            for (int i = 0; i < M - 1; i++) {
                cuts.push_back(rnd.next(0, rem));
            }
            sort(cuts.begin(), cuts.end());
            B[0] += cuts[0];
            for (int i = 1; i < M - 1; i++) {
                B[i] += cuts[i] - cuts[i - 1];
            }
            B[M - 1] += rem - cuts[M - 2];
        }
    }

    // Hyper-parameter for cost distribution
    vector<int> tChoices = {-2, -1, 0, 1, 2};
    int t = rnd.any(tChoices);
    vector<double> pChoices = {0.2, 0.3, 0.5, 0.7};
    double unifProb = rnd.any(pChoices);
    bool useUniformCost = rnd.next() < unifProb;

    // Base bias per store for weighted costs
    vector<int> baseBias(M);
    for (int j = 0; j < M; j++) {
        baseBias[j] = rnd.next(0, 500);
    }

    // Output input
    println(N, M);
    println(A);
    println(B);
    for (int j = 0; j < M; j++) {
        vector<int> row(N);
        for (int i = 0; i < N; i++) {
            int c;
            if (useUniformCost) {
                c = rnd.next(1, 1000);
            } else {
                c = baseBias[j] + rnd.wnext(500, t) + 1;
                if (c < 1) c = 1;
                if (c > 1000) c = 1000;
            }
            row[i] = c;
        }
        println(row);
    }

    return 0;
}
