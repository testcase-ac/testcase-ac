#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test expressions before termination
    int L = rnd.next(1, 10);
    vector<string> ops = {"<", "<=", ">", ">=", "==", "!="};
    // Hyper-parameter function for diverse integers
    auto getNum = [&]() {
        double p = rnd.next();
        if (p < 0.1) {
            // extreme values
            return rnd.any(vector<int>{-10000, 10000});
        } else if (p < 0.3) {
            // small values
            return rnd.next(-10, 10);
        } else {
            // moderately random, biased toward smaller by wnext
            return rnd.wnext(20001, -1) - 10000;
        }
    };
    // Generate L lines of comparisons
    for (int i = 0; i < L; i++) {
        int a = getNum();
        int b = getNum();
        string op = rnd.any(ops);
        println(a, op, b);
    }
    // Termination line with operator E
    int a_end = rnd.next(-5, 5);
    int b_end = rnd.next(-5, 5);
    println(a_end, "E", b_end);
    return 0;
}
