#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string s;
    int scenario = rnd.next(1, 8);

    if (scenario == 1) {
        // Empty string
        s = "";
    } else if (scenario == 2) {
        // Single repeated letter
        int len = rnd.next(1, 40);
        char c = 'A' + rnd.next(0, 25);
        s.assign(len, c);
    } else if (scenario == 3) {
        // Alphabet in order, exactly once
        s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    } else if (scenario == 4) {
        // Alphabet once, shuffled, plus some random extras
        vector<char> letters;
        for (char c = 'A'; c <= 'Z'; ++c) letters.push_back(c);
        shuffle(letters.begin(), letters.end());
        for (char c : letters) s.push_back(c);
        int extra = rnd.next(0, 20);
        for (int i = 0; i < extra; ++i)
            s.push_back('A' + rnd.next(0, 25));
    } else if (scenario == 5) {
        // Multiple shuffled copies of full alphabet
        int copies = rnd.next(2, 4);
        vector<char> base;
        for (char c = 'A'; c <= 'Z'; ++c) base.push_back(c);
        for (int k = 0; k < copies; ++k) {
            shuffle(base.begin(), base.end());
            for (char c : base) s.push_back(c);
        }
        int extra = rnd.next(0, 10);
        for (int i = 0; i < extra; ++i)
            s.push_back('A' + rnd.next(0, 25));
    } else if (scenario == 6) {
        // Almost pangram: missing exactly one random letter
        char miss = 'A' + rnd.next(0, 25);
        vector<char> pool;
        for (char c = 'A'; c <= 'Z'; ++c) {
            if (c == miss) continue;
            int cnt = rnd.next(1, 3);
            for (int i = 0; i < cnt; ++i) pool.push_back(c);
        }
        shuffle(pool.begin(), pool.end());
        for (char c : pool) s.push_back(c);
    } else if (scenario == 7) {
        // Random subset of letters, no pangram
        vector<char> all;
        for (char c = 'A'; c <= 'Z'; ++c) all.push_back(c);
        shuffle(all.begin(), all.end());
        int k = rnd.next(3, 15);
        vector<char> chosen(all.begin(), all.begin() + k);
        int maxLen = min(120, k * 5);
        int len = rnd.next(k, maxLen);
        for (int i = 0; i < len; ++i)
            s.push_back(rnd.any(chosen));
    } else if (scenario == 8) {
        // Only vowels or only consonants
        if (rnd.next(0, 1) == 0) {
            string vowels = "AEIOU";
            int len = rnd.next(5, 80);
            for (int i = 0; i < len; ++i)
                s.push_back(vowels[rnd.next(0, (int)vowels.size() - 1)]);
        } else {
            string consonants = "BCDFGHJKLMNPQRSTVWXYZ";
            int len = rnd.next(5, 80);
            for (int i = 0; i < len; ++i)
                s.push_back(consonants[rnd.next(0, (int)consonants.size() - 1)]);
        }
    }

    println(s);
    return 0;
}
