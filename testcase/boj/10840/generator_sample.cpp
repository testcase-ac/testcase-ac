#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomString(int len, const string& alphabet) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) s += rnd.any(alphabet);
    return s;
}

string shuffledCopy(string s) {
    shuffle(s.begin(), s.end());
    return s;
}

void insertAtRandomPosition(string& s, const string& block) {
    int pos = rnd.next(0, static_cast<int>(s.size()));
    s.insert(pos, block);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> alphabets = {
        "ab",
        "abc",
        "abcd",
        "abcdef",
        "abcdefghijklmnopqrstuvwxyz",
    };

    int mode = rnd.next(0, 5);
    string a, b;

    if (mode == 0) {
        int n = rnd.next(1, 30);
        int m = rnd.next(1, 30);
        a = randomString(n, "abc");
        b = randomString(m, "xyz");
    } else if (mode == 1) {
        string alphabet = rnd.any(alphabets);
        int blockLen = rnd.next(1, 18);
        string block = randomString(blockLen, alphabet);
        a = randomString(rnd.next(0, 12), alphabet);
        b = randomString(rnd.next(0, 12), alphabet);
        insertAtRandomPosition(a, block);
        insertAtRandomPosition(b, shuffledCopy(block));
        a += randomString(rnd.next(0, 12), alphabet);
        b += randomString(rnd.next(0, 12), alphabet);
    } else if (mode == 2) {
        char ca = static_cast<char>('a' + rnd.next(0, 25));
        char cb = static_cast<char>('a' + rnd.next(0, 25));
        int runA = rnd.next(1, 45);
        int runB = rnd.next(1, 45);
        a = string(runA, ca);
        b = string(runB, cb);
        if (rnd.next(0, 1)) b += string(rnd.next(1, 12), ca);
    } else if (mode == 3) {
        string alphabet = rnd.any(alphabets);
        int n = rnd.next(1, 80);
        int m = rnd.next(1, 80);
        a = randomString(n, alphabet);
        b = randomString(m, alphabet);
    } else if (mode == 4) {
        string left = randomString(rnd.next(1, 15), "abcde");
        string middle = randomString(rnd.next(1, 12), "mnopq");
        string right = randomString(rnd.next(1, 15), "vwxyz");
        a = left + middle + right;
        b = shuffledCopy(right) + shuffledCopy(middle) + shuffledCopy(left);
    } else {
        int n = rnd.next(100, 300);
        int m = rnd.next(100, 300);
        string alphabet = rnd.next(0, 1) ? "abc" : "abcdefghijklmnopqrstuvwxyz";
        a = randomString(n, alphabet);
        b = randomString(m, alphabet);
    }

    println(a);
    println(b);

    return 0;
}
