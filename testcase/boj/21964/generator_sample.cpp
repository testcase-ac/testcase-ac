#include "testlib.h"
#include <string>

using namespace std;

namespace {
char randomChar(const string& alphabet) {
    return alphabet[rnd.next((int)alphabet.size())];
}

string randomString(int n, const string& alphabet) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(randomChar(alphabet));
    }
    return s;
}
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string lower = "abcdefghijklmnopqrstuvwxyz";
    const string punctuation = ",.";
    const string all = upper + lower + punctuation;

    int mode = rnd.next(0, 5);
    int n;
    string alphabet = all;

    if (mode == 0) {
        n = 5;
    } else if (mode == 1) {
        n = rnd.next(6, 12);
        alphabet = upper + lower;
    } else if (mode == 2) {
        n = rnd.next(13, 30);
        alphabet = punctuation + lower;
    } else if (mode == 3) {
        n = rnd.next(31, 80);
    } else if (mode == 4) {
        n = rnd.next(81, 200);
        alphabet = punctuation + upper + lower;
    } else {
        n = rnd.next(5, 30);
        alphabet = punctuation;
    }

    string s = randomString(n, alphabet);

    if (mode == 1 && n >= 5) {
        string tail = randomString(5, upper + lower + punctuation);
        s.replace(n - 5, 5, tail);
    }

    println(n);
    println(s);

    return 0;
}
