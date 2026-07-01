#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

static bool isSpecial(const string& s) {
    for (int split = 1; split < static_cast<int>(s.size()); ++split) {
        if (!(s.substr(0, split) < s.substr(split))) {
            return false;
        }
    }
    return true;
}

static string randomBinaryString(int length) {
    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i) {
        s.push_back(static_cast<char>('0' + rnd.next(0, 1)));
    }
    return s;
}

static string randomSmallSpecial() {
    int length = rnd.next(1, 18);
    for (int attempt = 0; attempt < 20000; ++attempt) {
        string s = randomBinaryString(length);
        if (isSpecial(s)) {
            return s;
        }
    }

    int zeros = rnd.next(1, length - 1);
    return string(zeros, '0') + string(length - zeros, '1');
}

static string randomMonotoneSpecial(int minLength, int maxLength) {
    int length = rnd.next(minLength, maxLength);
    if (length == 1) {
        return string(1, static_cast<char>('0' + rnd.next(0, 1)));
    }

    int zeros = rnd.next(1, length - 1);
    return string(zeros, '0') + string(length - zeros, '1');
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> boundary = {"0", "1", "01", "001", "011"};

    string s;
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        s = rnd.any(boundary);
    } else if (mode <= 3) {
        s = randomSmallSpecial();
    } else if (mode == 4) {
        s = randomMonotoneSpecial(19, 50);
    } else {
        s = randomMonotoneSpecial(2, 50);
    }

    ensuref(isSpecial(s), "generator produced a non-special string: %s", s.c_str());
    println(s);
    return 0;
}
