#include "testlib.h"

#include <algorithm>
#include <map>
#include <set>
#include <vector>

using namespace std;

struct Segment {
    int fixed;
    int low;
    int high;
};

struct Fenwick {
    vector<int> tree;

    explicit Fenwick(int n) : tree(n + 1, 0) {}

    void add(int index, int value) {
        for (++index; index < (int)tree.size(); index += index & -index) {
            tree[index] += value;
        }
    }

    int sumPrefix(int index) const {
        int result = 0;
        for (++index; index > 0; index -= index & -index) {
            result += tree[index];
        }
        return result;
    }

    int sumRange(int low, int high) const {
        if (low > high) {
            return 0;
        }
        return sumPrefix(high) - (low == 0 ? 0 : sumPrefix(low - 1));
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int block = 1;
    int totalPosts = 0;
    while (true) {
        int p = inf.readInt(0, 100000, "P");
        inf.readEoln();
        if (p == 0) {
            break;
        }
        setTestCase(block);

        // CHECK: The written lower bound is 1, but a buildable orthogonal fence
        // with posts only at direction changes needs at least four posts.
        ensuref(p >= 4, "block %d: fewer than four posts cannot form a fence", block);
        ensuref(p % 2 == 0, "block %d: an orthogonal fence has an even number of posts", block);
        totalPosts += p;
        // CHECK: The statement does not cap the number of blocks. Keep aggregate
        // input at one largest block, matching local multi-case size policy.
        ensuref(totalPosts <= 100000, "total number of posts exceeds 100000");

        set<pair<int, int>> uniquePoints;
        map<int, vector<pair<int, int>>> byX;
        map<int, vector<pair<int, int>>> byY;

        for (int i = 0; i < p; ++i) {
            int x = inf.readInt(0, 10000, "X");
            inf.readSpace();
            int y = inf.readInt(0, 10000, "Y");
            inf.readEoln();

            ensuref(uniquePoints.insert({x, y}).second,
                    "block %d: duplicate post (%d, %d)", block, x, y);
            byX[x].push_back({y, i});
            byY[y].push_back({x, i});
        }

        vector<vector<int>> graph(p);
        vector<Segment> vertical;
        vector<Segment> horizontal;

        for (auto& [x, posts] : byX) {
            // CHECK: Buildability requires posts on each vertical line to pair
            // into fence segments.
            ensuref(posts.size() % 2 == 0,
                    "block %d: x = %d has an odd number of posts", block, x);
            sort(posts.begin(), posts.end());
            for (int i = 0; i < (int)posts.size(); i += 2) {
                int a = posts[i].second;
                int b = posts[i + 1].second;
                graph[a].push_back(b);
                graph[b].push_back(a);
                vertical.push_back({x, posts[i].first, posts[i + 1].first});
            }
        }

        for (auto& [y, posts] : byY) {
            // CHECK: Buildability requires posts on each horizontal line to pair
            // into fence segments.
            ensuref(posts.size() % 2 == 0,
                    "block %d: y = %d has an odd number of posts", block, y);
            sort(posts.begin(), posts.end());
            for (int i = 0; i < (int)posts.size(); i += 2) {
                int a = posts[i].second;
                int b = posts[i + 1].second;
                graph[a].push_back(b);
                graph[b].push_back(a);
                horizontal.push_back({y, posts[i].first, posts[i + 1].first});
            }
        }

        for (int i = 0; i < p; ++i) {
            ensuref(graph[i].size() == 2,
                    "block %d: post %d has degree %d, expected 2",
                    block, i + 1, (int)graph[i].size());
        }

        vector<int> stack = {0};
        vector<char> seen(p, false);
        seen[0] = true;
        for (int at = 0; at < (int)stack.size(); ++at) {
            int u = stack[at];
            for (int v : graph[u]) {
                if (!seen[v]) {
                    seen[v] = true;
                    stack.push_back(v);
                }
            }
        }
        ensuref((int)stack.size() == p,
                "block %d: posts do not form one connected fence", block);

        vector<vector<int>> addAtX(10001), removeAtX(10001);
        for (const Segment& h : horizontal) {
            if (h.low + 1 < h.high) {
                addAtX[h.low + 1].push_back(h.fixed);
                removeAtX[h.high].push_back(h.fixed);
            }
        }

        map<int, vector<Segment>> verticalByX;
        for (const Segment& v : vertical) {
            verticalByX[v.fixed].push_back(v);
        }

        Fenwick activeHorizontal(10001);
        for (int x = 0; x <= 10000; ++x) {
            for (int y : addAtX[x]) {
                activeHorizontal.add(y, 1);
            }
            for (int y : removeAtX[x]) {
                activeHorizontal.add(y, -1);
            }

            auto it = verticalByX.find(x);
            if (it == verticalByX.end()) {
                continue;
            }
            for (const Segment& v : it->second) {
                int crossingCount = activeHorizontal.sumRange(v.low + 1, v.high - 1);
                ensuref(crossingCount == 0,
                        "block %d: vertical segment x=%d y=[%d,%d] has an interior crossing",
                        block, v.fixed, v.low, v.high);
            }
        }

        inf.readEoln();
        ++block;
    }

    inf.readEof();
}
