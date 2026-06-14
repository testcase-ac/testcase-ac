#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomString(int len, const string& alphabet) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

string periodicString(int len, const string& pattern) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s += pattern[i % pattern.size()];
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> strings;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        string base = randomString(rnd.next(1, 12), "abc");
        int groups = rnd.next(1, 6);
        for (int i = 0; i < groups; ++i) {
            int copies = rnd.next(1, 4);
            for (int j = 0; j < copies; ++j) {
                strings.push_back(base);
            }
            if (rnd.next(0, 1) == 1 && !base.empty()) {
                strings.push_back(base.substr(rnd.next(0, (int)base.size() - 1)));
            }
        }
    } else if (mode == 1) {
        string base = randomString(rnd.next(4, 20), "abcd");
        int startCount = rnd.next(1, min<int>(10, base.size()));
        vector<int> starts;
        for (int i = 0; i < (int)base.size(); ++i) {
            starts.push_back(i);
        }
        shuffle(starts.begin(), starts.end());
        for (int i = 0; i < startCount; ++i) {
            strings.push_back(base.substr(starts[i]));
            if (rnd.next(0, 2) == 0) {
                strings.push_back(base.substr(starts[i]));
            }
        }
    } else if (mode == 2) {
        vector<string> patterns = {"a", "ab", "aba", "abc", "abab", "aab"};
        int n = rnd.next(3, 18);
        for (int i = 0; i < n; ++i) {
            string pattern = rnd.any(patterns);
            strings.push_back(periodicString(rnd.next(1, 24), pattern));
        }
    } else if (mode == 3) {
        string tail = randomString(rnd.next(1, 8), "ab");
        int n = rnd.next(3, 20);
        for (int i = 0; i < n; ++i) {
            string prefix = randomString(rnd.next(0, 8), "cde");
            strings.push_back(prefix + tail);
        }
    } else if (mode == 4) {
        int n = rnd.next(1, 30);
        string alphabet = "abcdefghijklmnopqrstuvwxyz";
        int alphabetSize = rnd.next(1, 6);
        alphabet.resize(alphabetSize);
        for (int i = 0; i < n; ++i) {
            strings.push_back(randomString(rnd.next(1, 30), alphabet));
        }
    } else {
        int n = rnd.next(2, 40);
        for (int i = 0; i < n; ++i) {
            char c = char('a' + rnd.next(0, 3));
            int len = rnd.next(1, 30);
            strings.push_back(string(len, c));
        }
    }

    shuffle(strings.begin(), strings.end());
    if ((int)strings.size() > 1000) {
        strings.resize(1000);
    }

    println((int)strings.size());
    for (const string& s : strings) {
        println(s);
    }

    return 0;
}
