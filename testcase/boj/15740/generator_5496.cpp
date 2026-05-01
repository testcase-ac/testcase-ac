#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for length distribution
    int max_len = 20;
    vector<int> tvals = {-2, -1, 0, 1, 2};
    int tA = rnd.any(tvals);
    int tB = rnd.any(tvals);

    // Sample lengths with weighted randomness
    int lenA = rnd.wnext(max_len, tA);
    if (lenA < 1) lenA = 1;
    int lenB = rnd.wnext(max_len, tB);
    if (lenB < 1) lenB = 1;

    // Function to generate a positive number string of given length
    auto genNum = [&](int len) {
        string s;
        s.reserve(len + 1);
        for (int i = 0; i < len; ++i) {
            int d = rnd.next(0, 9);
            if (i == 0 && len > 1) {
                // no leading zero if more than one digit
                d = rnd.next(1, 9);
            }
            s.push_back(char('0' + d));
        }
        return s;
    };

    string A = genNum(lenA);
    string B = genNum(lenB);

    // Hyper-parameters for sign probability
    double negProbA = rnd.next(0.0, 1.0);
    double negProbB = rnd.next(0.0, 1.0);

    // Assign signs, but avoid "-0"
    if (!(lenA == 1 && A == "0") && rnd.next() < negProbA) {
        A = "-" + A;
    }
    if (!(lenB == 1 && B == "0") && rnd.next() < negProbB) {
        B = "-" + B;
    }

    // Output the test case
    println(A, B);
    return 0;
}
