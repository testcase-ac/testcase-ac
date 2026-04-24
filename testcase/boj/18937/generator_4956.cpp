#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of bridges
    int N = rnd.next(1, 10);
    vector<long long> A(N);
    // Hyper-parameter for small vs large values
    double smallProb = rnd.next();
    const int MAX_A = 1000000000;
    int hiParam = MAX_A - 1; // for wnext range [0..hiParam-1]
    for (int i = 0; i < N; i++) {
        if (rnd.next() < smallProb) {
            // small Ai for hand-checkable cases
            A[i] = rnd.next(2, 20);
        } else {
            // large Ai with weighted distribution
            int t = rnd.next(-3, 3);
            A[i] = 2 + rnd.wnext(hiParam, t);
        }
    }
    // Choose starting player
    vector<string> names = {"Whiteking", "Blackking"};
    string first = rnd.any(names);
    // Output
    println(N);
    println(A);
    println(first);
    return 0;
}
