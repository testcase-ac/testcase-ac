#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of premises
    int n = rnd.next(2, 26);
    // Prepare letters
    vector<char> letters(26);
    for (int i = 0; i < 26; i++) letters[i] = char('a' + i);
    shuffle(letters.begin(), letters.end());
    // Left-side subjects and external pool
    vector<char> leftLetters(letters.begin(), letters.begin() + n);
    vector<char> extPool(letters.begin() + n, letters.end());
    // Hyper-parameter: probability to pick external parent
    double extProb = rnd.next(0.0, 1.0);
    // Generate premises
    vector<pair<char,char>> edges;
    for (char s : leftLetters) {
        // Candidates among left letters (excluding itself)
        vector<char> leftCands;
        leftCands.reserve(n-1);
        for (char t : leftLetters) if (t != s) leftCands.push_back(t);
        char p;
        if (!extPool.empty() && rnd.next() < extProb) {
            p = rnd.any(extPool);
        } else {
            p = rnd.any(leftCands);
        }
        edges.emplace_back(s, p);
    }
    // Shuffle premises
    shuffle(edges.begin(), edges.end());
    // Build reachability over all lowercase letters
    bool reach[26][26] = {};
    for (auto &e : edges) {
        int u = e.first - 'a';
        int v = e.second - 'a';
        reach[u][v] = true;
    }
    for (int k = 0; k < 26; k++)
        for (int i = 0; i < 26; i++)
            if (reach[i][k])
                for (int j = 0; j < 26; j++)
                    if (reach[k][j])
                        reach[i][j] = true;
    // Collect reachable and non-reachable pairs (i != j)
    vector<pair<int,int>> reachList, nonReachList;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) if (i != j) {
            if (reach[i][j]) reachList.emplace_back(i,j);
            else nonReachList.emplace_back(i,j);
        }
    }
    // Number of queries
    int m = rnd.next(1, 10);
    vector<pair<int,int>> queries;
    bool haveReach = !reachList.empty();
    bool haveNon = !nonReachList.empty();
    if (m >= 2 && haveReach && haveNon) {
        queries.push_back(rnd.any(reachList));
        queries.push_back(rnd.any(nonReachList));
        for (int i = 2; i < m; i++) {
            if (haveReach && haveNon) {
                if (rnd.next(0,1) == 0) queries.push_back(rnd.any(reachList));
                else queries.push_back(rnd.any(nonReachList));
            } else if (haveReach) {
                queries.push_back(rnd.any(reachList));
            } else {
                queries.push_back(rnd.any(nonReachList));
            }
        }
    } else {
        for (int i = 0; i < m; i++) {
            if (haveReach && haveNon) {
                if (rnd.next(0,1) == 0) queries.push_back(rnd.any(reachList));
                else queries.push_back(rnd.any(nonReachList));
            } else if (haveReach) {
                queries.push_back(rnd.any(reachList));
            } else {
                queries.push_back(rnd.any(nonReachList));
            }
        }
    }
    // Shuffle queries
    shuffle(queries.begin(), queries.end());
    // Output
    println(n);
    for (auto &e : edges) {
        printf("%c is %c\n", e.first, e.second);
    }
    println(m);
    for (auto &q : queries) {
        printf("%c is %c\n", char('a' + q.first), char('a' + q.second));
    }
    return 0;
}
