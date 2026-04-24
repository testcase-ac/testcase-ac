#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Roman numeral tables for tens and ones (0-9)
    vector<string> tens = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    vector<string> ones = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

    // Hyper-parameters: bias for tens and ones distribution
    int tBias = rnd.next(-2, 2);
    int uBias = rnd.next(-2, 2);

    // Sample digits with bias: rnd.wnext(10, bias) -> [0,9]
    int T = rnd.wnext(10, tBias);
    int U = rnd.wnext(10, uBias);
    // Ensure the number is at least 1
    if (T == 0 && U == 0) {
        U = rnd.next(1, 9);
    }

    // Build roman numeral
    string roman = tens[T] + ones[U];
    println(roman);

    return 0;
}
