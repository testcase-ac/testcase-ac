#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

string makeVariant(const string &orig) {
    int t = rnd.next(0, 2);
    if (t == 0) {
        // as listed
        return orig;
    } else if (t == 1) {
        // uppercase
        string s = orig;
        for (char &c : s)
            if (isalpha(c)) c = toupper(c);
        return s;
    } else {
        // capitalized
        string s = orig;
        if (!s.empty() && isalpha(s[0]))
            s[0] = toupper(s[0]);
        return s;
    }
}

string joinWords(const vector<string> &ws) {
    string s;
    for (size_t i = 0; i < ws.size(); i++) {
        if (i) s += ' ';
        s += ws[i];
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // pools of possible contractions and acronyms
    vector<pair<string,string>> poolCon = {
        {"doesn't","does not"},
        {"isn't","is not"},
        {"can't","cannot"},
        {"I'm","I am"},
        {"they're","they are"},
        {"we'll","we will"},
        {"you're","you are"},
        {"o'clock","of the clock"}
    };
    vector<pair<string,string>> poolAcr = {
        {"ACM","Association for Computing Machinery"},
        {"CS","Computing Science"},
        {"NASA","National Aeronautics and Space Administration"},
        {"radar","radio detecting and ranging"},
        {"CPU","Central Processing Unit"},
        {"RAM","Random Access Memory"}
    };

    // choose counts
    int C = rnd.next(1, min(5, (int)poolCon.size()));
    int A = rnd.next(1, min(5, (int)poolAcr.size()));
    shuffle(poolCon.begin(), poolCon.end());
    shuffle(poolAcr.begin(), poolAcr.end());
    vector<pair<string,string>> cons(poolCon.begin(), poolCon.begin()+C);
    vector<pair<string,string>> acrs(poolAcr.begin(), poolAcr.begin()+A);

    // output C and A
    println(C, A);
    for (auto &p : cons) {
        println("\"" + p.first + "\"", "->", "\"" + p.second + "\"");
    }
    for (auto &p : acrs) {
        println("\"" + p.first + "\"", "->", "\"" + p.second + "\"");
    }

    // how many texts
    int T = rnd.next(1, 3);
    vector<vector<string>> texts(T);

    // filler words
    vector<string> fillers = {
        "the","and","of","in","to","for","with","at","its","it",
        "on","this","that","though","many","large","small","magic",
        "resources","part","science","thank","you","suggestions",
        "signed","will","use","not","have","do","are","am"
    };

    // generate base texts
    for (int t = 0; t < T; t++) {
        int L = rnd.next(1, 5);
        for (int l = 0; l < L; l++) {
            int W = rnd.next(3, 7);
            vector<string> words;
            for (int w = 0; w < W; w++) {
                int p = rnd.next(0, 99);
                if (p < 15 && !cons.empty()) {
                    auto &pr = cons[rnd.next(0, (int)cons.size() - 1)];
                    words.push_back(makeVariant(pr.first));
                } else if (p < 25 && !acrs.empty()) {
                    auto &pr = acrs[rnd.next(0, (int)acrs.size() - 1)];
                    words.push_back(pr.first);
                } else {
                    words.push_back(rnd.any(fillers));
                }
            }
            // ensure line <=80 by trimming words
            while (!words.empty()) {
                string line = joinWords(words);
                if ((int)line.size() <= 80) break;
                words.pop_back();
            }
            if (words.empty()) {
                // fallback to a single small filler
                words.push_back(rnd.any(fillers));
            }
            texts[t].push_back(joinWords(words));
        }
    }

    // ensure at least one occurrence of each contraction
    for (int i = 0; i < C; i++) {
        string var = makeVariant(cons[i].first);
        int ti = rnd.next(0, T-1);
        bool placed = false;
        for (int l = 0; l < (int)texts[ti].size(); l++) {
            if ((int)texts[ti][l].size() + 1 + (int)var.size() <= 80) {
                texts[ti][l] += " " + var;
                placed = true;
                break;
            }
        }
        if (!placed) {
            texts[ti].push_back(var);
        }
    }
    // ensure at least one occurrence of each acronym
    for (int i = 0; i < A; i++) {
        string acr = acrs[i].first;
        int ti = rnd.next(0, T-1);
        bool placed = false;
        for (int l = 0; l < (int)texts[ti].size(); l++) {
            if ((int)texts[ti][l].size() + 1 + (int)acr.size() <= 80) {
                texts[ti][l] += " " + acr;
                placed = true;
                break;
            }
        }
        if (!placed) {
            texts[ti].push_back(acr);
        }
    }

    // output texts
    for (int t = 0; t < T; t++) {
        for (auto &line : texts[t]) {
            println(line);
        }
        println("#");
    }
    return 0;
}
