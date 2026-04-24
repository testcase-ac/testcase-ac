#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Generate A and B within bounds
    int A = rnd.next(1, 100000000);
    int B = rnd.next(1, 100000000);
    // Hyper-parameter for C length: more weight on small lengths
    vector<int> lens = {1, 1, 1, 2, 3, 4};
    int L = rnd.any(lens);
    // Decide parity of C (0 = even, 1 = odd)
    int par = rnd.next(0, 1);
    // Build C as a decimal string of length L with given parity
    string C;
    for (int i = 0; i < L; i++) {
        char d;
        if (L == 1) {
            // Single digit, must be non-zero and match parity
            if (par == 0) {
                vector<char> ev = {'2','4','6','8'};
                d = rnd.any(ev);
            } else {
                vector<char> od = {'1','3','5','7','9'};
                d = rnd.any(od);
            }
        } else {
            if (i == 0) {
                // First digit: 1-9
                vector<char> f;
                for (char c = '1'; c <= '9'; c++) f.push_back(c);
                d = rnd.any(f);
            } else if (i == L - 1) {
                // Last digit: ensure parity
                if (par == 0) {
                    vector<char> ev = {'0','2','4','6','8'};
                    d = rnd.any(ev);
                } else {
                    vector<char> od = {'1','3','5','7','9'};
                    d = rnd.any(od);
                }
            } else {
                // Middle digits: 0-9
                d = char('0' + rnd.next(0, 9));
            }
        }
        C.push_back(d);
    }
    // Output the test case
    println(A, B, C);
    return 0;
}
