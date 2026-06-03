#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

long long distinctAnagramCount(const string& word) {
    array<int, 26> freq{};
    for (char c : word) {
        ++freq[c - 'a'];
    }

    array<__int128_t, 21> fact{};
    fact[0] = 1;
    for (int i = 1; i <= 20; ++i) {
        fact[i] = fact[i - 1] * i;
    }

    __int128_t count = fact[word.size()];
    for (int x : freq) {
        count /= fact[x];
    }
    return static_cast<long long>(count);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound N; use the local default cap for case counts.
    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        setTestCase(i + 1);
        string word = inf.readToken("[a-z]{1,20}", "word");
        inf.readEoln();

        long long anagrams = distinctAnagramCount(word);
        ensuref(anagrams <= 100000,
                "word %d has %lld distinct anagrams, exceeding 100000",
                i + 1,
                anagrams);
    }

    inf.readEof();
}
