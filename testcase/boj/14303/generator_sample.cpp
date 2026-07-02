#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string shuffledWord(string word) {
    shuffle(word.begin(), word.end());
    return word;
}

string makeWord(int index) {
    string word;
    int value = index;
    do {
        word.push_back(static_cast<char>('a' + value % 26));
        value /= 26;
    } while (value > 0);
    return word;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 3);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int V = rnd.next(200, 230);
        int S = rnd.next(1, 5);
        println(V, S);

        vector<string> words = {
            "ab", "ba", "abc", "acb", "bca", "aabb", "abab", "baba",
            "code", "coed", "deco", "jam", "maj", "cipher", "reciph"
        };
        set<string> used(words.begin(), words.end());

        for (int i = 0; static_cast<int>(words.size()) < V; ++i) {
            string word = makeWord(i);
            if (used.insert(word).second) {
                words.push_back(word);
            }
        }

        shuffle(words.begin(), words.end());
        for (const string& word : words) {
            println(word);
        }

        for (int query = 0; query < S; ++query) {
            int pieces = rnd.next(1, 12);
            int mode = rnd.next(0, 3);
            string encrypted;

            for (int i = 0; i < pieces; ++i) {
                string word;
                if (mode == 0) {
                    word = words[rnd.next(0, min(V - 1, 25))];
                } else if (mode == 1) {
                    static const vector<string> collisionWords = {
                        "ab", "ba", "abc", "acb", "bca", "aabb", "abab", "baba"
                    };
                    word = rnd.any(collisionWords);
                } else if (mode == 2) {
                    word = words[rnd.next(0, V - 1)];
                } else {
                    word = words[(query + i) % V];
                }
                encrypted += shuffledWord(word);
            }

            println(encrypted);
        }
    }

    return 0;
}
