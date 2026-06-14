#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

string makeWord(int id) {
    string s;
    do {
        int x = id++;
        s.clear();
        do {
            s.push_back(char('a' + (x % 26)));
            x /= 26;
        } while (x > 0);
    } while (s.size() > 15);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 8) * 2;
    } else if (mode == 2) {
        n = rnd.next(1, 8) * 2 + 1;
    } else {
        n = rnd.next(2, 18);
    }

    vector<string> title;
    set<string> used;
    int base = rnd.next(0, 300);
    for (int i = 0; i < n; ++i) {
        string word = makeWord(base + i * 3 + 1);
        title.push_back(word);
        used.insert(word);
    }
    shuffle(title.begin(), title.end());

    vector<string> noise;
    for (int i = 0; i < 40; ++i) {
        string word;
        do {
            word = makeWord(1000 + base + i * 7 + rnd.next(0, 4));
        } while (used.count(word));
        noise.push_back(word);
        used.insert(word);
    }

    int need = (n + 1) / 2;
    int before = (mode == 0 ? 0 : rnd.next(0, 12));
    int repeatedKnown = rnd.next(0, min(need - 1, 3));
    vector<string> lyrics;

    for (int i = 0; i < before; ++i) {
        if (!lyrics.empty() && repeatedKnown > 0 && rnd.next(0, 2) == 0) {
            lyrics.push_back(title[rnd.next(0, repeatedKnown - 1)]);
        } else {
            lyrics.push_back(rnd.any(noise));
        }
    }

    for (int i = 0; i < repeatedKnown; ++i) {
        lyrics.push_back(title[i]);
        if (rnd.next(0, 1) == 0) {
            lyrics.push_back(title[i]);
        }
    }

    for (int i = repeatedKnown; i + 1 < need; ++i) {
        lyrics.push_back(rnd.any(noise));
        lyrics.push_back(title[i]);
    }

    if (mode == 3) {
        for (int i = 0; i < rnd.next(3, 20); ++i) {
            lyrics.push_back(rnd.any(noise));
        }
    }

    lyrics.push_back(title[need - 1]);

    int tail = rnd.next(0, 12);
    for (int i = 0; i < tail; ++i) {
        if (rnd.next(0, 3) == 0) {
            lyrics.push_back(title[rnd.next(0, n - 1)]);
        } else {
            lyrics.push_back(rnd.any(noise));
        }
    }

    println(n);
    for (const string& word : title) {
        println(word);
    }
    println(static_cast<int>(lyrics.size()));
    for (const string& word : lyrics) {
        println(word);
    }

    return 0;
}
