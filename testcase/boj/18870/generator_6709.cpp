#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Size of the array
    int N = rnd.next(1, 15);
    vector<long long> X(N);

    // Choose a scenario to diversify test cases
    int scenario = rnd.next(0, 4);
    if (scenario == 0) {
        // All equal
        int v = rnd.next(-5, 5);
        for (int i = 0; i < N; i++) X[i] = v;
    } else if (scenario == 1) {
        // Strictly increasing
        long long cur = rnd.next(-5, 5);
        X[0] = cur;
        for (int i = 1; i < N; i++) {
            cur += rnd.next(1, 3);
            X[i] = cur;
        }
    } else if (scenario == 2) {
        // Strictly decreasing
        long long cur = rnd.next(-5, 5);
        X[0] = cur;
        for (int i = 1; i < N; i++) {
            cur -= rnd.next(1, 3);
            X[i] = cur;
        }
    } else if (scenario == 3) {
        // Few distinct values
        int D = rnd.next(1, min(N, 5));
        set<long long> s;
        while ((int)s.size() < D) {
            s.insert(rnd.next(-10, 10));
        }
        vector<long long> vals(s.begin(), s.end());
        for (int i = 0; i < N; i++) {
            X[i] = rnd.any(vals);
        }
    } else {
        // Fully random in a moderate range
        for (int i = 0; i < N; i++) {
            X[i] = rnd.next(-10, 10);
        }
    }

    // Output
    println(N);
    println(X);
    return 0;
}
