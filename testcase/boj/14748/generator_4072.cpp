#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    char type;           // 'S', 'L', or 'B'
    bool bracket;        // true => use [ ], false => use ( )
    vector<Node*> ch;    // children for L and B
};

double probComposite, probLoop;

// generate a node that consumes exactly 'budget' nodes
Node* genNode(int budget) {
    // must consume at least 1
    if (budget == 1) {
        Node* n = new Node();
        n->type = 'S';
        return n;
    }
    // decide whether composite or simple
    if (rnd.next() < probComposite) {
        // composite node L or B
        char tp = rnd.next() < probLoop ? 'L' : 'B';
        Node* n = new Node();
        n->type = tp;
        n->bracket = rnd.next() < 0.5;
        // decide how many children (at least 1, at most 3 or budget-1)
        int maxC = min(budget - 1, 3);
        int ccount = rnd.next(1, maxC);
        // partition budget-1 into ccount parts, each >=1
        int rem = budget - 1 - ccount;
        vector<int> parts(ccount, 1);
        for (int i = 0; i < rem; ++i) {
            int idx = rnd.next(0, ccount - 1);
            parts[idx]++;
        }
        // generate each child with its budget
        for (int i = 0; i < ccount; ++i) {
            n->ch.push_back(genNode(parts[i]));
        }
        return n;
    } else {
        // simple statement
        Node* n = new Node();
        n->type = 'S';
        return n;
    }
}

string build(Node* n) {
    if (n->type == 'S') {
        return "S";
    }
    // composite: L(...) or B[...]
    string res;
    res += n->type;
    char o = n->bracket ? '[' : '(';
    char c = n->bracket ? ']' : ')';
    res += o;
    for (int i = 0; i < (int)n->ch.size(); ++i) {
        if (i) res += ',';
        res += build(n->ch[i]);
    }
    res += c;
    return res;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // hyper-parameters
    int totalNodes = rnd.next(1, 10);
    probComposite = rnd.next(0.0, 1.0);
    probLoop = rnd.next(0.0, 1.0);

    // top-level node list: split totalNodes into 1..3 parts
    int maxTop = min(totalNodes, 3);
    int topCount = rnd.next(1, maxTop);
    int rem = totalNodes - topCount;
    vector<int> topParts(topCount, 1);
    for (int i = 0; i < rem; ++i) {
        int idx = rnd.next(0, topCount - 1);
        topParts[idx]++;
    }

    vector<Node*> roots;
    for (int i = 0; i < topCount; ++i) {
        roots.push_back(genNode(topParts[i]));
    }

    // build the base string without spaces
    string base;
    for (int i = 0; i < (int)roots.size(); ++i) {
        if (i) base += ',';
        base += build(roots[i]);
    }

    // randomly insert spaces around punctuation
    string P;
    for (char ch : base) {
        if ((ch == '('||ch==')'||ch=='['||ch==']'||ch==',') && rnd.next() < 0.3)
            P += ' ';
        P += ch;
        if ((ch == '('||ch==')'||ch=='['||ch==']'||ch==',') && rnd.next() < 0.3)
            P += ' ';
    }

    // weight W
    int W = rnd.next(2, 27);

    // output
    println(W);
    println(P);

    return 0;
}
