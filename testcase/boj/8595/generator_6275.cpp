#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // 1) Choose total length n in small/medium/large ranges for variability
    int n;
    int choice = rnd.next(0, 2);
    if (choice == 0) {
        n = rnd.next(1, 10);
    } else if (choice == 1) {
        n = rnd.next(11, 50);
    } else {
        n = rnd.next(51, 200);
    }

    // 2) Hyper-parameter: probability to start a digit-block when possible
    vector<double> probs = {0.0, 0.3, 0.5, 0.7, 1.0};
    double probDigitStart = rnd.any(probs);

    // 3) Build the string ensuring:
    //    - digit blocks of length 1..6
    //    - no two digit-blocks are adjacent (force a letter in between)
    //    - other positions filled by random letters
    string s;
    s.reserve(n);
    bool prevDigit = false;
    int rem = n;
    while (rem > 0) {
        if (prevDigit) {
            // must insert at least one letter after a digit-block
            char c = rnd.next(0,1) ? rnd.next('a','z') : rnd.next('A','Z');
            s.push_back(c);
            rem--;
            prevDigit = false;
        } else {
            // decide to start a digit-block or insert a letter
            if (rnd.next() < probDigitStart) {
                int maxLen = min(6, rem);
                int len = rnd.next(1, maxLen);
                for (int i = 0; i < len; i++) {
                    s.push_back(char('0' + rnd.next(0, 9)));
                }
                rem -= len;
                prevDigit = true;
            } else {
                char c = rnd.next(0,1) ? rnd.next('a','z') : rnd.next('A','Z');
                s.push_back(c);
                rem--;
                prevDigit = false;
            }
        }
    }

    // Output
    println(n);
    println(s);

    return 0;
}
