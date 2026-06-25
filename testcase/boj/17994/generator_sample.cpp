#include "testlib.h"
#include <algorithm>
#include <set>
#include <string>
#include <vector>
using namespace std;

string makeAlphabet(int k) {
    string letters;
    for (int i = 0; i < k; ++i) {
        letters.push_back(char('a' + i));
    }
    return letters;
}

void addWord(vector<string>& words, set<string>& seen, const string& word) {
    if (seen.insert(word).second) {
        words.push_back(word);
    }
}

string randomPermutation(string letters) {
    shuffle(letters.begin(), letters.end());
    return letters;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k = 1;
    int target = 1;

    if (mode == 0) {
        k = 1;
        target = 1;
    } else if (mode == 1) {
        k = rnd.next(2, 5);
        target = rnd.next(1, min(10, k * (k - 1) / 2 + 1));
    } else if (mode == 2) {
        k = rnd.next(3, 6);
        target = rnd.next(k, min(40, k * (k - 1) / 2 + k));
    } else if (mode == 3) {
        k = rnd.next(3, 6);
        target = rnd.next(1, min(120, 500));
    } else if (mode == 4) {
        k = rnd.next(6, 8);
        target = rnd.next(20, 120);
    } else {
        k = rnd.next(8, 12);
        target = rnd.next(50, 200);
    }

    string base = makeAlphabet(k);
    vector<string> words;
    set<string> seen;

    if (mode == 0) {
        addWord(words, seen, base);
    } else if (mode == 1) {
        addWord(words, seen, base);
        vector<pair<int, int> > swaps;
        for (int i = 0; i < k; ++i) {
            for (int j = i + 1; j < k; ++j) {
                swaps.push_back(make_pair(i, j));
            }
        }
        shuffle(swaps.begin(), swaps.end());
        for (int i = 0; i < int(swaps.size()) && int(words.size()) < target; ++i) {
            string word = base;
            swap(word[swaps[i].first], word[swaps[i].second]);
            addWord(words, seen, word);
        }
    } else if (mode == 2) {
        addWord(words, seen, base);
        for (int center = 0; center < k && int(words.size()) < target; ++center) {
            vector<int> positions;
            for (int i = 0; i < k; ++i) {
                if (i != center) {
                    positions.push_back(i);
                }
            }
            shuffle(positions.begin(), positions.end());
            for (int pos : positions) {
                string word = base;
                swap(word[center], word[pos]);
                addWord(words, seen, word);
                if (int(words.size()) >= target) {
                    break;
                }
            }
        }
    } else if (mode == 3) {
        string word = base;
        do {
            addWord(words, seen, word);
            if (int(words.size()) >= target) {
                break;
            }
        } while (next_permutation(word.begin(), word.end()));
    } else {
        int attempts = 0;
        int maxAttempts = target * 80;
        while (int(words.size()) < target && attempts < maxAttempts) {
            addWord(words, seen, randomPermutation(base));
            ++attempts;
        }
    }

    shuffle(words.begin(), words.end());

    println(int(words.size()));
    for (const string& word : words) {
        println(word);
    }

    return 0;
}
