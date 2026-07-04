#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

const int MAX_VALUE = 50000;

static vector<int> chooseLabels(int count, bool highValues) {
    vector<int> labels;
    if (highValues) {
        int start = MAX_VALUE - count + 1;
        for (int i = 0; i < count; ++i) labels.push_back(start + i);
    } else {
        for (int i = 1; i <= count; ++i) labels.push_back(i);
    }
    shuffle(labels.begin(), labels.end());
    return labels;
}

static void addPath(vector<pair<int, int>>& edges, const vector<int>& labels, int len) {
    for (int i = 0; i < len; ++i) {
        edges.push_back({labels[i], labels[i + 1]});
    }
}

static void addCycle(vector<pair<int, int>>& edges, const vector<int>& labels, int len) {
    addPath(edges, labels, len - 1);
    edges.push_back({labels[len - 1], labels[0]});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> edges;
    int mode = rnd.next(0, 5);
    bool highValues = rnd.next(0, 4) == 0;

    if (mode == 0) {
        int len = rnd.next(1, 18);
        vector<int> labels = chooseLabels(len + 1, highValues);
        addPath(edges, labels, len);
    } else if (mode == 1) {
        int len = rnd.next(3, 16);
        vector<int> labels = chooseLabels(len, highValues);
        addCycle(edges, labels, len);
    } else if (mode == 2) {
        int components = rnd.next(2, 5);
        int nextLow = 1;
        int nextHigh = MAX_VALUE;
        for (int c = 0; c < components; ++c) {
            int len = rnd.next(1, 6);
            vector<int> labels;
            for (int i = 0; i <= len; ++i) {
                labels.push_back(highValues ? nextHigh-- : nextLow++);
            }
            addPath(edges, labels, len);
        }
    } else if (mode == 3) {
        int values = rnd.next(2, 8);
        vector<int> labels = chooseLabels(values, highValues);
        int n = rnd.next(6, 24);
        for (int i = 0; i < n; ++i) {
            int a = rnd.any(labels);
            int b = rnd.any(labels);
            edges.push_back({a, b});
        }
    } else if (mode == 4) {
        int values = rnd.next(2, 10);
        vector<int> labels = chooseLabels(values, highValues);
        int pairs = rnd.next(3, 12);
        for (int i = 0; i < pairs; ++i) {
            int a = rnd.any(labels);
            int b = rnd.any(labels);
            int copies = rnd.next(2, 5);
            for (int j = 0; j < copies; ++j) edges.push_back({a, b});
        }
    } else {
        int values = rnd.next(4, 14);
        vector<int> labels = chooseLabels(values, highValues);
        int n = rnd.next(values, 35);
        for (int i = 1; i < values; ++i) {
            edges.push_back({labels[rnd.next(0, i - 1)], labels[i]});
        }
        while ((int)edges.size() < n) {
            int a = rnd.any(labels);
            int b = rnd.any(labels);
            edges.push_back({a, b});
        }
    }

    shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        if (rnd.next(0, 1) == 1) swap(edge.first, edge.second);
    }

    println((int)edges.size());
    for (auto edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
