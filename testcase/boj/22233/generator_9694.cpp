#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <cstdio>

using namespace std;

string genKeyword(int lenMin, int lenMax, set<string> &used) {
    static const string chars = "abcdefghijklmnopqrstuvwxyz0123456789";
    while (true) {
        int len = rnd.next(lenMin, lenMax);
        string s;
        s.reserve(len);
        for (int i = 0; i < len; ++i) {
            s.push_back(chars[rnd.next(0, (int)chars.size() - 1)]);
        }
        if (!used.count(s)) {
            used.insert(s);
            return s;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 2); // 0,1,2
    int N = 0, M = 0;
    vector<string> memoKeywords;
    vector<string> extraKeywords;
    vector<vector<string>> posts;
    set<string> usedNames;

    if (scenario == 0) {
        // Scenario 0: Only memo keywords, every memo keyword appears in at least one post
        do {
            N = rnd.next(1, 8);
            M = rnd.next(1, 8);
        } while (N > 5 * M); // ensure capacity

        memoKeywords.resize(N);
        for (int i = 0; i < N; ++i) {
            memoKeywords[i] = genKeyword(1, 5, usedNames);
        }

        posts.assign(M, vector<string>());
        vector<int> cnt(M, 0);
        vector<bool> usedMemo(N, false);

        // Step 1: ensure each post has at least one memo keyword
        for (int i = 0; i < M; ++i) {
            int idx = rnd.next(0, N - 1);
            posts[i].push_back(memoKeywords[idx]);
            cnt[i]++;
            usedMemo[idx] = true;
        }

        // Step 2: ensure every memo keyword appears in at least one post
        vector<int> capacityIndices;
        capacityIndices.reserve(5 * M - M);
        for (int i = 0; i < M; ++i) {
            int cap = 5 - cnt[i];
            for (int c = 0; c < cap; ++c) capacityIndices.push_back(i);
        }

        for (int j = 0; j < N; ++j) {
            if (!usedMemo[j]) {
                int pos = rnd.next(0, (int)capacityIndices.size() - 1);
                int art = capacityIndices[pos];
                posts[art].push_back(memoKeywords[j]);
                cnt[art]++;
                // remove this capacity slot
                capacityIndices[pos] = capacityIndices.back();
                capacityIndices.pop_back();
            }
        }
    } else if (scenario == 1) {
        // Scenario 1: Mixed memo and extra keywords, at least one post with only extra keywords
        N = rnd.next(1, 6);
        M = rnd.next(2, 8);
        memoKeywords.resize(N);
        for (int i = 0; i < N; ++i) {
            memoKeywords[i] = genKeyword(1, 5, usedNames);
        }

        int maxExtra = 4;
        int E = rnd.next(1, maxExtra); // at least one extra keyword
        extraKeywords.resize(E);
        for (int i = 0; i < E; ++i) {
            extraKeywords[i] = genKeyword(1, 5, usedNames);
        }

        vector<string> pool = memoKeywords;
        pool.insert(pool.end(), extraKeywords.begin(), extraKeywords.end());
        int poolSize = (int)pool.size();

        posts.assign(M, vector<string>());

        // Generic generation
        for (int i = 0; i < M; ++i) {
            bool narrow = rnd.next(0, 1) == 1;
            vector<int> candidates;
            if (narrow) {
                int subsetSize = rnd.next(1, min(3, poolSize));
                for (int j = 0; j < subsetSize; ++j) candidates.push_back(j);
            } else {
                candidates.resize(poolSize);
                for (int j = 0; j < poolSize; ++j) candidates[j] = j;
            }
            shuffle(candidates.begin(), candidates.end());
            int kMax = min(5, (int)candidates.size());
            int k = rnd.next(1, kMax);
            posts[i].clear();
            for (int t = 0; t < k; ++t) {
                posts[i].push_back(pool[candidates[t]]);
            }
        }

        // Ensure at least one article contains only extra keywords
        int idx = rnd.next(0, M - 1);
        {
            int kMax = min(5, E);
            int k = rnd.next(1, kMax);
            vector<int> ids(E);
            for (int i = 0; i < E; ++i) ids[i] = i;
            shuffle(ids.begin(), ids.end());
            posts[idx].clear();
            for (int t = 0; t < k; ++t) {
                posts[idx].push_back(extraKeywords[ids[t]]);
            }
        }
    } else if (scenario == 2) {
        // Scenario 2: One special memo keyword repeated in many posts
        N = rnd.next(1, 8);
        M = rnd.next(2, 8);
        memoKeywords.resize(N);
        for (int i = 0; i < N; ++i) {
            memoKeywords[i] = genKeyword(1, 5, usedNames);
        }

        int maxExtra = 3;
        int E = rnd.next(0, maxExtra);
        extraKeywords.resize(E);
        for (int i = 0; i < E; ++i) {
            extraKeywords[i] = genKeyword(1, 5, usedNames);
        }

        vector<string> pool = memoKeywords;
        pool.insert(pool.end(), extraKeywords.begin(), extraKeywords.end());
        int poolSize = (int)pool.size();

        int specialIdx = rnd.next(0, N - 1);
        string special = memoKeywords[specialIdx];

        posts.assign(M, vector<string>());

        for (int i = 0; i < M; ++i) {
            bool forceSpecial;
            if (poolSize == 1) {
                forceSpecial = true; // only special exists
            } else {
                forceSpecial = (i == 0 || i == 1);
            }

            bool includeSpecial;
            if (forceSpecial) includeSpecial = true;
            else includeSpecial = (rnd.next(0, 1) == 1);

            int maxPossible = includeSpecial ? poolSize : (poolSize - 1);
            int kMax = min(5, maxPossible);
            int kMin = 1;
            int k = rnd.next(kMin, kMax);

            vector<string> article;
            if (includeSpecial) {
                article.push_back(special);
            }
            int remaining = k - (int)article.size();

            vector<int> others;
            others.reserve(poolSize - 1);
            for (int j = 0; j < poolSize; ++j) {
                if (pool[j] != special) others.push_back(j);
            }
            shuffle(others.begin(), others.end());
            for (int t = 0; t < remaining && t < (int)others.size(); ++t) {
                article.push_back(pool[others[t]]);
            }
            posts[i] = article;
        }
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; ++i) {
        println(memoKeywords[i]);
    }
    for (int i = 0; i < M; ++i) {
        const vector<string> &kw = posts[i];
        for (int j = 0; j < (int)kw.size(); ++j) {
            if (j) printf(",");
            printf("%s", kw[j].c_str());
        }
        printf("\n");
    }

    return 0;
}
