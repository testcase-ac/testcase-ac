#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

string build_number(int len, int scen) {
    // scen 0: no 5/6; scen 1: only 5/6; scen 2: full mix
    string s;
    for (int pos = 0; pos < len; pos++) {
        vector<char> allowed;
        if (scen == 0) {
            // no '5' or '6'
            for (char d = '0'; d <= '9'; d++) {
                if (d == '5' || d == '6') continue;
                if (pos == 0 && d == '0') continue;
                allowed.push_back(d);
            }
        } else if (scen == 1) {
            // only '5' or '6'
            allowed = {'5', '6'};
        } else {
            // full 0-9
            for (char d = '0'; d <= '9'; d++) {
                if (pos == 0 && d == '0') continue;
                allowed.push_back(d);
            }
        }
        s.push_back(rnd.any(allowed));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // lengths up to 6 digits => values <= 999999
    int lenA = rnd.next(1, 6);
    int lenB = rnd.next(1, 6);
    // scenario for diversity
    int scenA = rnd.next(0, 2);
    int scenB = rnd.next(0, 2);

    string sA = build_number(lenA, scenA);
    string sB = build_number(lenB, scenB);

    int A = stoi(sA);
    int B = stoi(sB);

    println(A, B);
    return 0;
}
