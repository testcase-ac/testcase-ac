#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string randomString(int m, int alphabetSize) {
    string s;
    for (int i = 0; i < m; ++i) {
        s += char('a' + rnd.next(alphabetSize));
    }
    return s;
}

string palindromeString(int m, int alphabetSize) {
    string s(m, 'a');
    for (int i = 0; i < (m + 1) / 2; ++i) {
        char c = char('a' + rnd.next(alphabetSize));
        s[i] = c;
        s[m - 1 - i] = c;
    }
    return s;
}

string indexedString(int index, int m) {
    string s(m, 'a');
    for (int i = 0; i < m; ++i) {
        s[i] = char('a' + index % 26);
        index /= 26;
    }
    return s;
}

void addUnique(vector<string>& words, set<string>& seen, const string& value) {
    if (!seen.count(value)) {
        seen.insert(value);
        words.push_back(value);
    }
}

void addRandomUnique(vector<string>& words, set<string>& seen, int m, int alphabetSize) {
    for (int attempt = 0; attempt < 2000; ++attempt) {
        string s = randomString(m, alphabetSize);
        if (!seen.count(s)) {
            addUnique(words, seen, s);
            return;
        }
    }

    for (int index = 0;; ++index) {
        string s = indexedString(index, m);
        if (!seen.count(s)) {
            addUnique(words, seen, s);
            return;
        }
    }
}

void addPalindromeUnique(vector<string>& words, set<string>& seen, int m, int alphabetSize) {
    for (int attempt = 0; attempt < 2000; ++attempt) {
        string s = palindromeString(m, alphabetSize);
        if (!seen.count(s)) {
            addUnique(words, seen, s);
            return;
        }
    }
    addRandomUnique(words, seen, m, alphabetSize);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int m = rnd.next(1, 12);
    if (mode == 3) {
        m = 1;
    } else if (mode == 4) {
        m = rnd.next(20, 50);
    }

    int alphabetSize = rnd.next(2, 6);
    if (m == 1) {
        alphabetSize = rnd.next(3, 26);
    }

    vector<string> words;
    set<string> seen;
    int pairCount = 0;
    int palindromeCount = 0;
    int targetN = 0;

    if (mode == 0) {
        pairCount = rnd.next(1, 6);
        palindromeCount = rnd.next(0, 2);
        targetN = rnd.next(2 * pairCount + palindromeCount, 18);
    } else if (mode == 1) {
        pairCount = rnd.next(0, 3);
        palindromeCount = rnd.next(1, 5);
        targetN = rnd.next(2 * pairCount + palindromeCount, 16);
    } else if (mode == 2) {
        pairCount = 0;
        palindromeCount = rnd.next(0, 1);
        targetN = rnd.next(1, 15);
    } else if (mode == 3) {
        pairCount = 0;
        palindromeCount = rnd.next(1, alphabetSize);
        targetN = rnd.next(palindromeCount, alphabetSize);
    } else {
        pairCount = rnd.next(0, 3);
        palindromeCount = rnd.next(0, 1);
        targetN = rnd.next(max(1, 2 * pairCount + palindromeCount), 8);
    }

    for (int i = 0; i < pairCount; ++i) {
        for (int attempt = 0; attempt < 2000; ++attempt) {
            string s = randomString(m, alphabetSize);
            string r = s;
            reverse(r.begin(), r.end());
            if (s != r && !seen.count(s) && !seen.count(r)) {
                addUnique(words, seen, s);
                addUnique(words, seen, r);
                break;
            }
        }
    }

    for (int i = 0; i < palindromeCount && (int)words.size() < targetN; ++i) {
        addPalindromeUnique(words, seen, m, alphabetSize);
    }

    while ((int)words.size() < targetN) {
        addRandomUnique(words, seen, m, alphabetSize);
    }

    shuffle(words.begin(), words.end());

    println((int)words.size(), m);
    for (const string& word : words) {
        println(word);
    }

    return 0;
}
