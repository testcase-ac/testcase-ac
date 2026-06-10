#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string randomWord(int len, const string& alphabet) {
    string s;
    for (int i = 0; i < len; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

string makeUnusedWord(set<string>& used, int minLen, int maxLen, const string& alphabet) {
    while (true) {
        string s = randomWord(rnd.next(minLen, maxLen), alphabet);
        if (used.insert(s).second) {
            return s;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string alphabet = "ABCDE";
    if (rnd.next(4) == 0) {
        alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    } else if (rnd.next(3) == 0) {
        alphabet = "ABC";
    }

    int mode = rnd.next(4);
    int n = rnd.next(4, 24);
    int m = rnd.next(1, 6);

    vector<pair<string, string>> entries;
    set<string> usedQ;
    set<string> usedA;

    if (mode == 0) {
        string base = randomWord(rnd.next(5, 10), alphabet);
        int chainLen = rnd.next(3, min(10, (int)base.size()));
        for (int len = 1; len <= chainLen && (int)entries.size() < n; ++len) {
            string q = base.substr(0, len);
            if (usedQ.insert(q).second) {
                entries.push_back({q, makeUnusedWord(usedA, 1, 10, alphabet)});
            }
        }
    } else if (mode == 1) {
        string left = randomWord(rnd.next(2, 5), alphabet);
        string right = randomWord(rnd.next(2, 5), alphabet);
        vector<string> candidates = {
            left,
            right,
            left + right,
            left.substr(0, 1) + right,
            left + right.substr(0, 1)
        };
        for (const string& q : candidates) {
            if ((int)q.size() <= 10 && usedQ.insert(q).second) {
                entries.push_back({q, makeUnusedWord(usedA, 1, 10, alphabet)});
            }
        }
    } else if (mode == 2) {
        int repeats = rnd.next(2, 10);
        for (int len = 1; len <= repeats && (int)entries.size() < n; ++len) {
            string q(len, rnd.any(alphabet));
            if (usedQ.insert(q).second) {
                entries.push_back({q, makeUnusedWord(usedA, 1, 10, alphabet)});
            }
        }
    }

    while ((int)entries.size() < n) {
        string q = makeUnusedWord(usedQ, 1, 10, alphabet);
        string a = makeUnusedWord(usedA, 1, 10, alphabet);
        entries.push_back({q, a});
    }

    shuffle(entries.begin(), entries.end());

    vector<string> sentences;
    string noiseAlphabet = "XYZ";
    if (alphabet.find('X') != string::npos) {
        noiseAlphabet = "QRS";
    }

    for (int i = 0; i < m; ++i) {
        string s;
        int targetLen = rnd.next(1, 80);
        if (i == 0 || rnd.next(3) != 0) {
            while ((int)s.size() < targetLen) {
                if (rnd.next(4) == 0) {
                    s += randomWord(rnd.next(1, 4), noiseAlphabet);
                } else {
                    s += rnd.any(entries).first;
                }
            }
        } else {
            s = randomWord(targetLen, noiseAlphabet);
        }
        if ((int)s.size() > 100) {
            s.resize(100);
        }
        if (s.empty()) {
            s = randomWord(1, noiseAlphabet);
        }
        sentences.push_back(s);
    }

    println(n, m);
    for (const auto& entry : entries) {
        println(entry.first, entry.second);
    }
    for (const string& sentence : sentences) {
        println(sentence);
    }

    return 0;
}
