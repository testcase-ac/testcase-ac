#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomString(int length, const string& alphabet) {
    string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result.push_back(rnd.any(alphabet));
    }
    return result;
}

string shuffledCopy(string value) {
    shuffle(value.begin(), value.end());
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> alphabets = {
        "ab",
        "abc",
        "abcd",
        "abcde",
        "abcdefghijklmnopqrstuvwxyz",
    };

    string s1;
    string s2;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 24);
        int m = rnd.next(1, 24);
        s1 = randomString(n, "abc");
        s2 = randomString(m, "xyz");
    } else if (mode == 1) {
        char a = char('a' + rnd.next(0, 25));
        char b = char('a' + rnd.next(0, 25));
        int n = rnd.next(1, 30);
        int m = rnd.next(1, 30);
        s1 = string(n, a);
        s2 = string(m, b);
    } else if (mode == 2) {
        string alphabet = rnd.any(alphabets);
        int windowLen = rnd.next(1, 12);
        string window = randomString(windowLen, alphabet);
        string leftNoise = randomString(rnd.next(0, 8), "xyz");
        string rightNoise = randomString(rnd.next(0, 8), "xyz");
        string midNoise = randomString(rnd.next(0, 8), "uvw");
        s1 = leftNoise + window + rightNoise;
        s2 = midNoise + shuffledCopy(window) + randomString(rnd.next(0, 8), "uvw");
    } else if (mode == 3) {
        int n = rnd.next(5, 30);
        int m = rnd.next(5, 30);
        int split = rnd.next(1, 25);
        string leftAlphabet = string("abcdefghijklmnopqrstuvwxyz").substr(0, split + 1);
        string rightAlphabet = string("abcdefghijklmnopqrstuvwxyz").substr(split);
        s1 = randomString(n, leftAlphabet);
        s2 = randomString(m, rightAlphabet);
    } else if (mode == 4) {
        int blocks = rnd.next(2, 8);
        for (int i = 0; i < blocks; ++i) {
            char c = char('a' + rnd.next(0, 5));
            int count = rnd.next(1, 5);
            s1 += string(count, c);
            if (rnd.next(0, 1)) {
                s2 += string(count, c);
            } else {
                s2 += string(rnd.next(1, 5), char('a' + rnd.next(0, 5)));
            }
        }
        if (rnd.next(0, 1)) {
            reverse(s2.begin(), s2.end());
        }
    } else {
        string alphabet = rnd.any(alphabets);
        int n = rnd.next(1, 30);
        int m = rnd.next(1, 30);
        s1 = randomString(n, alphabet);
        s2 = randomString(m, alphabet);
    }

    println(s1);
    println(s2);
    return 0;
}
