#include "testlib.h"
#include <algorithm>
#include <array>
#include <string>
#include <vector>
using namespace std;

long long distinctAnagramCount(const string& word) {
    array<int, 26> freq{};
    for (char c : word) ++freq[c - 'a'];

    array<__int128_t, 21> fact{};
    fact[0] = 1;
    for (int i = 1; i <= 20; ++i) fact[i] = fact[i - 1] * i;

    __int128_t count = fact[word.size()];
    for (int x : freq) count /= fact[x];
    return static_cast<long long>(count);
}

string shuffledWord(vector<pair<char, int>> counts) {
    string word;
    for (auto [ch, cnt] : counts) word += string(cnt, ch);
    shuffle(word.begin(), word.end());
    return word;
}

string randomSmallWord() {
    int len = rnd.next(1, 8);
    int alphabet = rnd.next(1, min(6, len));
    string word;
    for (int i = 0; i < len; ++i) word += char('a' + rnd.next(alphabet));
    return word;
}

string randomRepeatedLongWord() {
    int len = rnd.next(12, 20);
    int alphabet = rnd.next(1, 4);
    vector<pair<char, int>> counts;
    int remaining = len;
    for (int i = 0; i < alphabet; ++i) {
        int cnt = (i + 1 == alphabet) ? remaining : rnd.next(1, remaining - (alphabet - i - 1));
        counts.push_back({char('a' + i), cnt});
        remaining -= cnt;
    }
    return shuffledWord(counts);
}

string randomPatternWord() {
    vector<vector<int>> patterns = {
        {2, 2, 2, 2, 2},
        {3, 3, 3, 3},
        {4, 4, 4, 4, 4},
        {6, 5, 4, 3, 2},
        {10, 5, 3, 2},
        {12, 4, 2, 1, 1},
        {16, 1, 1, 1, 1},
    };
    vector<int> pattern = rnd.any(patterns);
    int offset = rnd.next(0, 26 - int(pattern.size()));
    vector<pair<char, int>> counts;
    for (int i = 0; i < int(pattern.size()); ++i) counts.push_back({char('a' + offset + i), pattern[i]});
    return shuffledWord(counts);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(6, 18);
    vector<string> words;

    while (int(words.size()) < n) {
        string word;
        int mode = rnd.next(0, 5);
        if (mode <= 1) {
            word = randomSmallWord();
        } else if (mode <= 3) {
            word = randomRepeatedLongWord();
        } else {
            word = randomPatternWord();
        }

        if (distinctAnagramCount(word) <= 100000) words.push_back(word);
    }

    println(n);
    for (const string& word : words) println(word);
    return 0;
}
