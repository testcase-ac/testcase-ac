#include "testlib.h"

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Claim {
    bool impossible;
    vector<int> left;
    vector<int> right;
    long long leftSum;
    long long rightSum;
};

int n;
int sideSize;
vector<int> leftChild;
vector<int> rightChild;

void buildShape() {
    leftChild.assign(sideSize, -1);
    rightChild.assign(sideSize, -1);
    for (int i = 0; i < sideSize; ++i) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < sideSize) {
            leftChild[i] = l;
        }
        if (r < sideSize) {
            rightChild[i] = r;
        }
    }
}

void mirrorShape(vector<int>& childLeft, vector<int>& childRight) {
    for (int i = 0; i < sideSize; ++i) {
        swap(childLeft[i], childRight[i]);
    }
}

vector<int> parseLineValues(InStream& stream, const string& line, const char* lineName) {
    istringstream iss(line);
    vector<int> values;
    string token;
    while (iss >> token) {
        size_t pos = 0;
        int value = 0;
        try {
            value = stoi(token, &pos);
        } catch (...) {
            stream.quitf(_wa, "%s contains non-integer token '%s'", lineName, token.c_str());
        }
        if (pos != token.size()) {
            stream.quitf(_wa, "%s contains non-integer token '%s'", lineName, token.c_str());
        }
        values.push_back(value);
    }
    return values;
}

int assignPreorder(const vector<int>& preorder,
                   const vector<int>& childLeft,
                   const vector<int>& childRight,
                   vector<int>& nodeValue,
                   int node,
                   int pos) {
    if (node == -1) {
        return pos;
    }
    if (pos >= (int)preorder.size()) {
        return pos;
    }
    nodeValue[node] = preorder[pos++];
    pos = assignPreorder(preorder, childLeft, childRight, nodeValue, childLeft[node], pos);
    pos = assignPreorder(preorder, childLeft, childRight, nodeValue, childRight[node], pos);
    return pos;
}

pair<int, int> validateOrder(InStream& stream,
                             const vector<int>& nodeValue,
                             const vector<int>& childLeft,
                             const vector<int>& childRight,
                             int node,
                             const char* sideName) {
    int value = nodeValue[node];
    int minimum = value;
    int maximum = value;

    if (childLeft[node] != -1) {
        auto child = validateOrder(stream, nodeValue, childLeft, childRight, childLeft[node], sideName);
        if (child.second >= value) {
            stream.quitf(_wa,
                         "%s subtree rooted at %d has left-side weight %d not lighter than %d",
                         sideName,
                         value,
                         child.second,
                         value);
        }
        minimum = min(minimum, child.first);
        maximum = max(maximum, child.second);
    }

    if (childRight[node] != -1) {
        auto child = validateOrder(stream, nodeValue, childLeft, childRight, childRight[node], sideName);
        if (child.first <= value) {
            stream.quitf(_wa,
                         "%s subtree rooted at %d has right-side weight %d not heavier than %d",
                         sideName,
                         value,
                         child.first,
                         value);
        }
        minimum = min(minimum, child.first);
        maximum = max(maximum, child.second);
    }

    return {minimum, maximum};
}

long long validateSide(InStream& stream,
                       const vector<int>& preorder,
                       const vector<int>& childLeft,
                       const vector<int>& childRight,
                       const char* sideName) {
    if ((int)preorder.size() != sideSize) {
        stream.quitf(_wa,
                     "%s side has %d weights, expected %d",
                     sideName,
                     (int)preorder.size(),
                     sideSize);
    }

    long long sum = 0;
    for (int i = 0; i < sideSize; ++i) {
        int value = preorder[i];
        if (value < 1 || value > n) {
            stream.quitf(_wa,
                         "%s[%d]=%d is outside [1, %d]",
                         sideName,
                         i + 1,
                         value,
                         n);
        }
        sum += value;
    }

    vector<int> nodeValue(sideSize);
    int consumed = assignPreorder(preorder, childLeft, childRight, nodeValue, 0, 0);
    if (consumed != sideSize) {
        stream.quitf(_wa, "%s preorder did not match the required shape", sideName);
    }
    if (sideSize > 0) {
        validateOrder(stream, nodeValue, childLeft, childRight, 0, sideName);
    }
    return sum;
}

Claim readClaim(InStream& stream) {
    string firstLine = stream.readLine();
    vector<int> first = parseLineValues(stream, firstLine, "first line");

    if (first.size() == 1 && first[0] == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, {}, {}, 0, 0};
    }

    string secondLine = stream.readLine();
    vector<int> second = parseLineValues(stream, secondLine, "second line");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after the two preorder lines");
    }

    vector<int> mirroredLeft = leftChild;
    vector<int> mirroredRight = rightChild;
    mirrorShape(mirroredLeft, mirroredRight);

    long long leftSum = validateSide(stream, first, leftChild, rightChild, "left");
    long long rightSum = validateSide(stream, second, mirroredLeft, mirroredRight, "right");

    vector<int> used(n + 1, 0);
    for (int value : first) {
        if (used[value]) {
            stream.quitf(_wa, "weight %d is used more than once", value);
        }
        used[value] = 1;
    }
    for (int value : second) {
        if (used[value]) {
            stream.quitf(_wa, "weight %d is used more than once", value);
        }
        used[value] = 1;
    }

    if (leftSum != rightSum) {
        stream.quitf(_wa, "left sum %lld differs from right sum %lld", leftSum, rightSum);
    }

    return {false, first, second, leftSum, rightSum};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 100000, "n");
    sideSize = n / 2;
    buildShape();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid balanced arrangement while jury reports -1");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports -1, but jury has a valid arrangement");
    }

    quitf(_ok, "valid balanced arrangement with side sum %lld", participant.leftSum);
}
