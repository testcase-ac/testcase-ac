#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

static bool is_shape_char(char c) {
    return c=='C' || c=='R' || c=='W' || c=='S';
}
static bool is_color_char_initial(char c) {
    // initial shapes can be uncolored 'u' too
    return c=='r' || c=='g' || c=='b' || c=='y' || c=='p' || c=='c' || c=='u' || c=='w';
}
static bool is_color_char_painter(char c) {
    // painter cannot paint 'u'
    return c=='r' || c=='g' || c=='b' || c=='y' || c=='p' || c=='c' || c=='w';
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    int N = inf.readInt(1, 10, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10000, "M");
    inf.readEoln();

    // Read initial N shape codes, each one-layer valid code
    for (int i = 1; i <= N; i++) {
        // read a code line with no internal whitespace
        string code = inf.readLine("[^ \\t]+", "shape_code");
        // split by ':'
        vector<string> layers;
        {
            string cur;
            for (char c : code) {
                if (c == ':') {
                    layers.push_back(cur);
                    cur.clear();
                } else {
                    cur.push_back(c);
                }
            }
            layers.push_back(cur);
        }
        // number of layers must be 1 (problem says initial shapes have 1 layer)
        ensuref((int)layers.size() == 1,
                "Initial shape %d: number of layers must be 1, found %d",
                i, (int)layers.size());
        // validate each layer (only one)
        for (int li = 0; li < (int)layers.size(); li++) {
            const string &layer = layers[li];
            ensuref((int)layer.size() == 8,
                    "Initial shape %d, layer %d: length must be 8, found %d",
                    i, li+1, (int)layer.size());
            bool has_piece = false;
            // check each quadrant (2 chars)
            for (int p = 0; p < 8; p += 2) {
                char c1 = layer[p];
                char c2 = layer[p+1];
                if (c1 == '-' && c2 == '-') {
                    // empty quadrant is okay
                } else {
                    has_piece = true;
                    ensuref(is_shape_char(c1),
                            "Initial shape %d, layer %d, cell %d: invalid shape '%c'",
                            i, li+1, p/2+1, c1);
                    ensuref(is_color_char_initial(c2),
                            "Initial shape %d, layer %d, cell %d: invalid color '%c'",
                            i, li+1, p/2+1, c2);
                }
            }
            ensuref(has_piece,
                    "Initial shape %d, layer %d: layer must not be completely empty",
                    i, li+1);
        }
    }

    // Read M operations
    for (int opi = 1; opi <= M; opi++) {
        int t = inf.readInt(1, 4, "op_type");
        if (t == 1) {
            // 1 i j k, j != k
            inf.readSpace();
            int i = inf.readInt(1, 100, "i");
            inf.readSpace();
            int j = inf.readInt(1, 100, "j");
            inf.readSpace();
            int k = inf.readInt(1, 100, "k");
            inf.readEoln();
            ensuref(j != k,
                    "Operation %d (type 1): j and k must differ, both are %d",
                    opi, j);
        } else if (t == 2) {
            // 2 i j k (k in {1,2,3})
            inf.readSpace();
            int i = inf.readInt(1, 100, "i");
            inf.readSpace();
            int j = inf.readInt(1, 100, "j");
            inf.readSpace();
            int k = inf.readInt(1, 3, "rotations");
            inf.readEoln();
        } else if (t == 3) {
            // 3 i j k
            inf.readSpace();
            int i = inf.readInt(1, 100, "i");
            inf.readSpace();
            int j = inf.readInt(1, 100, "j");
            inf.readSpace();
            int k = inf.readInt(1, 100, "k");
            inf.readEoln();
        } else {
            // t == 4
            // 4 i j c where c in {r,g,b,y,p,c,w}
            inf.readSpace();
            int i = inf.readInt(1, 100, "i");
            inf.readSpace();
            int j = inf.readInt(1, 100, "j");
            inf.readSpace();
            string color = inf.readToken("[rgbypcw]", "color");
            inf.readEoln();
            ensuref(color.size() == 1 && is_color_char_painter(color[0]),
                    "Operation %d (type 4): invalid paint color '%s'",
                    opi, color.c_str());
        }
    }

    inf.readEof();
    return 0;
}
