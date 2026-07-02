#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomSuffix(int length) {
    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i) {
        s.push_back(static_cast<char>('a' + rnd.next(0, 25)));
    }
    return s;
}

string buildWord(const string& prefix, int totalLength) {
    return prefix + randomSuffix(totalLength - static_cast<int>(prefix.size()));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = 2 * rnd.next(1, 12);
    int length = rnd.next(1, 12);
    vector<string> words;
    words.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n / 2; ++i) {
            string word = randomSuffix(length);
            words.push_back(word);
            words.push_back(word);
        }
    } else if (mode == 1) {
        int prefixLength = rnd.next(0, length);
        string common = randomSuffix(prefixLength);
        for (int i = 0; i < n; ++i) {
            words.push_back(buildWord(common, length));
        }
    } else if (mode == 2) {
        int clusterCount = rnd.next(1, min(6, n / 2));
        vector<string> prefixes;
        for (int i = 0; i < clusterCount; ++i) {
            int prefixLength = rnd.next(0, length);
            prefixes.push_back(randomSuffix(prefixLength));
        }
        for (int i = 0; i < n; ++i) {
            const string& prefix = prefixes[i % clusterCount];
            words.push_back(buildWord(prefix, length));
        }
    } else if (mode == 3) {
        string base = randomSuffix(length);
        words.push_back(base);
        words.push_back(base);
        for (int i = 2; i < n; ++i) {
            int prefixLength = rnd.next(0, length);
            words.push_back(buildWord(base.substr(0, prefixLength), length));
        }
    } else {
        length = rnd.next(8, 20);
        n = 2 * rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int prefixLength = rnd.wnext(length + 1, -2);
            words.push_back(buildWord(randomSuffix(prefixLength), length));
        }
    }

    shuffle(words.begin(), words.end());

    println(static_cast<int>(words.size()));
    for (const string& word : words) {
        println(word);
    }

    return 0;
}
