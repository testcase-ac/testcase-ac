#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

bool luhn_valid(const string &s) {
    int sum = 0;
    for (int i = 0; i < 16; i++) {
        int d = s[i] - '0';
        int pos = 16 - i;
        if (pos % 2 == 0) {
            int dd = d * 2;
            if (dd >= 10) dd = dd / 10 + dd % 10;
            sum += dd;
        } else {
            sum += d;
        }
    }
    return sum % 10 == 0;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 10);
    double probValid = rnd.next(0.3, 0.7);
    bool allowLeadZero = rnd.next(0, 1) == 1;
    println(T);
    for (int ti = 0; ti < T; ti++) {
        bool makeValid = rnd.next() < probValid;
        if (makeValid) {
            // generate a valid card
            string s;
            s.reserve(16);
            // first 15 digits
            s.push_back('0' + rnd.next(allowLeadZero ? 0 : 1, 9));
            for (int i = 1; i < 15; i++)
                s.push_back('0' + rnd.next(0, 9));
            // compute checksum
            int sum = 0;
            for (int i = 0; i < 15; i++) {
                int d = s[i] - '0';
                int pos = 16 - i;
                if (pos % 2 == 0) {
                    int dd = d * 2;
                    if (dd >= 10) dd = dd / 10 + dd % 10;
                    sum += dd;
                } else {
                    sum += d;
                }
            }
            int check = (10 - (sum % 10)) % 10;
            s.push_back('0' + check);
            println(s);
        } else {
            // generate an invalid card
            if (rnd.next(0, 1) == 0) {
                // flip the last digit of a valid card
                string s;
                s.reserve(16);
                s.push_back('0' + rnd.next(allowLeadZero ? 0 : 1, 9));
                for (int i = 1; i < 15; i++)
                    s.push_back('0' + rnd.next(0, 9));
                int sum = 0;
                for (int i = 0; i < 15; i++) {
                    int d = s[i] - '0';
                    int pos = 16 - i;
                    if (pos % 2 == 0) {
                        int dd = d * 2;
                        if (dd >= 10) dd = dd / 10 + dd % 10;
                        sum += dd;
                    } else {
                        sum += d;
                    }
                }
                int check = (10 - (sum % 10)) % 10;
                s.push_back('0' + check);
                int wrong = (check + rnd.next(1, 9)) % 10;
                s[15] = char('0' + wrong);
                println(s);
            } else {
                // random 16-digit, ensure invalid
                string s;
                do {
                    s.clear();
                    s.push_back('0' + rnd.next(allowLeadZero ? 0 : 1, 9));
                    for (int i = 1; i < 16; i++)
                        s.push_back('0' + rnd.next(0, 9));
                } while (luhn_valid(s));
                println(s);
            }
        }
    }
    return 0;
}
