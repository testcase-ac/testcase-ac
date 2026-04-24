#include "testlib.h"
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: probability that N == M
    double eqProb = rnd.next(0.0, 1.0);
    // Generate N as a random integer with 1 to 10 digits (no leading zeros except "0")
    int lenN = rnd.next(1, 10);
    string N;
    if (lenN == 1) {
        // single digit 0-9
        N.push_back(char('0' + rnd.next(0, 9)));
    } else {
        // first digit 1-9
        N.push_back(char('1' + rnd.next(0, 8)));
        for (int i = 1; i < lenN; i++) {
            N.push_back(char('0' + rnd.next(0, 9)));
        }
    }
    // Generate M
    string M;
    bool makeEqual = rnd.next() < eqProb;
    if (makeEqual) {
        M = N;
    } else {
        // ensure M != N
        do {
            int lenM = rnd.next(1, 10);
            M.clear();
            if (lenM == 1) {
                M.push_back(char('0' + rnd.next(0, 9)));
            } else {
                M.push_back(char('1' + rnd.next(0, 8)));
                for (int i = 1; i < lenM; i++) {
                    M.push_back(char('0' + rnd.next(0, 9)));
                }
            }
        } while (M == N);
    }
    // Output
    printf("%s %s\n", N.c_str(), M.c_str());
    return 0;
}
