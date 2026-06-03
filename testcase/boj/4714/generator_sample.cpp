#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

static string decimalFromParts(long long whole, int frac, int fracDigits) {
    string s = to_string(whole);
    if (fracDigits == 0) {
        return s;
    }

    string tail = to_string(frac);
    while ((int)tail.size() < fracDigits) {
        tail = "0" + tail;
    }
    return s + "." + tail;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> weights;
    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 12);

    if (mode == 0) {
        weights.push_back("0");
    } else if (mode == 1) {
        weights.push_back(decimalFromParts(rnd.next(0, 9), rnd.next(1, 99), 2));
    } else if (mode == 2) {
        weights.push_back(decimalFromParts(rnd.next(10000, 200000), rnd.next(0, 9), 1));
    } else if (mode == 3) {
        weights.push_back(decimalFromParts(rnd.next(0, 2), rnd.next(1, 9999), 4));
    } else {
        weights.push_back(decimalFromParts(rnd.next(1, 500), 0, 0));
    }

    while ((int)weights.size() < n) {
        int kind = rnd.next(0, 5);
        if (kind == 0) {
            weights.push_back("0");
        } else if (kind == 1) {
            weights.push_back(decimalFromParts(rnd.next(1, 999), rnd.next(0, 9), 1));
        } else if (kind == 2) {
            weights.push_back(decimalFromParts(rnd.next(0, 99), rnd.next(0, 99), 2));
        } else if (kind == 3) {
            weights.push_back(decimalFromParts(rnd.next(1000, 120000), rnd.next(0, 999), 3));
        } else if (kind == 4) {
            weights.push_back(decimalFromParts(rnd.next(0, 1), rnd.next(1, 99999), 5));
        } else {
            weights.push_back(decimalFromParts(rnd.next(1, 999999), 0, 0));
        }
    }

    for (const string& weight : weights) {
        println(weight);
    }
    println("-1.0");

    return 0;
}
