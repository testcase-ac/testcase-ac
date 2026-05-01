#include "testlib.h"
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

string randName() {
    static const string chars =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";
    int len = rnd.next(1, 8);
    string s;
    for (int i = 0; i < len; i++)
        s += rnd.any(chars);
    if (s == "ChongChong")
        return randName();
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of meetings
    int N = rnd.next(1, 20);
    // Number of other distinct people (excluding ChongChong)
    int M = rnd.next(1, min(10, N + 1));
    set<string> nameSet;
    nameSet.insert("ChongChong");
    while ((int)nameSet.size() < M + 1) {
        nameSet.insert(randName());
    }
    vector<string> names(nameSet.begin(), nameSet.end());
    // Collect non-ChongChong names
    vector<string> non;
    for (auto &s : names) if (s != "ChongChong") non.push_back(s);

    // Early non-dancer meetings to trip up time-ignorant solutions
    int maxEarly = (int)non.size() * ((int)non.size() - 1) / 2;
    maxEarly = min(maxEarly, N / 2);
    int K = rnd.next(0, maxEarly);
    vector<pair<string, string>> events;
    set<pair<int,int>> usedEarly;
    for (int i = 0; i < K; i++) {
        int u, v;
        do {
            u = rnd.next(0, (int)non.size() - 1);
            v = rnd.next(0, (int)non.size() - 1);
        } while (u == v || usedEarly.count({min(u,v), max(u,v)}));
        usedEarly.insert({min(u,v), max(u,v)});
        events.emplace_back(non[u], non[v]);
    }

    // Chain of propagation to ensure correct dancer spread
    int remSlots = N - K;
    int maxChain = min((int)non.size(), remSlots);
    int L = rnd.next(1, maxChain);
    shuffle(non.begin(), non.end());
    vector<string> chain(non.begin(), non.begin() + L);
    // First link: ChongChong meets chain[0]
    events.emplace_back("ChongChong", chain[0]);
    // Then chain links
    for (int i = 1; i < L; i++) {
        events.emplace_back(chain[i-1], chain[i]);
    }

    // Fill remaining random meetings
    int rest = N - (K + L);
    for (int i = 0; i < rest; i++) {
        int a, b;
        do {
            a = rnd.next(0, (int)names.size() - 1);
            b = rnd.next(0, (int)names.size() - 1);
        } while (a == b);
        events.emplace_back(names[a], names[b]);
    }

    // Shuffle only the tail to preserve early vs chain structure
    if (K + L < (int)events.size()) {
        shuffle(events.begin() + (K + L), events.end());
    }

    // Output
    println(N);
    for (auto &e : events) {
        println(e.first, e.second);
    }

    return 0;
}
