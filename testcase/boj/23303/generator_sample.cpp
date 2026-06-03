#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char randomChar(const string& alphabet) {
    return alphabet[rnd.next(static_cast<int>(alphabet.size()))];
}

string randomNonMatchingString(int len) {
    const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 ";
    string s;
    while (static_cast<int>(s.size()) < len) {
        char c = randomChar(alphabet);
        if (s.empty() && c == ' ') continue;
        if ((c == '2') && !s.empty() && (s.back() == 'D' || s.back() == 'd')) continue;
        s.push_back(c);
    }
    while (!s.empty() && s.back() == ' ') {
        s.back() = randomChar("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int len = rnd.next(1, 80);
    string s = randomNonMatchingString(len);

    if (mode == 0 || mode == 1) {
        string token = mode == 0 ? "D2" : "d2";
        if (len == 1) {
            s = token;
        } else {
            int pos = rnd.next(0, static_cast<int>(s.size()));
            s.insert(pos, token);
        }
    } else if (mode == 2) {
        vector<string> variants = {"D 2", "d 2", "D02", "d02", "DD2", "dd2"};
        string token = rnd.any(variants);
        int pos = rnd.next(0, static_cast<int>(s.size()));
        s.insert(pos, token);
    } else if (mode == 3) {
        vector<string> variants = {"A2", "a2", "D3", "d3", "2D", "2d"};
        string token = rnd.any(variants);
        int pos = rnd.next(0, static_cast<int>(s.size()));
        s.insert(pos, token);
    } else if (mode == 4) {
        len = rnd.next(1, 25);
        s.clear();
        for (int i = 0; i < len; ++i) {
            s.push_back(randomChar("0123456789"));
        }
    } else {
        len = rnd.next(1, 100);
        s = randomNonMatchingString(len);
    }

    if (s.front() == ' ') s.front() = 'A';
    if (s.back() == ' ') s.back() = '9';

    println(s);
    return 0;
}
