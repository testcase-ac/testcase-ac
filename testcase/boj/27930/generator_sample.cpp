#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

int firstCompletionIndex(const string& s, const string& target) {
    int matched = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (matched < (int)target.size() && s[i] == target[matched]) {
            ++matched;
            if (matched == (int)target.size()) {
                return i;
            }
        }
    }
    return -1;
}

bool valid(const string& s) {
    int yonsei = firstCompletionIndex(s, "YONSEI");
    int korea = firstCompletionIndex(s, "KOREA");
    return (yonsei != -1 || korea != -1) &&
           (yonsei == -1 || korea == -1 || yonsei != korea);
}

string forcedSubsequenceCase(int n, const string& target) {
    string s(n, 'A');
    for (char& c : s) {
        c = char('A' + rnd.next(26));
    }

    vector<int> cuts;
    for (int i = 0; i < n; ++i) {
        cuts.push_back(i);
    }
    shuffle(cuts.begin(), cuts.end());
    cuts.resize(target.size());
    sort(cuts.begin(), cuts.end());

    for (int i = 0; i < (int)target.size(); ++i) {
        s[cuts[i]] = target[i];
    }
    return s;
}

string noisyDirectCase(const string& target) {
    string s;
    for (char c : target) {
        int noise = rnd.next(0, 4);
        while (noise--) {
            s += char('A' + rnd.next(26));
        }
        s += c;
    }
    int suffix = rnd.next(0, 8);
    while (suffix--) {
        s += char('A' + rnd.next(26));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> targets = {"YONSEI", "KOREA"};

    for (int attempt = 0; attempt < 10000; ++attempt) {
        string target = rnd.any(targets);
        string s;
        int mode = rnd.next(4);

        if (mode == 0) {
            s = noisyDirectCase(target);
        } else {
            int n;
            if (mode == 1) {
                n = rnd.next((int)target.size(), 20);
            } else if (mode == 2) {
                n = rnd.next(21, 80);
            } else {
                n = rnd.next(81, 500);
            }
            s = forcedSubsequenceCase(n, target);
        }

        if ((int)s.size() >= 5 && valid(s)) {
            println(s);
            return 0;
        }
    }

    println("YONSEI");
    return 0;
}
