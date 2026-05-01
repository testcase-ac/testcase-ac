#include "testlib.h"
#include <string>
using namespace std;

string genNonZero(int len) {
    string s;
    if (len == 1) {
        // single digit 1-9
        s.push_back(char('1' + rnd.next(0, 8)));
    } else {
        // first digit 1-9
        s.push_back(char('1' + rnd.next(0, 8)));
        for (int i = 1; i < len; i++) {
            s.push_back(char('0' + rnd.next(0, 9)));
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxLen = 25;
    int scenario = rnd.next(0, 5);

    int N = 0, M = 0;
    string A, B;

    switch (scenario) {
        case 0: {
            // both small lengths [1,4]
            N = rnd.next(1, 4);
            M = rnd.next(1, 4);
            A = genNonZero(N);
            B = genNonZero(M);
            break;
        }
        case 1: {
            // one small [1,4], one medium [5,maxLen]
            int smallLen = rnd.next(1, 4);
            int medLen = rnd.next(5, maxLen);
            if (rnd.next(0,1) == 0) {
                N = smallLen;
                M = medLen;
                A = genNonZero(N);
                B = genNonZero(M);
            } else {
                N = medLen;
                M = smallLen;
                A = genNonZero(N);
                B = genNonZero(M);
            }
            break;
        }
        case 2: {
            // both medium [maxLen/2, maxLen]
            int minLen = maxLen / 2;
            N = rnd.next(minLen, maxLen);
            M = rnd.next(minLen, maxLen);
            A = genNonZero(N);
            B = genNonZero(M);
            break;
        }
        case 3: {
            // zero case: one of them is "0"
            if (rnd.next(0,1) == 0) {
                N = 1;
                A = "0";
                M = rnd.next(1, maxLen);
                B = genNonZero(M);
            } else {
                M = 1;
                B = "0";
                N = rnd.next(1, maxLen);
                A = genNonZero(N);
            }
            break;
        }
        case 4: {
            // uniform random lengths [1, maxLen]
            N = rnd.next(1, maxLen);
            M = rnd.next(1, maxLen);
            A = genNonZero(N);
            B = genNonZero(M);
            break;
        }
        case 5: {
            // power-of-ten case: both are 1 followed by zeros
            N = rnd.next(2, maxLen);
            M = rnd.next(2, maxLen);
            A = "1" + string(N - 1, '0');
            B = "1" + string(M - 1, '0');
            break;
        }
    }

    println(N, M);
    println(A);
    println(B);

    return 0;
}
