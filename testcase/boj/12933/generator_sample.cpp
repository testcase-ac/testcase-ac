#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomValidRecording(int ducks, int repeats) {
    const string sound = "quack";
    vector<int> stage(ducks, 0);
    vector<int> done(ducks, 0);
    string s;

    while (true) {
        vector<int> candidates;
        for (int i = 0; i < ducks; ++i) {
            if (done[i] < repeats) candidates.push_back(i);
        }
        if (candidates.empty()) break;

        int duck = rnd.any(candidates);
        s += sound[stage[duck]];
        ++stage[duck];
        if (stage[duck] == 5) {
            stage[duck] = 0;
            ++done[duck];
        }
    }

    return s;
}

string blockRecording(int ducks, int repeats) {
    const string sound = "quack";
    string s;
    for (int r = 0; r < repeats; ++r) {
        for (char c : sound) {
            s += string(ducks, c);
        }
    }
    return s;
}

string repeatedSingleDuck(int repeats) {
    string s;
    for (int i = 0; i < repeats; ++i) s += "quack";
    return s;
}

string randomContractString(int len) {
    const string alphabet = "quack";
    string s;
    for (int i = 0; i < len; ++i) s += rnd.any(alphabet);
    return s;
}

string mutateValidToInvalid(string s) {
    const string alphabet = "quack";
    int mode = rnd.next(4);
    if (mode == 0) {
        int pos = rnd.next((int)s.size());
        char replacement = rnd.any(alphabet);
        while (replacement == s[pos]) replacement = rnd.any(alphabet);
        s[pos] = replacement;
    } else if (mode == 1) {
        s.insert(s.begin() + rnd.next((int)s.size() + 1), rnd.any(alphabet));
    } else if (mode == 2 && s.size() > 5) {
        s.erase(s.begin() + rnd.next((int)s.size()));
    } else {
        shuffle(s.begin(), s.end());
    }

    while (s.size() < 5) s += rnd.any(alphabet);
    if (s.size() > 2500) s.resize(2500);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    string s;

    if (mode == 0) {
        s = repeatedSingleDuck(rnd.next(1, 12));
    } else if (mode == 1) {
        int ducks = rnd.next(2, 12);
        int repeats = rnd.next(1, 4);
        s = blockRecording(ducks, repeats);
    } else if (mode == 2) {
        int ducks = rnd.next(2, 10);
        int repeats = rnd.next(1, 5);
        s = randomValidRecording(ducks, repeats);
    } else if (mode == 3) {
        int len = rnd.next(5, 80);
        s = randomContractString(len);
    } else if (mode == 4) {
        int ducks = rnd.next(1, 8);
        int repeats = rnd.next(1, 4);
        s = mutateValidToInvalid(randomValidRecording(ducks, repeats));
    } else {
        int ducks = rnd.next(20, 80);
        s = blockRecording(ducks, 1);
    }

    println(s);
    return 0;
}
