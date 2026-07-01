#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomString(int length, const string& alphabet) {
    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

char differentLowercase(char c, const string& alphabet) {
    char next = rnd.any(alphabet);
    while (next == c) {
        next = rnd.any(alphabet);
    }
    return next;
}

string mutateOne(string s, const string& alphabet) {
    int pos = rnd.next(0, int(s.size()) - 1);
    s[pos] = differentLowercase(s[pos], alphabet);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string smallAlphabet = "abc";
    const string fullAlphabet = "abcdefghijklmnopqrstuvwxyz";
    int n = rnd.next(8, 18);
    vector<pair<string, string>> cases;
    cases.reserve(n);

    for (int tc = 0; tc < n; ++tc) {
        int mode = rnd.next(0, 5);
        const string& alphabet = rnd.next(0, 4) == 0 ? fullAlphabet : smallAlphabet;

        int targetLength = rnd.next(1, 10);
        string target = randomString(targetLength, alphabet);
        string initial;

        if (mode == 0) {
            initial = rnd.next(0, 1) == 0 ? target : mutateOne(target, alphabet);
        } else if (mode == 1) {
            int extra = 2 * rnd.next(1, 5);
            int left = extra / 2;
            int right = extra - left;
            initial = randomString(left, alphabet) + target + randomString(right, alphabet);
        } else if (mode == 2) {
            int extra = 2 * rnd.next(0, 4) + 1;
            int left = extra / 2;
            int right = extra - left;
            initial = randomString(left, alphabet) + target + randomString(right, alphabet);
        } else if (mode == 3) {
            int extra = rnd.next(1, 10);
            int left = rnd.next(0, extra);
            int right = extra - left;
            initial = randomString(left, alphabet) + mutateOne(target, alphabet) + randomString(right, alphabet);
        } else if (mode == 4) {
            char fill = rnd.any(smallAlphabet);
            targetLength = rnd.next(1, 12);
            target.assign(targetLength, fill);
            int extra = rnd.next(0, 12);
            initial.assign(targetLength + extra, fill);
            if (extra > 0 && rnd.next(0, 2) == 0) {
                initial[rnd.next(0, int(initial.size()) - 1)] = differentLowercase(fill, smallAlphabet);
            }
        } else {
            int initialLength = rnd.next(targetLength, 25);
            initial = randomString(initialLength, alphabet);
            if (rnd.next(0, 2) == 0) {
                int start = rnd.next(0, initialLength - targetLength);
                target = initial.substr(start, targetLength);
            }
        }

        cases.emplace_back(initial, target);
    }

    println(int(cases.size()));
    for (const auto& test : cases) {
        println(test.first, test.second);
    }

    return 0;
}
