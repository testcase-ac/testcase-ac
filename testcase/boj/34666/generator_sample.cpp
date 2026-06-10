#include "testlib.h"
#include <algorithm>
#include <array>
#include <vector>

using namespace std;

struct Case {
    int grade;
    int language;
    int reading;
    int listening;
};

int clampScore(int score) {
    return max(0, min(60, score));
}

int nearScore(int base, int radius) {
    return clampScore(base + rnd.next(-radius, radius));
}

Case randomCase() {
    int grade = rnd.next(1, 5);
    int listeningMode = rnd.next(0, 5);
    int listening;
    if (listeningMode == 0) {
        listening = nearScore(50, 2);
    } else if (listeningMode == 1) {
        listening = rnd.next(0, 18);
    } else if (listeningMode == 2) {
        listening = rnd.next(55, 60);
    } else {
        listening = rnd.next(0, 60);
    }

    vector<int> pivots;
    if (grade == 1) {
        pivots = {18, 21, 22, 33, 34};
    } else if (grade == 2 || grade == 4) {
        pivots = {18, 21, 22, 29, 30};
    } else if (grade == 3) {
        pivots = {18, 21, 22, 31, 32};
    } else {
        pivots = {18, 21, 22, 26, 27};
    }

    auto pickSection = [&]() {
        if (rnd.next(0, 3) == 0) {
            return rnd.next(0, 60);
        }
        return nearScore(rnd.any(pivots), 2);
    };

    return {grade, pickSection(), pickSection(), listening};
}

Case focusedCase() {
    static const array<Case, 16> patterns = {{
        {1, 21, 60, 50},
        {1, 22, 60, 50},
        {1, 33, 33, 50},
        {1, 34, 34, 50},
        {1, 18, 18, 49},
        {2, 21, 60, 50},
        {2, 22, 60, 50},
        {2, 29, 29, 50},
        {2, 30, 30, 50},
        {2, 60, 60, 60},
        {3, 21, 21, 60},
        {3, 31, 31, 60},
        {4, 0, 37, 60},
        {4, 38, 0, 60},
        {5, 0, 37, 60},
        {5, 38, 0, 60},
    }};

    Case c = rnd.any(patterns);
    int mutate = rnd.next(0, 3);
    if (mutate == 0) c.language = nearScore(c.language, 1);
    if (mutate == 1) c.reading = nearScore(c.reading, 1);
    if (mutate == 2) c.listening = nearScore(c.listening, 1);
    return c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int q;
    int sizeMode = rnd.next(0, 9);
    if (sizeMode == 0) {
        q = 1;
    } else if (sizeMode <= 6) {
        q = rnd.next(2, 25);
    } else {
        q = rnd.next(26, 80);
    }

    vector<Case> cases;
    for (int i = 0; i < q; ++i) {
        if (rnd.next(0, 2) == 0) {
            cases.push_back(focusedCase());
        } else {
            cases.push_back(randomCase());
        }
    }

    shuffle(cases.begin(), cases.end());

    println(q);
    for (const Case& c : cases) {
        println(c.grade, c.language, c.reading, c.listening);
    }

    return 0;
}
