#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string alphabetPrefix(int k) {
    return string("ABCD").substr(0, k);
}

string randomWord(int len, const string& alphabet) {
    string s;
    for (int i = 0; i < len; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

string repeatedBlocks(const string& order, int maxRun) {
    string s;
    for (char c : order) {
        int run = rnd.next(1, maxRun);
        s += string(run, c);
    }
    return s.substr(0, min<int>(9, s.size()));
}

string alternatingWord(const string& pattern, int len) {
    string s;
    for (int i = 0; i < len; ++i) {
        s += pattern[i % pattern.size()];
    }
    return s;
}

string noisySubsequence(const string& base, int targetLen, const string& alphabet) {
    string s;
    for (char c : base) {
        if ((int)s.size() < targetLen && rnd.next(0, 99) < 75) {
            s += c;
        }
    }
    while ((int)s.size() < targetLen) {
        s += rnd.any(alphabet);
    }
    shuffle(s.begin(), s.end());
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = mode == 0 ? rnd.next(1, 2) : rnd.next(2, 6);
    vector<string> words;

    if (mode == 0) {
        string alphabet = alphabetPrefix(rnd.next(1, 4));
        for (int i = 0; i < n; ++i) {
            words.push_back(randomWord(rnd.next(1, 9), alphabet));
        }
    } else if (mode == 1) {
        string letters = "ABCD";
        shuffle(letters.begin(), letters.end());
        for (int i = 0; i < n; ++i) {
            string order = letters;
            if (rnd.next(0, 1)) {
                reverse(order.begin(), order.end());
            }
            rotate(order.begin(), order.begin() + rnd.next(0, 3), order.end());
            words.push_back(repeatedBlocks(order, rnd.next(1, 3)));
        }
    } else if (mode == 2) {
        vector<string> patterns = {"AB", "BA", "AC", "CA", "BD", "DB", "CD", "DC", "ABCD", "DCBA"};
        shuffle(patterns.begin(), patterns.end());
        for (int i = 0; i < n; ++i) {
            words.push_back(alternatingWord(patterns[i % patterns.size()], rnd.next(3, 9)));
        }
    } else if (mode == 3) {
        string base = randomWord(rnd.next(6, 9), "ABCD");
        for (int i = 0; i < n; ++i) {
            words.push_back(noisySubsequence(base, rnd.next(1, 9), "ABCD"));
        }
    } else if (mode == 4) {
        vector<string> orders = {"ABCD", "DCBA", "ACBD", "CADB", "BDAC", "DBCA"};
        shuffle(orders.begin(), orders.end());
        for (int i = 0; i < n; ++i) {
            words.push_back(repeatedBlocks(orders[i % orders.size()], rnd.next(1, 3)));
        }
    } else {
        string alphabet = alphabetPrefix(rnd.next(2, 4));
        for (int i = 0; i < n; ++i) {
            int len = rnd.wnext(9, rnd.next(0, 2)) + 1;
            words.push_back(randomWord(len, alphabet));
        }
    }

    println(n);
    for (const string& word : words) {
        println(word);
    }

    return 0;
}
