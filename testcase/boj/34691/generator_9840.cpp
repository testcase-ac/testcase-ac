#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> queries;

    int pattern = rnd.next(0, 4);

    if (pattern == 0) {
        // All same word, small N
        int n = rnd.next(1, 10);
        string w = rnd.any(vector<string>{"animal", "tree", "flower"});
        queries.assign(n, w);
    } else if (pattern == 1) {
        // Fully random, medium N
        int n = rnd.next(5, 60);
        vector<string> opts = {"animal", "tree", "flower"};
        queries.resize(n);
        for (int i = 0; i < n; ++i)
            queries[i] = rnd.any(opts);
    } else if (pattern == 2) {
        // Cyclic pattern animal -> tree -> flower
        int n = rnd.next(3, 30);
        vector<string> cycle = {"animal", "tree", "flower"};
        for (int i = 0; i < n; ++i)
            queries.push_back(cycle[i % 3]);
    } else if (pattern == 3) {
        // Skewed distribution: mostly one type
        int n = rnd.next(10, 60);
        vector<string> opts = {"animal", "tree", "flower"};
        string major = rnd.any(opts);
        string other1, other2;
        if (major == "animal") {
            other1 = "tree"; other2 = "flower";
        } else if (major == "tree") {
            other1 = "animal"; other2 = "flower";
        } else {
            other1 = "animal"; other2 = "tree";
        }
        for (int i = 0; i < n; ++i) {
            int r = rnd.next(1, 10); // 1..10
            if (r <= 8) queries.push_back(major);
            else if (r == 9) queries.push_back(other1);
            else queries.push_back(other2);
        }
    } else {
        // Block pattern: several blocks of same word
        int blocks = rnd.next(3, 6);
        string last = "";
        while ((int)queries.size() == 0 && blocks == 0) blocks = 1; // safety
        for (int b = 0; b < blocks; ++b) {
            vector<string> opts = {"animal", "tree", "flower"};
            // choose type different from last if possible
            if (!last.empty()) {
                vector<string> filtered;
                for (auto &s : opts) if (s != last) filtered.push_back(s);
                opts = filtered;
            }
            string t = rnd.any(opts);
            int maxLen = 10;
            int remain = 60 - (int)queries.size();
            if (remain <= 0) break;
            int len = rnd.next(1, min(maxLen, remain));
            for (int i = 0; i < len; ++i) queries.push_back(t);
            last = t;
            if ((int)queries.size() >= 60) break;
        }
        if (queries.empty()) {
            // Fallback if something went wrong
            queries.push_back("animal");
        }
    }

    // Output queries
    for (const string &s : queries)
        println(s);
    // Terminating line
    println("end");

    return 0;
}
