#include "testlib.h"

#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string word(char prefix, int index) {
    string result(1, prefix);
    result += char('A' + index / 26);
    result += char('A' + index % 26);
    return result;
}

void addTopic(vector<pair<string, string>>& topics, set<pair<string, string>>& seen, const string& first, const string& second) {
    if (seen.insert({first, second}).second) {
        topics.push_back({first, second});
    }
}

vector<pair<string, string>> makeGridCase(int rows, int cols, int keep) {
    vector<pair<string, string>> topics;
    set<pair<string, string>> seen;

    vector<string> firsts;
    vector<string> seconds;
    for (int i = 0; i < rows; ++i) firsts.push_back(word('F', i));
    for (int i = 0; i < cols; ++i) seconds.push_back(word('S', i));

    for (const string& first : firsts) {
        for (const string& second : seconds) {
            addTopic(topics, seen, first, second);
        }
    }
    shuffle(topics.begin(), topics.end());
    topics.resize(keep);
    shuffle(topics.begin(), topics.end());
    return topics;
}

vector<pair<string, string>> makeSparseCase(int n) {
    vector<pair<string, string>> topics;
    set<pair<string, string>> seen;

    for (int i = 0; i < n; ++i) {
        string first = (i % 3 == 0 && i > 0) ? word('F', rnd.next(i)) : word('A', i);
        string second = (i % 4 == 0 && i > 0) ? word('S', rnd.next(i)) : word('B', i);
        addTopic(topics, seen, first, second);
    }

    int filler = 0;
    while ((int)topics.size() < n) {
        addTopic(topics, seen, word('C', filler), word('D', filler + 7));
        ++filler;
    }
    shuffle(topics.begin(), topics.end());
    return topics;
}

vector<pair<string, string>> makeMixedCase(int n) {
    vector<pair<string, string>> topics;
    set<pair<string, string>> seen;

    vector<string> firsts = {"ALPHA", "BETA", "GAMMA", "DELTA", "EPSILON"};
    vector<string> seconds = {"ONE", "TWO", "THREE", "FOUR", "FIVE"};

    addTopic(topics, seen, firsts[0], seconds[0]);
    addTopic(topics, seen, firsts[1], seconds[1]);
    addTopic(topics, seen, firsts[0], seconds[1]);
    addTopic(topics, seen, firsts[1], seconds[0]);

    while ((int)topics.size() < n) {
        int mode = rnd.next(0, 2);
        string first = mode == 0 ? rnd.any(firsts) : word('P', rnd.next(40));
        string second = mode == 1 ? rnd.any(seconds) : word('Q', rnd.next(40));
        addTopic(topics, seen, first, second);
    }
    shuffle(topics.begin(), topics.end());
    return topics;
}

vector<pair<string, string>> makeLongWordCase() {
    vector<pair<string, string>> topics;
    set<pair<string, string>> seen;
    string first = "ABCDEFGHIJKLMNOPQRST";
    string second = "QRSTUVWXYZABCDEFGHIJ";
    addTopic(topics, seen, first, "X");
    addTopic(topics, seen, "Y", second);
    addTopic(topics, seen, first, second);
    shuffle(topics.begin(), topics.end());
    return topics;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        vector<pair<string, string>> topics;
        int mode = tc < 4 ? tc : rnd.next(0, 3);

        if (mode == 0) {
            int rows = rnd.next(2, 4);
            int cols = rnd.next(2, 4);
            int keep = rnd.next(1, rows * cols);
            topics = makeGridCase(rows, cols, keep);
        } else if (mode == 1) {
            topics = makeSparseCase(rnd.next(1, 16));
        } else if (mode == 2) {
            topics = makeMixedCase(rnd.next(4, 16));
        } else {
            topics = makeLongWordCase();
        }

        println((int)topics.size());
        for (const auto& topic : topics) {
            println(topic.first, topic.second);
        }
    }

    return 0;
}
