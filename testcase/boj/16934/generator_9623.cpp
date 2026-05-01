#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> names;

    int scenario = rnd.next(0, 7);

    if (scenario == 0) {
        // Exactly example 1
        names = {
            "baekjoon",
            "startlink",
            "bakejoon",
            "beakjoon",
            "baekjoon"
        };
    } else if (scenario == 1) {
        // Exactly example 2
        names = {
            "codeplus",
            "startlink",
            "beakjoon",
            "baek",
            "baekjoon",
            "baek",
            "codingwiki"
        };
    } else if (scenario == 2) {
        // Exactly example 3
        names = {
            "abcd",
            "ab",
            "ab",
            "a",
            "a",
            "ab"
        };
    } else if (scenario == 3) {
        // Many identical nicknames
        int N = rnd.next(2, 15);
        int len = rnd.next(1, 4);
        string base;
        for (int i = 0; i < len; ++i)
            base += char('a' + rnd.next(0, 1)); // 'a' or 'b'
        for (int i = 0; i < N; ++i)
            names.push_back(base);
    } else if (scenario == 4) {
        // Chain of prefixes from a common base, plus some duplicates
        int L = rnd.next(2, 10);
        string base;
        for (int i = 0; i < L; ++i)
            base += char('a' + rnd.next(0, 3)); // 'a'..'d'
        for (int len = 1; len <= L; ++len)
            names.push_back(base.substr(0, len));

        int extra = rnd.next(0, 3);
        for (int i = 0; i < extra; ++i) {
            int idx = rnd.next(0, (int)names.size() - 1);
            names.push_back(names[idx]);
        }
    } else if (scenario == 5) {
        // Mixed: duplicates, prefixes, extensions, and new randoms over small alphabet
        int N = rnd.next(5, 20);
        string prev = "";
        for (int i = 0; i < N; ++i) {
            int type = rnd.next(0, 2); // 0: duplicate, 1: prefix/extension, 2: new
            if (i > 0 && type == 0) {
                // Exact duplicate of previous
                names.push_back(prev);
            } else if (i > 0 && type == 1 && !prev.empty()) {
                // Prefix or extension of previous
                int lenprev = (int)prev.size();
                bool makePrefix = rnd.next(0, 1);
                string s;
                if (makePrefix || lenprev == 10) {
                    // Take some prefix of prev
                    int l = rnd.next(1, lenprev);
                    s = prev.substr(0, l);
                } else {
                    // Extend prev (keeping length <= 10)
                    s = prev;
                    int left = 10 - (int)s.size();
                    if (left > 0) {
                        int addLen = rnd.next(1, left);
                        for (int k = 0; k < addLen; ++k)
                            s += char('a' + rnd.next(0, 2)); // 'a'..'c'
                    }
                }
                names.push_back(s);
                prev = s;
            } else {
                // Completely new random over small alphabet
                int L = rnd.next(1, 10);
                string s;
                for (int j = 0; j < L; ++j)
                    s += char('a' + rnd.next(0, 2)); // 'a'..'c'
                names.push_back(s);
                prev = s;
            }
        }
    } else if (scenario == 6) {
        // Carefully crafted prefix & duplicate interactions
        names = {
            "a",
            "ab",
            "abc",
            "abcd",
            "abc",
            "abcd",
            "abc",
            "a",
            "ab",
            "abc",
            "ab"
        };
    } else if (scenario == 7) {
        // Generic random small/medium test, mostly distinct
        int N = rnd.next(1, 25);
        int alphaType = rnd.next(0, 1);
        int alphaSize = (alphaType == 0 ? 3 : 26); // small or full alphabet

        for (int i = 0; i < N; ++i) {
            int L;
            if (rnd.next(0, 4) == 0)
                L = rnd.next(1, 3);
            else
                L = rnd.next(3, 10);
            string s;
            for (int j = 0; j < L; ++j)
                s += char('a' + rnd.next(0, alphaSize - 1));
            names.push_back(s);
        }
    }

    int N = (int)names.size();
    println(N);
    for (const string &s : names)
        println(s);

    return 0;
}
