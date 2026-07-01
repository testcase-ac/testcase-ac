#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

const string ALPHABET = "pinkhare";

string randomCode(int len) {
    string s;
    for (int i = 0; i < len; ++i) {
        s += rnd.any(ALPHABET);
    }
    return s;
}

string repeatToLength(const string& pattern, int len) {
    string s;
    while ((int)s.size() < len) {
        s += pattern;
    }
    s.resize(len);
    return s;
}

vector<string> windowsOf(const string& chromosome) {
    set<string> uniqueWindows;
    for (int i = 0; i + 10 <= (int)chromosome.size(); ++i) {
        uniqueWindows.insert(chromosome.substr(i, 10));
    }
    return vector<string>(uniqueWindows.begin(), uniqueWindows.end());
}

string makeChromosome(int mode) {
    if (mode == 0) {
        return randomCode(44);
    }
    if (mode == 1) {
        string pattern = randomCode(rnd.next(1, 8));
        return repeatToLength(pattern, 44);
    }
    if (mode == 2) {
        string base = randomCode(10);
        string filler = randomCode(7);
        return repeatToLength(base + filler, 44);
    }

    string motif = rnd.any(vector<string>{"pinkhare", "harepink", "kkkkpppp", "iiiiiiii"});
    return repeatToLength(motif, 44);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 4);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int q = rnd.next(2, 30);
        println(q);

        vector<string> seenWindows;
        vector<string> commands;

        for (int i = 0; i < q; ++i) {
            bool shouldAdd = seenWindows.empty() || rnd.next(100) < 45;
            if (shouldAdd) {
                string chromosome = makeChromosome(rnd.next(0, 3));
                commands.push_back(chromosome);

                vector<string> windows = windowsOf(chromosome);
                seenWindows.insert(seenWindows.end(), windows.begin(), windows.end());
            } else {
                int queryMode = rnd.next(100);
                if (queryMode < 65 && !seenWindows.empty()) {
                    commands.push_back(rnd.any(seenWindows));
                } else if (queryMode < 85) {
                    commands.push_back(repeatToLength(string(1, rnd.any(ALPHABET)), 10));
                } else {
                    commands.push_back(randomCode(10));
                }
            }
        }

        for (const string& command : commands) {
            println(command);
        }
    }

    return 0;
}
