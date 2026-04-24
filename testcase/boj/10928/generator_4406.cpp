#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for length bias: negative t for small, positive for large, zero for uniform
    vector<int> tvals = {-3, -1, 0, 1, 3};
    int t = rnd.any(tvals);
    // rnd.wnext(50, t) returns [0,49] biased; add 1 for [1,50]
    int L = rnd.wnext(50, t) + 1;

    // Hyper-parameter for character composition
    vector<string> modes = {"lower", "upper", "digit", "mix"};
    string mode = rnd.any(modes);

    string pool;
    if (mode == "lower") {
        pool = "abcdefghijklmnopqrstuvwxyz";
    } else if (mode == "upper") {
        pool = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    } else if (mode == "digit") {
        pool = "0123456789";
    } else {
        pool = "abcdefghijklmnopqrstuvwxyz"
               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
               "0123456789";
    }

    // Generate the string
    string s;
    for (int i = 0; i < L; i++) {
        s.push_back(rnd.any(pool));
    }

    // Output the test case
    println(s);
    return 0;
}
