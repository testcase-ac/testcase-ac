#include "testlib.h"
using namespace std;

string randomNumberWithLength(int len) {
    string s;
    s.reserve(len);
    // first digit != '0'
    s += char('0' + rnd.next(1, 9));
    for (int i = 1; i < len; ++i)
        s += char('0' + rnd.next(0, 9));
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxLongLen = 60;
    vector<string> cases;

    // Ensure all behavior categories are present:

    // Category: answer = 1  (x0 = 1)
    cases.push_back("1");

    // Category: answer = 2, including explicit 0-case
    cases.push_back("0");

    // Category: answer = 3 (length between 2 and 9)
    {
        int lenSmall = rnd.next(2, 9);
        cases.push_back(randomNumberWithLength(lenSmall));
    }

    // Category: answer = 4 (length >= 10)
    {
        int lenLarge = rnd.next(10, maxLongLen);
        cases.push_back(randomNumberWithLength(lenLarge));
    }

    // Add a few extra randomized cases for variability
    int extra = rnd.next(0, 3);
    for (int i = 0; i < extra; ++i) {
        int type = rnd.next(0, 2);
        if (type == 0) {
            // single digit in [2..9]
            char c = char('0' + rnd.next(2, 9));
            cases.push_back(string(1, c));
        } else if (type == 1) {
            // length 2..9
            int len = rnd.next(2, 9);
            cases.push_back(randomNumberWithLength(len));
        } else {
            // length 10..maxLongLen
            int len = rnd.next(10, maxLongLen);
            cases.push_back(randomNumberWithLength(len));
        }
    }

    shuffle(cases.begin(), cases.end());

    for (const string &s : cases)
        println(s);
    println("END");

    return 0;
}
