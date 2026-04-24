#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for (a,b) diversity
    int caseType = rnd.next(0, 5);
    int a, b;
    if (caseType == 0) {
        // both small
        a = rnd.next(1, 10);
        b = rnd.next(1, 10);
    } else if (caseType == 1) {
        // a small, b medium
        a = rnd.next(1, 10);
        b = rnd.next(50, 100);
    } else if (caseType == 2) {
        // a medium, b small
        a = rnd.next(50, 100);
        b = rnd.next(1, 10);
    } else if (caseType == 3) {
        // equal values
        a = rnd.next(1, 100);
        b = a;
    } else if (caseType == 4) {
        // one divisor is 1
        if (rnd.next(0,1) == 0) {
            a = 1;
            b = rnd.next(1, 1000);
        } else {
            b = 1;
            a = rnd.next(1, 1000);
        }
    } else {
        // both large
        a = rnd.next(50000, 100000);
        b = rnd.next(50000, 100000);
    }

    // Length of transcript
    int L = rnd.next(1, 20);

    // Start position c: sometimes small, sometimes large
    int c_max = 100000 - (L - 1);
    int c;
    if (rnd.next(0,1) == 0) {
        c = rnd.next(1, min(50, c_max));
    } else {
        c = rnd.next(1000, c_max);
    }
    int d = c + L - 1;

    // Build the transcript
    vector<string> out;
    out.reserve(L);
    for (int x = c; x <= d; x++) {
        bool divA = (x % a == 0);
        bool divB = (x % b == 0);
        if (divA && divB) {
            out.push_back("FizzBuzz");
        } else if (divA) {
            out.push_back("Fizz");
        } else if (divB) {
            out.push_back("Buzz");
        } else {
            out.push_back(to_string(x));
        }
    }

    // Output
    println(c, d);
    println(out);

    return 0;
}
