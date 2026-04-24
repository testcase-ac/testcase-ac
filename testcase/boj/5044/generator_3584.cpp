#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

string random_format(const string &s) {
    string res;
    // leading spaces
    int ls = rnd.next(0, 2);
    res.append(ls, ' ');
    // core content with random case and spaces
    for (char c : s) {
        if (c == ' ') {
            int cnt = rnd.next(1, 2);
            res.append(cnt, ' ');
        } else if (isalpha(c)) {
            char d = rnd.next(0, 1) ? toupper(c) : tolower(c);
            res.push_back(d);
        } else {
            res.push_back(c);
        }
    }
    // trailing spaces
    int ts = rnd.next(0, 2);
    res.append(ts, ' ');
    return res;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // A small pool of possible code lines (including blank)
    vector<string> pool = {
        "",  // empty line
        "int a = 0;",
        "return 0;",
        "for(i = 0; i < n; i++){",
        "printf(\"Hello\\n\");",
        "if(x > 0){",
        "}",
        "else{",
        "x++;",
        "y--;",
        "// comment"
    };

    // Number of repository files
    int N = rnd.next(1, 3);
    // Choose which files will share a matching segment
    int K = rnd.next(1, min(2, N));
    vector<int> all_idx(N);
    iota(all_idx.begin(), all_idx.end(), 0);
    shuffle(all_idx.begin(), all_idx.end());
    vector<int> match_idx(all_idx.begin(), all_idx.begin() + K);

    // Generate segments for matched files
    map<int, vector<string>> segments;
    for (int idx : match_idx) {
        int len = rnd.next(2, 3);
        vector<string> seg;
        for (int i = 0; i < len; i++) {
            // pick a non-empty pool line
            string line;
            do {
                line = rnd.any(pool);
            } while (line.empty());
            seg.push_back(line);
        }
        segments[idx] = seg;
    }

    // Build repository files
    vector<vector<string>> repos(N);
    vector<string> names(N);
    for (int i = 0; i < N; i++) {
        names[i] = "File" + to_string(i+1) + ".c";
        if (segments.count(i)) {
            // this repo has a matching segment
            auto &seg = segments[i];
            int pre = rnd.next(0, 3);
            int post = rnd.next(0, 3);
            // pre
            for (int j = 0; j < pre; j++)
                repos[i].push_back(random_format(rnd.any(pool)));
            // segment
            for (auto &ln : seg)
                repos[i].push_back(random_format(ln));
            // post
            for (int j = 0; j < post; j++)
                repos[i].push_back(random_format(rnd.any(pool)));
        } else {
            // totally random content
            int L = rnd.next(2, 5);
            for (int j = 0; j < L; j++)
                repos[i].push_back(random_format(rnd.any(pool)));
        }
    }

    // Build target source
    vector<string> target;
    int pre_t = rnd.next(0, 3), post_t = rnd.next(0, 3);
    // pre
    for (int i = 0; i < pre_t; i++)
        target.push_back(random_format(rnd.any(pool)));
    // embed segments in random order with small separators
    shuffle(match_idx.begin(), match_idx.end());
    for (int idx : match_idx) {
        auto &seg = segments[idx];
        for (auto &ln : seg)
            target.push_back(random_format(ln));
        int sep = rnd.next(0, 2);
        for (int k = 0; k < sep; k++)
            target.push_back(random_format(rnd.any(pool)));
    }
    // post
    for (int i = 0; i < post_t; i++)
        target.push_back(random_format(rnd.any(pool)));

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        println(names[i]);
        for (auto &ln : repos[i])
            println(ln);
        println("***END***");
    }
    for (auto &ln : target)
        println(ln);
    println("***END***");

    return 0;
}
