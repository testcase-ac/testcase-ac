#include "testlib.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

struct Node {
    vector<int> items;
    vector<int> children;
};

static int addNode(vector<Node>& nodes, const vector<int>& items) {
    nodes.push_back({items, {}});
    return (int)nodes.size() - 1;
}

static void splitNode(vector<Node>& nodes, int node, int depth) {
    int size = (int)nodes[node].items.size();
    if (size <= 1 || depth >= 3 || rnd.next(100) < 30) return;

    int parts = rnd.next(2, min(4, size));
    vector<int> cut(size - 1);
    iota(cut.begin(), cut.end(), 1);
    shuffle(cut.begin(), cut.end());
    cut.resize(parts - 1);
    sort(cut.begin(), cut.end());
    cut.push_back(size);

    int last = 0;
    for (int end : cut) {
        vector<int> childItems(nodes[node].items.begin() + last, nodes[node].items.begin() + end);
        int child = addNode(nodes, childItems);
        nodes[node].children.push_back(child);
        splitNode(nodes, child, depth + 1);
        last = end;
    }
}

static int priceFor(const vector<Node>& nodes, int node) {
    int size = (int)nodes[node].items.size();
    if (nodes[node].children.empty()) return rnd.next(1, 25);

    int childSum = 0;
    for (int child : nodes[node].children) {
        childSum += max(1, (int)nodes[child].items.size() * rnd.next(2, 9));
    }

    if (rnd.next(100) < 45) return max(1, childSum - rnd.next(0, min(10, childSum - 1)));
    return size * rnd.next(4, 18) + rnd.next(0, 20);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    cout << T << '\n';

    for (int tc = 0; tc < T; ++tc) {
        int n = rnd.next(1, 18);
        vector<int> labels(n);
        iota(labels.begin(), labels.end(), 1);
        shuffle(labels.begin(), labels.end());

        vector<Node> nodes;
        int topParts = n == 1 ? 1 : rnd.next(1, min(4, n));
        vector<int> cut(n - 1);
        iota(cut.begin(), cut.end(), 1);
        shuffle(cut.begin(), cut.end());
        cut.resize(topParts - 1);
        sort(cut.begin(), cut.end());
        cut.push_back(n);

        int last = 0;
        vector<int> roots;
        for (int end : cut) {
            vector<int> rootItems(labels.begin() + last, labels.begin() + end);
            sort(rootItems.begin(), rootItems.end());
            int root = addNode(nodes, rootItems);
            roots.push_back(root);
            splitNode(nodes, root, 0);
            last = end;
        }

        vector<int> chosen = roots;
        for (int i = 0; i < (int)nodes.size(); ++i) {
            if (find(roots.begin(), roots.end(), i) != roots.end()) continue;
            int keepChance = nodes[i].items.size() == 1 ? 65 : 80;
            if (rnd.next(100) < keepChance) chosen.push_back(i);
        }

        if (topParts > 1 && rnd.next(100) < 35) {
            vector<int> all = labels;
            sort(all.begin(), all.end());
            int full = addNode(nodes, all);
            chosen.push_back(full);
        }

        int duplicateBudget = min(8, 150 - (int)chosen.size());
        int duplicates = chosen.empty() ? 0 : rnd.next(0, duplicateBudget);
        for (int i = 0; i < duplicates; ++i) {
            chosen.push_back(rnd.any(chosen));
        }

        shuffle(chosen.begin(), chosen.end());
        cout << n << ' ' << chosen.size() << '\n';
        for (int node : chosen) {
            vector<int> items = nodes[node].items;
            if (rnd.next(100) < 55) shuffle(items.begin(), items.end());
            int price = priceFor(nodes, node);
            cout << price << ' ' << items.size();
            for (int item : items) cout << ' ' << item;
            cout << '\n';
        }
    }

    return 0;
}
