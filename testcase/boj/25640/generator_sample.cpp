#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> types = {
        "INFP", "ENFP", "ISFP", "ESFP",
        "INTP", "ENTP", "ISTP", "ESTP",
        "INFJ", "ENFJ", "ISFJ", "ESFJ",
        "INTJ", "ENTJ", "ISTJ", "ESTJ",
    };

    string jinho = rnd.any(types);
    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else if (mode == 2) {
        n = rnd.next(9, 24);
    } else if (mode == 3) {
        n = rnd.next(25, 60);
    } else if (mode == 4) {
        n = 100;
    } else {
        n = rnd.next(1, 100);
    }

    vector<string> otherTypes;
    for (const string& type : types) {
        if (type != jinho) otherTypes.push_back(type);
    }

    vector<string> friends;
    friends.reserve(n);
    int matches;
    if (mode == 0) {
        matches = rnd.next(0, 1);
    } else if (mode == 1) {
        matches = 0;
    } else if (mode == 2) {
        matches = n;
    } else if (mode == 3) {
        matches = rnd.next(1, n - 1);
    } else if (mode == 4) {
        matches = rnd.next(0, 100);
    } else {
        matches = rnd.next(0, n);
    }

    for (int i = 0; i < matches; ++i) {
        friends.push_back(jinho);
    }
    while ((int)friends.size() < n) {
        friends.push_back(rnd.any(otherTypes));
    }
    shuffle(friends.begin(), friends.end());

    println(jinho);
    println(n);
    for (const string& type : friends) {
        println(type);
    }

    return 0;
}
