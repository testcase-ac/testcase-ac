#include "testlib.h"

#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string randomWord(int minLen, int maxLen) {
    int len = rnd.next(minLen, maxLen);
    string word;
    for (int i = 0; i < len; ++i) {
        word += char('a' + rnd.next(26));
    }
    return word;
}

string joinWords(const vector<string>& words) {
    string name = words[0];
    for (int i = 1; i < int(words.size()); ++i) {
        name += "_";
        name += words[i];
    }
    return name;
}

string makeFillerWord(const string& target) {
    for (int attempt = 0; attempt < 100; ++attempt) {
        string word = randomWord(1, 8);
        if (word != target) {
            return word;
        }
    }
    return target == "a" ? "b" : "a";
}

string makeItemName(const string& target, int mode) {
    if (mode == 0) {
        return target;
    }

    if (mode == 1) {
        vector<string> words;
        int count = rnd.next(2, 5);
        int targetPos = rnd.next(count);
        for (int i = 0; i < count; ++i) {
            words.push_back(i == targetPos ? target : makeFillerWord(target));
        }
        string name = joinWords(words);
        if (name.size() <= 50) {
            return name;
        }
        return rnd.next(2) == 0 ? joinWords({target, makeFillerWord(target)}) : joinWords({makeFillerWord(target), target});
    }

    if (mode == 2 && target.size() <= 48) {
        string name = target + char('a' + rnd.next(26));
        if (name == target) {
            name += 'x';
        }
        return name;
    }

    if (mode == 3 && target.size() <= 48) {
        return string(1, char('a' + rnd.next(26))) + target;
    }

    if (mode == 4) {
        vector<string> words;
        int count = rnd.next(2, 6);
        for (int i = 0; i < count; ++i) {
            words.push_back(makeFillerWord(target));
        }
        string name = joinWords(words);
        if (name.size() <= 50) {
            return name;
        }
    }

    return makeFillerWord(target);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> targetPool = {"a", "birch", "stone", "oak", "log", "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz"};
    string target = rnd.next(4) == 0 ? randomWord(1, 10) : rnd.any(targetPool);
    int n = rnd.next(1, 20);

    set<string> used;
    vector<pair<string, int>> items;
    for (int i = 0; i < n; ++i) {
        string name;
        for (int attempt = 0; attempt < 200; ++attempt) {
            int mode = rnd.next(0, 5);
            name = makeItemName(target, mode);
            if (name.size() <= 50 && used.insert(name).second) {
                break;
            }
            name.clear();
        }
        if (name.empty()) {
            for (char c = 'a'; c <= 'z'; ++c) {
                string candidate(1, c);
                if (candidate != target && used.insert(candidate).second) {
                    name = candidate;
                    break;
                }
            }
        }
        items.push_back({name, rnd.next(1, 64)});
    }

    shuffle(items.begin(), items.end());

    println(n, target);
    for (const auto& item : items) {
        println(item.first, item.second);
    }

    return 0;
}
