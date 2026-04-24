#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters
    int N = rnd.next(1, 10);
    int D = rnd.next(1, min(5, N));
    double intProb = rnd.next(); // probability to place an integer

    // Generate a pool of distinct variable names
    vector<string> vars;
    while ((int)vars.size() < D) {
        int L = rnd.next(1, 3);
        string s;
        for (int i = 0; i < L; i++) {
            s += char('a' + rnd.next(0, 25));
        }
        bool unique = true;
        for (auto &t : vars) if (t == s) { unique = false; break; }
        if (unique) vars.push_back(s);
    }

    // Build the two arrays
    vector<string> A(N), B(N);
    for (int i = 0; i < N; i++) {
        if (rnd.next() < intProb)
            A[i] = to_string(rnd.next(1, 999));
        else
            A[i] = rnd.any(vars);
        if (rnd.next() < intProb)
            B[i] = to_string(rnd.next(1, 999));
        else
            B[i] = rnd.any(vars);
    }

    // Output
    println(N);
    println(A);
    println(B);

    return 0;
}
