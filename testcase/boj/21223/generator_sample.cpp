#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string makeBaseWord(int bucket, int len) {
    string word;
    for (int i = 0; i < len; ++i) {
        word.push_back(char('a' + (bucket + i * 7) % 26));
    }
    sort(word.begin(), word.end());
    return word;
}

string shuffledVariant(string base) {
    shuffle(base.begin(), base.end());
    return base;
}

void addAnagramBucket(vector<string>& words, set<string>& used, int bucket, int size, int len) {
    string base = makeBaseWord(bucket, len);
    vector<string> variants;

    while ((int)variants.size() < size) {
        string candidate = shuffledVariant(base);
        if (used.insert(candidate).second) {
            variants.push_back(candidate);
        }
    }

    for (const string& word : variants) {
        words.push_back(word);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<string> words;
    set<string> used;

    if (mode == 0) {
        int n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            string word = string(1, char('a' + i % 26));
            if (i >= 26) {
                word.push_back(char('a' + i / 26));
            }
            used.insert(word);
            words.push_back(word);
        }
    } else if (mode == 1) {
        int bucketSize = rnd.next(2, 8);
        addAnagramBucket(words, used, 0, bucketSize, rnd.next(4, 7));
    } else {
        int buckets = rnd.next(2, 8);
        for (int bucket = 0; bucket < buckets; ++bucket) {
            int bucketSize = mode == 2 ? rnd.next(1, 5) : rnd.next(2, 7);
            int len = rnd.next(4, 8);
            addAnagramBucket(words, used, bucket * 3, bucketSize, len);
        }
    }

    shuffle(words.begin(), words.end());

    int maxPairs = 0;
    if (mode == 4) {
        maxPairs = 2000;
    } else {
        maxPairs = rnd.next(0, 2000);
    }
    int k = rnd.next(0, maxPairs);

    println((int)words.size(), k);
    for (const string& word : words) {
        println(word);
    }
}
