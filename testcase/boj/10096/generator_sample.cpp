#include "testlib.h"

#include <string>

using namespace std;

string randomUppercaseString(int length, int alphabetSize) {
    string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result.push_back(static_cast<char>('A' + rnd.next(alphabetSize)));
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    string u;

    if (mode == 0) {
        int n = 2 * rnd.next(1, 16);
        u = randomUppercaseString(n, rnd.next(2, 7));
    } else if (mode == 1) {
        int sLength = rnd.next(1, 18);
        int alphabetSize = rnd.next(2, 9);
        string s = randomUppercaseString(sLength, alphabetSize);
        u = s + s;

        int pos = rnd.next(0, static_cast<int>(u.size()));
        char inserted = static_cast<char>('A' + rnd.next(alphabetSize));
        if (rnd.next(3) == 0) {
            inserted = static_cast<char>('A' + alphabetSize + rnd.next(26 - alphabetSize));
        }
        u.insert(u.begin() + pos, inserted);
    } else if (mode == 2) {
        int sLength = rnd.next(1, 18);
        char ch = static_cast<char>('A' + rnd.next(26));
        u.assign(2 * sLength + 1, ch);
    } else {
        int sLength = rnd.next(1, 18);
        int alphabetSize = rnd.next(3, 10);
        u = randomUppercaseString(2 * sLength + 1, alphabetSize);
    }

    println(static_cast<int>(u.size()));
    println(u);

    return 0;
}
