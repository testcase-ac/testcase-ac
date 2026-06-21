#include "testlib.h"

#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int alphabetSize = rnd.next(2, 8);
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    shuffle(alphabet.begin(), alphabet.end());
    alphabet.resize(alphabetSize);

    int n = rnd.next(2, mode == 5 ? 120 : 45);
    string t;
    t.reserve(n);

    if (mode == 0) {
        char a = alphabet[0], b = alphabet[1];
        for (int i = 0; i < n; ++i) t.push_back(i % 2 == 0 ? a : b);
    } else if (mode == 1) {
        char a = alphabet[0];
        char b = alphabet[1];
        char c = alphabet[rnd.next(0, alphabetSize - 1)];
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(0, 9);
            t.push_back(pick < 5 ? a : (pick < 8 ? b : c));
        }
    } else if (mode == 2) {
        string pattern;
        int len = rnd.next(2, min(8, alphabetSize + 2));
        for (int i = 0; i < len; ++i) pattern.push_back(alphabet[i % alphabetSize]);
        shuffle(pattern.begin(), pattern.end());
        for (int i = 0; i < n; ++i) t.push_back(pattern[i % len]);
    } else {
        for (int i = 0; i < n; ++i) t.push_back(alphabet[rnd.next(0, alphabetSize - 1)]);
    }

    set<pair<char, char>> seenInT;
    for (int i = 0; i + 1 < n; ++i) {
        seenInT.insert({t[i], t[i + 1]});
    }

    vector<pair<char, char>> allEdges;
    for (char a = 'a'; a <= 'z'; ++a) {
        for (char b = 'a'; b <= 'z'; ++b) {
            allEdges.push_back({a, b});
        }
    }
    shuffle(allEdges.begin(), allEdges.end());

    set<pair<char, char>> edges;
    if (mode <= 2) {
        edges = seenInT;
    } else if (mode == 3) {
        vector<pair<char, char>> present(seenInT.begin(), seenInT.end());
        shuffle(present.begin(), present.end());
        int take = rnd.next(1, max(1, (int)present.size()));
        for (int i = 0; i < take; ++i) edges.insert(present[i]);
    } else if (mode == 4) {
        edges = seenInT;
        int extras = rnd.next(1, 8);
        for (auto edge : allEdges) {
            if ((int)edges.size() >= (int)seenInT.size() + extras) break;
            edges.insert(edge);
        }
    } else {
        int m = rnd.next(1, min(60, 26 * 26));
        for (auto edge : allEdges) {
            edges.insert(edge);
            if ((int)edges.size() == m) break;
        }
    }

    if (edges.empty()) {
        edges.insert({t[0], t[1]});
    }

    vector<pair<char, char>> outputEdges(edges.begin(), edges.end());
    shuffle(outputEdges.begin(), outputEdges.end());

    println(n);
    println(t);
    println((int)outputEdges.size());
    for (auto edge : outputEdges) {
        string s;
        s.push_back(edge.first);
        s.push_back(edge.second);
        println(s);
    }

    return 0;
}
