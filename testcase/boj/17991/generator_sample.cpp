#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomNumber(int length) {
    string s;
    s += char('1' + rnd.next(9));
    for (int i = 1; i < length; ++i) {
        s += char('0' + rnd.next(10));
    }
    return s;
}

string carrylessSquare(const string& a) {
    vector<int> c(2 * int(a.size()) - 1, 0);
    for (int i = 0; i < int(a.size()); ++i) {
        for (int j = 0; j < int(a.size()); ++j) {
            c[i + j] = (c[i + j] + (a[i] - '0') * (a[j] - '0')) % 10;
        }
    }

    string result;
    for (int digit : c) {
        result += char('0' + digit);
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(100);
    string n;

    if (mode < 45) {
        int rootLength = rnd.next(1, 13);
        n = carrylessSquare(randomNumber(rootLength));
    } else if (mode < 70) {
        int rootLength = rnd.next(1, 8);
        string root = randomNumber(rootLength);
        for (char& digit : root) {
            if (rnd.next(100) < 35) {
                digit = '0';
            }
        }
        if (root[0] == '0') {
            root[0] = char('1' + rnd.next(9));
        }
        n = carrylessSquare(root);
    } else if (mode < 88) {
        int length = 2 * rnd.next(1, 12);
        n = randomNumber(length);
    } else if (mode < 97) {
        int length = 2 * rnd.next(0, 12) + 1;
        n = randomNumber(length);
    } else {
        n = "10000000000000000000000000";
    }

    println(n);
    return 0;
}
