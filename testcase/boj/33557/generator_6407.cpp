#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

bool has_zero(int x) {
    string s = to_string(x);
    return s.find('0') != string::npos;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 20);
    vector<pair<int,int>> tests;
    // Hyper-parameter types
    vector<string> types = {"ONE", "MIX", "ZERO", "MAX", "POW10"};
    for (auto &tp : types) {
        if ((int)tests.size() >= T) break;
        int A, B;
        if (tp == "ONE") {
            // both one-digit
            A = rnd.next(1, 9);
            B = rnd.next(1, 9);
        } else if (tp == "MIX") {
            // mixed small/medium
            A = rnd.next(10, 999);
            B = rnd.next(1, 9999);
        } else if (tp == "ZERO") {
            // numbers containing at least one zero
            do { A = rnd.next(10, 1000000); } while (!has_zero(A));
            do { B = rnd.next(10, 1000000); } while (!has_zero(B));
        } else if (tp == "MAX") {
            // near maximum values
            A = rnd.next(1000000-10, 1000000);
            B = rnd.next(1000000-10, 1000000);
        } else { // POW10
            // powers of ten
            vector<int> pows = {1,10,100,1000,10000,100000,1000000};
            A = rnd.any(pows);
            B = rnd.any(pows);
        }
        tests.emplace_back(A, B);
    }
    // fill rest with random pairs
    while ((int)tests.size() < T) {
        int A = rnd.next(1, 1000000);
        int B = rnd.next(1, 1000000);
        tests.emplace_back(A, B);
    }
    // shuffle order
    shuffle(tests.begin(), tests.end());
    // output
    println(T);
    for (auto &pr : tests) {
        println(pr.first, pr.second);
    }
    return 0;
}
