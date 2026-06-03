#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomString(int len, const string& alphabet) {
    string s;
    for (int i = 0; i < len; ++i) {
        s += alphabet[rnd.next((int)alphabet.size())];
    }
    return s;
}

string shuffledCopy(string s) {
    shuffle(s.begin(), s.end());
    return s;
}

char differentChar(char c, const string& alphabet) {
    char d = c;
    while (d == c) {
        d = alphabet[rnd.next((int)alphabet.size())];
    }
    return d;
}

string makePossibleSameLength(const string& s, const string& alphabet) {
    string t = shuffledCopy(s);
    int pos = rnd.next((int)t.size());
    t[pos] = differentChar(t[pos], alphabet);
    return t;
}

string makePossiblePadded(const string& s, const string& alphabet) {
    string middle = shuffledCopy(s);
    int mode = rnd.next(3);
    if (mode == 0) {
        int pos = rnd.next((int)middle.size());
        middle[pos] = differentChar(middle[pos], alphabet);
    }

    string left = randomString(rnd.next(0, 6), alphabet);
    string right = randomString(rnd.next(0, 6), alphabet);
    string t = left + middle + right;

    if (mode == 1 && !left.empty()) {
        int pos = rnd.next((int)left.size());
        t[pos] = differentChar(t[pos], alphabet);
    } else if (mode == 2 && !right.empty()) {
        int start = (int)(left.size() + middle.size());
        int pos = rnd.next(start, (int)t.size() - 1);
        t[pos] = differentChar(t[pos], alphabet);
    } else if (t == middle) {
        int pos = rnd.next((int)t.size());
        t[pos] = differentChar(t[pos], alphabet);
    }

    return t;
}

string makeNearMiss(const string& s, const string& alphabet) {
    if ((int)s.size() == 1 || rnd.next(2) == 0) {
        return randomString(rnd.next(1, max(1, (int)s.size() - 1)), alphabet);
    }

    string t = shuffledCopy(s);
    int first = rnd.next((int)t.size());
    int second = rnd.next((int)t.size());
    while (second == first) {
        second = rnd.next((int)t.size());
    }
    t[first] = differentChar(t[first], alphabet);
    t[second] = differentChar(t[second], alphabet);
    return t;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> alphabets = {"ab", "abc", "abcd", "abcdefghijklmnopqrstuvwxyz"};
    string alphabet = alphabets[rnd.next((int)alphabets.size())];

    int sLen = rnd.next(1, 24);
    if (rnd.next(5) == 0) {
        sLen = rnd.next(1, 6);
        alphabet = string(1, char('a' + rnd.next(26)));
    }

    string s = randomString(sLen, alphabet);
    int n = rnd.next(8, 20);

    vector<string> queries;
    queries.push_back(makePossibleSameLength(s, "abcdefghijklmnopqrstuvwxyz"));
    queries.push_back(makePossiblePadded(s, "abcdefghijklmnopqrstuvwxyz"));
    queries.push_back(makeNearMiss(s, "abcdefghijklmnopqrstuvwxyz"));

    while ((int)queries.size() < n) {
        int mode = rnd.next(6);
        if (mode == 0) {
            queries.push_back(makePossibleSameLength(s, "abcdefghijklmnopqrstuvwxyz"));
        } else if (mode == 1) {
            queries.push_back(makePossiblePadded(s, "abcdefghijklmnopqrstuvwxyz"));
        } else if (mode == 2) {
            queries.push_back(makeNearMiss(s, "abcdefghijklmnopqrstuvwxyz"));
        } else if (mode == 3) {
            queries.push_back(randomString(rnd.next(1, 30), "abcdefghijklmnopqrstuvwxyz"));
        } else if (mode == 4) {
            string t = randomString(rnd.next(0, 5), "abcdefghijklmnopqrstuvwxyz") + shuffledCopy(s);
            t += randomString(rnd.next(0, 5), "abcdefghijklmnopqrstuvwxyz");
            queries.push_back(t);
        } else {
            queries.push_back(randomString(rnd.next(1, 30), alphabet));
        }
    }

    shuffle(queries.begin(), queries.end());

    println(s);
    println(n);
    for (const string& t : queries) {
        println(t);
    }

    return 0;
}
