#include "testlib.h"
#include <string>
#include <utility>
#include <vector>
using namespace std;

const string kChars = "()[]{}*";
const vector<pair<char, char>> kPairs = {{'(', ')'}, {'[', ']'}, {'{', '}'}};

string randomString(int len, const string& alphabet) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s += alphabet[rnd.next((int)alphabet.size())];
    }
    return s;
}

string balancedString(int pairs) {
    string s;
    vector<char> stack;
    stack.reserve(pairs);

    int opened = 0;
    while (opened < pairs || !stack.empty()) {
        bool openNext = opened < pairs && (stack.empty() || rnd.next(0, 99) < 58);
        if (openNext) {
            auto p = kPairs[rnd.next((int)kPairs.size())];
            s += p.first;
            stack.push_back(p.second);
            ++opened;
        } else {
            s += stack.back();
            stack.pop_back();
        }
    }
    return s;
}

void replaceSomeWithWildcards(string& s, int percent) {
    for (char& c : s) {
        if (rnd.next(0, 99) < percent) {
            c = '*';
        }
    }
}

string crossingPattern(int blocks) {
    string s;
    for (int i = 0; i < blocks; ++i) {
        auto a = kPairs[rnd.next((int)kPairs.size())];
        auto b = kPairs[rnd.next((int)kPairs.size())];
        s += a.first;
        s += b.first;
        s += a.second;
        s += b.second;
        if (rnd.next(0, 99) < 35) {
            s += '*';
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 10);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 5);
        string s;

        if (mode == 0) {
            int pairs = rnd.next(1, 12);
            s = balancedString(pairs);
            replaceSomeWithWildcards(s, rnd.next(0, 35));
        } else if (mode == 1) {
            int len = rnd.next(1, 45);
            string alphabet = rnd.any(vector<string>{"()", "[]", "{}"});
            s = randomString(len, alphabet);
        } else if (mode == 2) {
            int len = rnd.next(1, 60);
            s = randomString(len, kChars);
        } else if (mode == 3) {
            int len = rnd.next(1, 55);
            s = randomString(len, "*()[]{}");
            replaceSomeWithWildcards(s, rnd.next(45, 85));
        } else if (mode == 4) {
            int blocks = rnd.next(1, 9);
            s = crossingPattern(blocks);
        } else {
            int left = rnd.next(1, 16);
            int right = rnd.next(0, 16);
            char open = rnd.any(string("([{"));
            char close = rnd.any(string(")]}"));
            s = string(left, open) + randomString(rnd.next(0, 10), "*") + string(right, close);
        }

        if ((int)s.size() > 500) {
            s.resize(500);
        }
        println(s);
    }

    return 0;
}
