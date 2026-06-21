#include "testlib.h"
#include <string>

using namespace std;

string randomString(int length, int alphabetSize) {
    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i) {
        s.push_back(char('A' + rnd.next(alphabetSize)));
    }
    return s;
}

string growOnce(const string& source) {
    int sideToRemove = rnd.next(2);
    int attachSide = rnd.next(2);
    string shortened = sideToRemove == 0 ? source.substr(1) : source.substr(0, source.size() - 1);
    return attachSide == 0 ? source + shortened : shortened + source;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    string encrypted;

    if (mode == 0) {
        encrypted = randomString(rnd.next(1, 8), rnd.next(1, 4));
    } else if (mode == 1) {
        encrypted = randomString(rnd.next(9, 30), rnd.next(2, 8));
    } else if (mode == 2) {
        encrypted = string(rnd.next(1, 100), char('A' + rnd.next(3)));
    } else if (mode == 3) {
        string block = randomString(rnd.next(1, 12), rnd.next(1, 5));
        encrypted = block + char('A' + rnd.next(5)) + block;
    } else if (mode == 4) {
        encrypted = randomString(rnd.next(2, 8), rnd.next(1, 4));
        int steps = rnd.next(1, 4);
        for (int i = 0; i < steps && encrypted.size() <= 50; ++i) {
            encrypted = growOnce(encrypted);
        }
    } else {
        encrypted = randomString(100, rnd.next(1, 6));
    }

    println(encrypted);
    return 0;
}
