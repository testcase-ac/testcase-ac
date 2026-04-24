#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: bias for length distribution (-1 small, 0 uniform, 1 large)
    vector<int> tb = {-1, 0, 1};
    int t = rnd.any(tb);
    int len0 = rnd.wnext(10, t); // in [0,9]
    int L = len0 + 1;            // in [1,10]
    // Hyper-parameter: probability to pick a wrap-around character
    double pWrap = rnd.next(0.0, 1.0);

    string orig, enc;
    orig.reserve(L);
    enc.reserve(L);
    for (int i = 0; i < L; i++) {
        char c;
        // with probability pWrap pick original in X,Y,Z to test wrap-around
        if (rnd.next() < pWrap) {
            c = char(rnd.next('X', 'Z'));
        } else {
            c = char(rnd.next('A', 'W'));
        }
        orig.push_back(c);
        // encrypt: shift by +3 mod 26
        char e = char((c - 'A' + 3) % 26 + 'A');
        enc.push_back(e);
    }

    // Output the encrypted word as the test input
    println(enc);
    return 0;
}
