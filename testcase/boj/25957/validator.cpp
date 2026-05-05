#include "testlib.h"
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

// Helper function to check if two words are "scrambled" as per the problem's definition
bool is_scrambled(const string& orig, const string& scrambled) {
    if (orig.size() != scrambled.size()) return false;
    if (orig.size() == 1) return orig == scrambled;
    if (orig.front() != scrambled.front()) return false;
    if (orig.back() != scrambled.back()) return false;
    if (orig.size() == 2) return orig == scrambled;
    // Check if the middle letters are a permutation
    string mid_orig = orig.substr(1, orig.size() - 2);
    string mid_scrambled = scrambled.substr(1, scrambled.size() - 2);
    sort(mid_orig.begin(), mid_orig.end());
    sort(mid_scrambled.begin(), mid_scrambled.end());
    return mid_orig == mid_scrambled;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // 2. Read N words, check constraints
    set<string> orig_words_set;
    vector<string> orig_words;
    for (int i = 0; i < N; ++i) {
        string word = inf.readToken("[^ ]{1,8}", "word");
        inf.readEoln();

        // Check for only valid unicode characters? (Problem does not specify, so we only check length and no spaces)
        ensuref(orig_words_set.insert(word).second, "Duplicate word detected at line %d: '%s'", i+2, word.c_str());
        orig_words.push_back(word);
    }

    // 3. For all pairs, ensure that no two words differ only by permutation of middle letters
    // (i.e., for any two words, if first and last letter are same and sorted(middle) is same, they must be the same word)
    // Since N is large, we use a map for this check
    map<tuple<char, char, int, string>, string> word_signature;
    for (const string& word : orig_words) {
        char first = word.front();
        char last = word.back();
        int len = word.size();
        string mid = (len > 2) ? word.substr(1, len-2) : "";
        if (!mid.empty()) sort(mid.begin(), mid.end());
        auto key = make_tuple(first, last, len, mid);
        auto it = word_signature.find(key);
        ensuref(it == word_signature.end() || it->second == word,
            "Two words differ only by permutation of middle letters: '%s' and '%s'", word.c_str(), it->second.c_str());
        word_signature[key] = word;
    }

    // 4. Read M
    int M = inf.readInt(1, 200000, "M");
    inf.readEoln();

    // 5. Read M scrambled words (space separated, single line)
    vector<string> scrambled_words = inf.readTokens(M, "[^ ]{1,8}", "scrambled_word");
    inf.readEoln();

    // 6. For each scrambled word, ensure that it matches exactly one original word by the scrambling rule
    // Build a lookup for scrambled word signature -> original word
    map<tuple<char, char, int, string>, string> sig_to_orig;
    for (const string& word : orig_words) {
        char first = word.front();
        char last = word.back();
        int len = word.size();
        string mid = (len > 2) ? word.substr(1, len-2) : "";
        if (!mid.empty()) sort(mid.begin(), mid.end());
        auto key = make_tuple(first, last, len, mid);
        sig_to_orig[key] = word;
    }

    for (int i = 0; i < M; ++i) {
        const string& sw = scrambled_words[i];
        int len = sw.size();
        ensuref(1 <= len && len <= 8, "Scrambled word at index %d has invalid length: '%s'", i, sw.c_str());
        char first = sw.front();
        char last = sw.back();
        string mid = (len > 2) ? sw.substr(1, len-2) : "";
        if (!mid.empty()) sort(mid.begin(), mid.end());
        auto key = make_tuple(first, last, len, mid);
        ensuref(sig_to_orig.count(key), "Scrambled word at index %d ('%s') does not correspond to any original word", i, sw.c_str());
        // Additionally, check that sw is a valid permutation of the original word (not just signature)
        const string& orig = sig_to_orig[key];
        ensuref(is_scrambled(orig, sw), "Scrambled word at index %d ('%s') is not a valid scramble of '%s'", i, sw.c_str(), orig.c_str());
    }

    inf.readEof();
}
