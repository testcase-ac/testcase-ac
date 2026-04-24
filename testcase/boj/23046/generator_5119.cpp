#include "testlib.h"
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int n = rnd.next(1, 20);              // total length of the query string
    double revProb = rnd.next();          // probability of a reversal at each position
    int digitWeight = rnd.next(-2, 2);    // weight parameter for digit distribution

    // Build the query string T
    string T;
    T.reserve(n);

    // First character must be a digit '1'..'9'
    int firstDigit = rnd.wnext(9, digitWeight) + 1;
    T.push_back(char('0' + firstDigit));

    // Fill the rest of the string
    for (int i = 1; i < n; i++) {
        if (rnd.next() < revProb) {
            T.push_back('-');
        } else {
            int d = rnd.wnext(9, digitWeight) + 1;
            T.push_back(char('0' + d));
        }
    }

    // Output the generated query string
    printf("%s\n", T.c_str());
    return 0;
}
