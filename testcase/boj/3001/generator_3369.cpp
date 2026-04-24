#include "testlib.h"
#include <string>
#include <cassert>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // number of digits
    int d = rnd.next(1, 5);
    // sum S between 1 and 9*d
    int S = rnd.next(1, 9 * d);

    // build the smallest d-digit number with digit sum S
    string a;
    int rem = S;
    for (int i = 0; i < d; i++) {
        int start = (i == 0 ? 1 : 0);
        for (int dig = start; dig <= 9; dig++) {
            if (rem - dig < 0) break;
            int maxRem = 9 * (d - i - 1);
            if (rem - dig <= maxRem) {
                a.push_back(char('0' + dig));
                rem -= dig;
                break;
            }
        }
    }
    assert(rem == 0);
    long long A = stoll(a);

    // hyper-parameter for interval extension
    int t = rnd.next(-1, 1);
    int dm = rnd.wnext(101, t); // up to 100
    int delta = rnd.next(0, dm);
    long long B = A + delta;

    // output A, B, S
    println(A, B, S);
    return 0;
}
