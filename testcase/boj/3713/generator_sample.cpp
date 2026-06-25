#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

struct Pupil {
    int h;
    string sex;
    string music;
    string sport;
};

string label(const string& prefix, int id) {
    return prefix + to_string(id);
}

Pupil makePupil(int h, const string& sex, int music, int sport) {
    return Pupil{h, sex, label("m", music), label("s", sport)};
}

void addDenseConflictCluster(vector<Pupil>& pupils, int men, int women) {
    int baseH = rnd.next(20, 220);
    int music = rnd.next(0, 4);
    int sportBase = rnd.next(0, 20);

    for (int i = 0; i < men; ++i) {
        pupils.push_back(makePupil(baseH + rnd.next(0, 40), "M", music, sportBase + i));
    }
    for (int i = 0; i < women; ++i) {
        pupils.push_back(makePupil(baseH + rnd.next(0, 40), "F", music, sportBase + men + i));
    }
}

void addAllSafeByRule(vector<Pupil>& pupils, int n, int rule) {
    int baseH = rnd.next(50, 200);
    int music = rnd.next(10, 20);
    int sport = rnd.next(10, 20);

    for (int i = 0; i < n; ++i) {
        string sex = (i % 2 == 0 ? "M" : "F");
        int h = baseH + rnd.next(0, 30);
        int curMusic = music;
        int curSport = sport + i;

        if (rule == 0) h = baseH + 50 * i;
        if (rule == 1) sex = "M";
        if (rule == 2) curMusic = music + i;
        if (rule == 3) curSport = sport;

        pupils.push_back(makePupil(h, sex, curMusic, curSport));
    }
}

vector<Pupil> makeCase() {
    vector<Pupil> pupils;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            pupils.push_back(makePupil(rnd.next(0, 80), rnd.next(0, 1) ? "M" : "F",
                                       rnd.next(0, 2), rnd.next(0, 2)));
        }
    } else if (mode == 1) {
        addDenseConflictCluster(pupils, rnd.next(2, 7), rnd.next(2, 7));
    } else if (mode == 2) {
        addAllSafeByRule(pupils, rnd.next(4, 12), rnd.next(0, 3));
    } else if (mode == 3) {
        int baseH = rnd.next(0, 1000000000 - 41);
        int music = rnd.next(0, 3);
        pupils.push_back(makePupil(baseH, "M", music, 0));
        pupils.push_back(makePupil(baseH + 40, "F", music, 1));
        pupils.push_back(makePupil(baseH + 41, "F", music, 2));
        pupils.push_back(makePupil(baseH, "F", music + 1, 3));
        pupils.push_back(makePupil(baseH, "F", music, 0));
    } else if (mode == 4) {
        int clusters = rnd.next(2, 4);
        for (int i = 0; i < clusters; ++i) {
            addDenseConflictCluster(pupils, rnd.next(1, 4), rnd.next(1, 4));
        }
        addAllSafeByRule(pupils, rnd.next(2, 6), rnd.next(0, 3));
    } else {
        int n = rnd.next(8, 28);
        int heightBase = rnd.next(0, 250);
        int musicKinds = rnd.next(1, 5);
        int sportKinds = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            int h = heightBase + rnd.next(0, 90);
            string sex = rnd.next(0, 1) ? "M" : "F";
            pupils.push_back(makePupil(h, sex, rnd.next(0, musicKinds - 1),
                                       rnd.next(0, sportKinds - 1)));
        }
    }

    shuffle(pupils.begin(), pupils.end());
    return pupils;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        vector<Pupil> pupils = makeCase();
        println((int)pupils.size());
        for (const Pupil& pupil : pupils) {
            println(pupil.h, pupil.sex, pupil.music, pupil.sport);
        }
    }

    return 0;
}
