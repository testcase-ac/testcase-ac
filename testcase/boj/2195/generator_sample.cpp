#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomToken(const string& alphabet, int len) {
    string result;
    result.reserve(len);
    for (int i = 0; i < len; ++i) {
        result.push_back(rnd.any(alphabet));
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string lower = "abcdefghijklmnopqrstuvwxyz";
    const string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string digits = "0123456789";
    const string all = lower + upper + digits;

    int mode = rnd.next(0, 5);
    string s;
    string p;

    if (mode == 0) {
        char ch = rnd.any(all);
        s = string(1, ch);
        p = string(rnd.next(1, 30), ch);
    } else if (mode == 1) {
        int distinct = rnd.next(1, 8);
        vector<char> chars(all.begin(), all.end());
        shuffle(chars.begin(), chars.end());
        chars.resize(distinct);

        int sLen = rnd.next(distinct, distinct + 12);
        for (int i = 0; i < sLen; ++i) {
            s.push_back(rnd.any(chars));
        }
        for (char ch : chars) {
            s.push_back(ch);
        }

        int pLen = rnd.next(1, 40);
        for (int i = 0; i < pLen; ++i) {
            p.push_back(rnd.any(chars));
        }
    } else if (mode == 2) {
        int sLen = rnd.next(4, 24);
        s = randomToken(all, sLen);

        int pieces = rnd.next(2, 10);
        for (int i = 0; i < pieces; ++i) {
            int start = rnd.next(0, sLen - 1);
            int len = rnd.next(1, min(8, sLen - start));
            p += s.substr(start, len);
        }
    } else if (mode == 3) {
        string alphabet = lower.substr(0, rnd.next(1, 6));
        if (rnd.next(0, 1)) {
            alphabet += upper.substr(0, rnd.next(1, 6));
        }
        if (rnd.next(0, 1)) {
            alphabet += digits.substr(0, rnd.next(1, 6));
        }

        s = alphabet;
        shuffle(s.begin(), s.end());
        s += randomToken(alphabet, rnd.next(0, 12));

        vector<string> blocks;
        int maxBlock = min(6, int(alphabet.size()));
        for (int len = 1; len <= maxBlock; ++len) {
            blocks.push_back(alphabet.substr(0, len));
        }

        int pLen = rnd.next(1, 45);
        while (int(p.size()) < pLen) {
            string block = rnd.any(blocks);
            if (rnd.next(0, 1)) {
                reverse(block.begin(), block.end());
            }
            p += block;
        }
        p.resize(pLen);
    } else {
        int distinct = rnd.next(2, 12);
        vector<char> chars(all.begin(), all.end());
        shuffle(chars.begin(), chars.end());
        chars.resize(distinct);

        for (char ch : chars) {
            s.push_back(ch);
            if (rnd.next(0, 2) == 0) {
                s.push_back(ch);
            }
        }
        shuffle(s.begin(), s.end());

        int pLen = rnd.next(10, 60);
        for (int i = 0; i < pLen; ++i) {
            char ch = rnd.any(chars);
            int run = rnd.next(1, 4);
            while (run-- && int(p.size()) < pLen) {
                p.push_back(ch);
            }
        }
    }

    println(s);
    println(p);
    return 0;
}
