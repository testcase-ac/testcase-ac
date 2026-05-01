#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for string length: bias to small or large
    vector<int> tLvals = {-3, -2, -1, 0, 1, 2, 3};
    int tL = rnd.any(tLvals);
    int L = rnd.wnext(20, tL) + 1;  // Length between 1 and 20

    // Choose string generation type: 0=random, 1=periodic, 2=uniform char
    int type = rnd.next(0, 2);
    string S;
    if (type == 0) {
        // Fully random string
        for (int i = 0; i < L; ++i)
            S += char('a' + rnd.next(0, 25));
    } else if (type == 1) {
        // Periodic string based on a random base of length p
        int p = rnd.next(1, L);
        string base;
        for (int i = 0; i < p; ++i)
            base += char('a' + rnd.next(0, 25));
        for (int i = 0; i < L; ++i)
            S += base[i % p];
    } else {
        // Uniform character string
        char c = char('a' + rnd.next(0, 25));
        S = string(L, c);
    }

    // Hyper-parameter for K scale: small, medium, or large
    vector<int> his = {10, 1000, 1000000};
    int hi = rnd.any(his);
    vector<int> tKvals = {-3, -2, -1, 0, 1, 2, 3};
    int tK = rnd.any(tKvals);
    int K = rnd.wnext(hi, tK) + 1;  // K between 1 and hi

    // Output
    println(S, K);
    return 0;
}
