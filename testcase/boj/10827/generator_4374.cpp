#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    vector<int> ipCaps = {1, 9, 99};
    int maxIp = rnd.any(ipCaps);          // integer part max

    vector<int> digitCaps = {3, 5, 9};
    int maxDigits = rnd.any(digitCaps);   // max decimal digits

    vector<int> bWeights = {-2, 0, 2};
    int bWeight = rnd.any(bWeights);      // bias for exponent

    // Generate integer part 0..maxIp
    int ip = rnd.next(0, maxIp);

    // Generate number of fractional digits 1..maxDigits
    int nd = rnd.next(1, maxDigits);

    // Build fractional part digits
    string frac;
    frac.reserve(nd);
    for (int i = 0; i < nd - 1; ++i) {
        frac.push_back(char('0' + rnd.next(0, 9)));
    }
    // Last digit non-zero to avoid trailing zeros and ensure a>0 if ip==0
    frac.push_back(char('0' + rnd.next(1, 9)));

    // Assemble a as string
    string aStr = to_string(ip) + "." + frac;

    // Generate exponent b in [1..100] with bias
    int b = rnd.wnext(100, bWeight) + 1;

    // Output single test
    println(aStr, b);

    return 0;
}
