#include "testlib.h"
using namespace std;

struct PreCase {
    string s;
    vector<string> words;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 2); // 0: constructed from dict, 1: random independent, 2: predefined

    string S;
    vector<string> dict;

    if (scenario == 2) {
        // Predefined interesting cases (from samples)
        vector<PreCase> cases;

        cases.push_back({"neotowheret",
                         {"one", "two", "three", "there"}});
        cases.push_back({"abba",
                         {"ab", "ac", "ad"}});
        cases.push_back({"thisismeaningless",
                         {"this", "is", "meaningful"}});
        cases.push_back({"ommwreehisymkiml",
                         {"we", "were", "here", "my", "is", "mom", "here", "si", "milk", "where", "si"}});
        cases.push_back({"ogodtsneeencs",
                         {"go", "good", "do", "sentences", "tense", "scen"}});
        cases.push_back({"sepawaterords",
                         {"separate", "words"}});

        PreCase &c = cases[rnd.next(0, (int)cases.size() - 1)];
        S = c.s;
        dict = c.words;
    } else if (scenario == 0) {
        // Sentence constructed as concatenation of permuted dictionary words (guaranteed decodable)
        int alphaSize = rnd.next(3, 6);
        string alph;
        for (int i = 0; i < alphaSize; ++i)
            alph += char('a' + i);

        int N = rnd.next(1, 10);
        dict.resize(N);

        for (int i = 0; i < N; ++i) {
            int len = rnd.next(1, 8);
            string w;
            for (int j = 0; j < len; ++j)
                w += rnd.any(alph);
            dict[i] = w;
        }

        int K = rnd.next(1, 8);
        S.clear();
        for (int i = 0; i < K; ++i) {
            string base = rnd.any(dict);
            string perm = base;
            if (rnd.next() < 0.6) { // often permute to create cost
                string tmp = perm;
                for (int attempt = 0; attempt < 5; ++attempt) {
                    shuffle(tmp.begin(), tmp.end());
                    if (tmp != base) break;
                }
                perm = tmp;
            }
            if (S.size() + perm.size() > 50)
                break;
            S += perm;
        }
        if (S.empty()) {
            // Fallback: use first word (always length <= 8)
            S = dict[0];
        }
    } else {
        // scenario == 1: Completely random sentence and nearly independent dictionary
        int alphaSize = rnd.next(3, 6);
        string alph;
        for (int i = 0; i < alphaSize; ++i)
            alph += char('a' + i);

        int lenS = rnd.next(1, 40);
        S.clear();
        for (int i = 0; i < lenS; ++i)
            S += rnd.any(alph);

        int N = rnd.next(1, 12);
        dict.clear();
        dict.reserve(N);
        for (int i = 0; i < N; ++i) {
            int len = rnd.next(1, 10);
            string w;
            if (rnd.next() < 0.35 && (int)S.size() >= len) {
                // Sometimes take a substring of S to increase chances of partial matches
                int start = rnd.next(0, (int)S.size() - len);
                w = S.substr(start, len);
            } else {
                for (int j = 0; j < len; ++j)
                    w += rnd.any(alph);
            }
            dict.push_back(w);
        }
    }

    // Output
    println(S);
    println((int)dict.size());
    for (const string &w : dict)
        println(w);

    return 0;
}
