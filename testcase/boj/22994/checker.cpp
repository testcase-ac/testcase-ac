#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int expandedRows, expandedCols;
vector<string> expandedImage;

struct Answer {
    int rows;
    int cols;
    long long area;
};

Answer readAnswer(InStream& stream, TResult invalidVerdict, const char* who) {
    int rows = stream.readInt(1, expandedRows, format("%s n", who).c_str());
    stream.readSpace();
    int cols = stream.readInt(1, expandedCols, format("%s m", who).c_str());
    stream.readEoln();

    if (expandedRows % rows != 0) {
        stream.quitf(invalidVerdict,
                     "%s n=%d does not divide expanded height %d",
                     who,
                     rows,
                     expandedRows);
    }
    if (expandedCols % cols != 0) {
        stream.quitf(invalidVerdict,
                     "%s m=%d does not divide expanded width %d",
                     who,
                     cols,
                     expandedCols);
    }

    int rowScale = expandedRows / rows;
    int colScale = expandedCols / cols;
    string rowPattern = "[a-z]{" + to_string(cols) + "," + to_string(cols) + "}";

    for (int r = 0; r < rows; ++r) {
        string row = stream.readToken(rowPattern, format("%s row[%d]", who, r + 1).c_str());
        stream.readEoln();

        for (int c = 0; c < cols; ++c) {
            char pixel = row[c];
            for (int er = r * rowScale; er < (r + 1) * rowScale; ++er) {
                for (int ec = c * colScale; ec < (c + 1) * colScale; ++ec) {
                    if (expandedImage[er][ec] != pixel) {
                        stream.quitf(invalidVerdict,
                                     "%s pixel (%d,%d)='%c' does not reproduce expanded pixel (%d,%d)='%c'",
                                     who,
                                     r + 1,
                                     c + 1,
                                     pixel,
                                     er + 1,
                                     ec + 1,
                                     expandedImage[er][ec]);
                    }
                }
            }
        }
    }

    stream.readEof();
    return {rows, cols, 1LL * rows * cols};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    expandedRows = inf.readInt();
    expandedCols = inf.readInt();
    expandedImage.resize(expandedRows);
    for (int r = 0; r < expandedRows; ++r) {
        expandedImage[r] = inf.readToken();
    }

    Answer jury = readAnswer(ans, _fail, "jury");
    Answer participant = readAnswer(ouf, _wa, "participant");

    if (participant.area > jury.area) {
        quitf(_wa,
              "participant area %lld is larger than jury area %lld",
              participant.area,
              jury.area);
    }
    if (participant.area < jury.area) {
        quitf(_fail,
              "participant found smaller valid original: participant area %lld, jury area %lld",
              participant.area,
              jury.area);
    }

    quitf(_ok, "valid original image with minimum area %lld", participant.area);
}
