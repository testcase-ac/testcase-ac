#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const string kAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

string uniqueQueue(int n) {
    string chars = kAlphabet;
    shuffle(chars.begin(), chars.end());
    return chars.substr(0, n);
}

string repeatedCharQueue(int n) {
    return string(n, rnd.any(kAlphabet));
}

string blockQueue(int n) {
    int groups = rnd.next(1, min(8, n));
    string labels = uniqueQueue(groups);
    string result;

    int remaining = n;
    for (int i = 0; i < groups; ++i) {
        int len = (i == groups - 1) ? remaining : rnd.next(1, remaining - (groups - i - 1));
        result += string(len, labels[i]);
        remaining -= len;
    }

    if (rnd.next(2)) {
        vector<string> blocks;
        int pos = 0;
        for (int i = 0; i < groups; ++i) {
            int end = pos;
            while (end < n && result[end] == result[pos]) ++end;
            blocks.push_back(result.substr(pos, end - pos));
            pos = end;
        }
        shuffle(blocks.begin(), blocks.end());
        result.clear();
        for (const string& block : blocks) result += block;
    }

    return result;
}

string alternatingQueue(int n) {
    int groups = rnd.next(2, min(5, n));
    string labels = uniqueQueue(groups);
    string result;
    for (int i = 0; i < n; ++i) result += labels[i % groups];

    int swaps = rnd.next(n / 3 + 1);
    for (int i = 0; i < swaps; ++i) {
        swap(result[rnd.next(n)], result[rnd.next(n)]);
    }

    return result;
}

string randomSubsetQueue(int n) {
    int groups = rnd.next(1, min(12, n));
    string labels = uniqueQueue(groups);
    string result;
    for (int i = 0; i < n; ++i) {
        int label = rnd.wnext(groups, rnd.next(-2, 3));
        result += labels[label];
    }
    return result;
}

string pairedEndsQueue(int n) {
    int groups = rnd.next(1, min(8, n));
    string labels = uniqueQueue(groups);
    string result(n, labels[0]);

    for (int i = 0; i < n; ++i) {
        int mirrored = min(i, n - 1 - i);
        result[i] = labels[mirrored % groups];
    }

    if (rnd.next(2)) reverse(result.begin(), result.end());
    return result;
}

string makeQueue() {
    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 62);
        return uniqueQueue(n);
    }

    n = (mode == 3) ? rnd.next(2, 80) : rnd.next(1, 80);
    if (mode == 1) return repeatedCharQueue(n);
    if (mode == 2) return blockQueue(n);
    if (mode == 3) return alternatingQueue(n);
    if (mode == 4) return randomSubsetQueue(n);
    return pairedEndsQueue(n);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 12);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        string queue = makeQueue();
        println((int)queue.size());
        println(queue);
    }

    return 0;
}
