#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Submission {
    string name;
    string place;
    int start;
    int end;
};

string label(const string& prefix, int index) {
    string suffix;
    do {
        suffix.push_back(char('a' + index % 26));
        index /= 26;
    } while (index > 0);
    return prefix + suffix;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int placeCount = rnd.next(1, mode == 5 ? 10 : 5);
    int uniqueNameCount = rnd.next(1, 12);
    vector<string> places;
    vector<string> names;
    for (int i = 0; i < placeCount; ++i) {
        places.push_back(label("p", i));
    }
    for (int i = 0; i < uniqueNameCount; ++i) {
        names.push_back(label("n", i));
    }

    vector<Submission> submissions;
    auto addSubmission = [&](string name, string place, int start, int end) {
        submissions.push_back({name, place, start, end});
    };

    if (mode == 0) {
        int n = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            int start = rnd.next(1, 20);
            int end = rnd.next(start + 1, start + rnd.next(1, 8));
            addSubmission(names[i % uniqueNameCount], places[rnd.next(placeCount)], start, end);
        }
    } else if (mode == 1) {
        int baseStart = rnd.next(1, 30);
        int baseEnd = baseStart + rnd.next(3, 15);
        int copies = rnd.next(3, 8);
        for (int i = 0; i < copies; ++i) {
            addSubmission(names[i % uniqueNameCount], places[0], baseStart, baseEnd);
        }
        int extras = rnd.next(1, 8);
        for (int i = 0; i < extras; ++i) {
            int start = rnd.next(1, 40);
            int end = rnd.next(start + 1, start + rnd.next(1, 10));
            addSubmission(names[(i + copies) % uniqueNameCount], places[rnd.next(placeCount)], start, end);
        }
    } else if (mode == 2) {
        int left = rnd.next(1, 30);
        int width = rnd.next(4, 12);
        for (int i = 0; i < placeCount; ++i) {
            addSubmission(names[i % uniqueNameCount], places[i], left, left + width);
            addSubmission(names[(i + placeCount) % uniqueNameCount], places[i], left + 1, left + width + 1);
        }
        int extras = rnd.next(0, 6);
        for (int i = 0; i < extras; ++i) {
            int start = rnd.next(1, 45);
            addSubmission(names[(i + 2 * placeCount) % uniqueNameCount], places[rnd.next(placeCount)], start, start + rnd.next(1, 5));
        }
    } else if (mode == 3) {
        int n = rnd.next(8, 20);
        for (int i = 0; i < n; ++i) {
            int start = rnd.next(1, 80);
            int end = rnd.next(start + 1, start + rnd.next(1, 20));
            string name = rnd.next(0, 3) == 0 ? names[rnd.next(uniqueNameCount)] : label("u", i);
            addSubmission(name, places[rnd.next(placeCount)], start, end);
        }
    } else if (mode == 4) {
        int start = rnd.next(49970, 49998);
        addSubmission("edgea", places[0], 1, 50000);
        addSubmission("edgeb", places[0], start, 50000);
        addSubmission("edgec", places[rnd.next(placeCount)], 1, 2);
        int extras = rnd.next(0, 7);
        for (int i = 0; i < extras; ++i) {
            int s = rnd.next(49950, 49998);
            addSubmission(label("e", i), places[rnd.next(placeCount)], s, rnd.next(s + 1, 50000));
        }
    } else {
        int n = rnd.next(25, 60);
        for (int i = 0; i < n; ++i) {
            int cluster = rnd.next(0, 3);
            int start = 1 + cluster * 10 + rnd.next(0, 12);
            int end = rnd.next(start + 1, start + rnd.next(2, 18));
            string name = rnd.next(0, 5) == 0 ? names[rnd.next(uniqueNameCount)] : label("m", i);
            addSubmission(name, places[rnd.next(placeCount)], start, end);
        }
    }

    shuffle(submissions.begin(), submissions.end());
    println((int)submissions.size());
    for (const Submission& sub : submissions) {
        println(sub.name, sub.place, sub.start, sub.end);
    }

    return 0;
}
