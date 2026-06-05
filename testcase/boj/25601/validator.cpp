#include "testlib.h"

#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Dsu {
public:
    explicit Dsu(int n) : parent_(n), rank_(n, 0) {
        iota(parent_.begin(), parent_.end(), 0);
    }

    int find(int x) {
        if (parent_[x] == x) {
            return x;
        }
        return parent_[x] = find(parent_[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        if (rank_[a] < rank_[b]) {
            swap(a, b);
        }
        parent_[b] = a;
        if (rank_[a] == rank_[b]) {
            ++rank_[a];
        }
        return true;
    }

private:
    vector<int> parent_;
    vector<int> rank_;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    unordered_map<string, int> id;
    id.reserve(static_cast<size_t>(n) * 2);

    auto getId = [&](const string& name) {
        auto it = id.find(name);
        if (it != id.end()) {
            return it->second;
        }
        int next = static_cast<int>(id.size());
        ensuref(next < n, "more than n distinct class names");
        id.emplace(name, next);
        return next;
    };

    Dsu dsu(n);
    vector<int> parent(n, -1);

    for (int i = 1; i <= n - 1; ++i) {
        string child = inf.readToken("[a-z]{2,50}", "child");
        inf.readSpace();
        string par = inf.readToken("[a-z]{2,50}", "parent");
        inf.readEoln();

        ensuref(child != par, "self inheritance at relationship %d: %s", i, child.c_str());

        int childId = getId(child);
        int parentId = getId(par);

        ensuref(parent[childId] == -1, "class %s has multiple direct parents", child.c_str());
        parent[childId] = parentId;
        ensuref(dsu.unite(childId, parentId), "inheritance relationships contain a cycle");
    }

    ensuref(static_cast<int>(id.size()) == n, "expected exactly n distinct class names, found %d",
            static_cast<int>(id.size()));

    int roots = 0;
    for (int i = 0; i < n; ++i) {
        if (parent[i] == -1) {
            ++roots;
        }
    }
    ensuref(roots == 1, "inheritance tree must have exactly one root, found %d", roots);

    string a = inf.readToken("[a-z]{2,50}", "query_a");
    inf.readSpace();
    string b = inf.readToken("[a-z]{2,50}", "query_b");
    inf.readEoln();

    ensuref(a != b, "query class names must be distinct");
    ensuref(id.find(a) != id.end(), "query class %s was not present in relationships", a.c_str());
    ensuref(id.find(b) != id.end(), "query class %s was not present in relationships", b.c_str());

    inf.readEof();
}
