#include "testlib.h"

#include <vector>

using namespace std;

struct Answer {
    int scenes;
};

Answer readAnswer(InStream& stream, int n) {
    const int maxScenes = (1 << n) - 1;
    int scenes = stream.readInt(1, maxScenes, "K");
    vector<char> seen(1 << n, 0);

    int mask = 0;
    for (int i = 0; i <= scenes; ++i) {
        int actor = stream.readInt(1, n, format("move[%d]", i + 1).c_str());
        mask ^= 1 << (actor - 1);

        if (i < scenes) {
            if (mask == 0) {
                stream.quitf(_wa, "scene %d has no actors on stage", i + 1);
            }
            if (seen[mask]) {
                stream.quitf(_wa, "scene %d repeats an earlier actor set", i + 1);
            }
            seen[mask] = 1;
        } else if (mask != 0) {
            stream.quitf(_wa, "stage is not empty after the final move");
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after final move");
    }
    return {scenes};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();

    Answer jury = readAnswer(ans, n);
    Answer participant = readAnswer(ouf, n);

    if (participant.scenes < jury.scenes) {
        quitf(_wa, "jury has more scenes: jury=%d participant=%d", jury.scenes, participant.scenes);
    }
    if (participant.scenes > jury.scenes) {
        quitf(_fail, "participant found more scenes: jury=%d participant=%d", jury.scenes, participant.scenes);
    }
    quitf(_ok, "answer has %d scenes", participant.scenes);
}
