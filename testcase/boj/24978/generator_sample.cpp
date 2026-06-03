#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string randomQuery(const string& alphabet, int maxLen) {
    int len = rnd.next(1, maxLen);
    vector<char> chars(alphabet.begin(), alphabet.end());
    shuffle(chars.begin(), chars.end());
    chars.resize(len);
    sort(chars.begin(), chars.end());
    return string(chars.begin(), chars.end());
}

string randomString(const string& alphabet, int len) {
    string result;
    for (int i = 0; i < len; ++i) {
        result += rnd.any(alphabet);
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string fullAlphabet = "abcdefghijklmnopqr";
    int alphabetSize = rnd.next(1, 8);
    string alphabet = fullAlphabet.substr(0, alphabetSize);

    int mode = rnd.next(0, 5);
    int baseLen = rnd.next(1, 24);
    string s;
    string t;

    if (mode == 0) {
        s = randomString(alphabet, baseLen);
        t = s;
    } else if (mode == 1) {
        s = randomString(alphabet, baseLen);
        t = s;
        shuffle(t.begin(), t.end());
    } else if (mode == 2) {
        s = randomString(alphabet, baseLen);
        t = s;
        int pos = rnd.next(0, static_cast<int>(t.size()) - 1);
        t[pos] = rnd.any(alphabet);
    } else if (mode == 3) {
        int half = rnd.next(1, 10);
        string a = alphabet.substr(0, min(2, alphabetSize));
        s = string(half, a[0]) + string(half, a.back());
        t = string(half, a.back()) + string(half, a[0]);
    } else if (mode == 4) {
        s = randomString(alphabet, baseLen);
        t = randomString(alphabet, rnd.next(1, 24));
    } else {
        string coreAlphabet = alphabet.substr(0, max(1, alphabetSize / 2));
        string noiseAlphabet = alphabet.substr(coreAlphabet.size());
        if (noiseAlphabet.empty()) {
            noiseAlphabet = coreAlphabet;
        }

        string core = randomString(coreAlphabet, rnd.next(1, 12));
        s = core;
        t = core;
        int noiseCount = rnd.next(1, 8);
        for (int i = 0; i < noiseCount; ++i) {
            s.insert(rnd.next(0, static_cast<int>(s.size())), 1, rnd.any(noiseAlphabet));
            t.insert(rnd.next(0, static_cast<int>(t.size())), 1, rnd.any(noiseAlphabet));
        }
    }

    set<string> queries;
    queries.insert(string(1, rnd.any(alphabet)));
    queries.insert(alphabet);

    int maxQueries = min(20, (1 << alphabetSize) - 1);
    int qTarget = rnd.next(1, maxQueries);
    while (static_cast<int>(queries.size()) < qTarget) {
        queries.insert(randomQuery(alphabet, alphabetSize));
    }

    vector<string> queryList(queries.begin(), queries.end());
    shuffle(queryList.begin(), queryList.end());

    println(s);
    println(t);
    println(static_cast<int>(queryList.size()));
    for (const string& query : queryList) {
        println(query);
    }

    return 0;
}
