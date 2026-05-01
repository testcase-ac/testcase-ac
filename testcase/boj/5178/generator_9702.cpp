#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int K = rnd.next(3, 5);
    println(K);

    vector<int> baseTypes = {0, 1, 4};
    vector<int> otherTypes = {2, 3, 5, 6, 7, 8};

    for (int tc = 0; tc < K; ++tc) {
        int type;
        if (tc < (int)baseTypes.size())
            type = baseTypes[tc];
        else
            type = rnd.any(otherTypes);

        vector<string> prg;

        switch (type) {
            // Type 0: complexity 0 (only empty loops)
            case 0: {
                int depth = rnd.next(1, 3);
                vector<string> args = {"x", "y", "2", "3", "4"};
                for (int i = 0; i < depth; ++i) {
                    prg.push_back("loop " + rnd.any(args));
                }
                for (int i = 0; i < depth; ++i) {
                    prg.push_back("endloop");
                }
                prg.push_back("endprogram");
                break;
            }
            // Type 1: O(1) programs (only constants)
            case 1: {
                if (rnd.next(0, 1) == 0) {
                    int cntBasic = rnd.next(1, 3);
                    for (int i = 0; i < cntBasic; ++i)
                        prg.push_back("basic");
                    prg.push_back("endprogram");
                } else {
                    int depth = rnd.next(1, 2);
                    for (int i = 0; i < depth; ++i) {
                        int c = rnd.next(2, 5);
                        prg.push_back("loop " + to_string(c));
                    }
                    int cntBasic = rnd.next(1, 2);
                    for (int i = 0; i < cntBasic; ++i)
                        prg.push_back("basic");
                    for (int i = 0; i < depth; ++i)
                        prg.push_back("endloop");
                    if (rnd.next(0, 1))
                        prg.push_back("basic");
                    prg.push_back("endprogram");
                }
                break;
            }
            // Type 2: single monomial x^a y^b (with some constant loops)
            case 2: {
                int a, b;
                do {
                    a = rnd.next(0, 2); // exponent of x
                    b = rnd.next(0, 2); // exponent of y
                } while (a + b == 0 || a + b > 3);
                int d = rnd.next(0, 1); // number of constant loops

                vector<char> layers;
                for (int i = 0; i < a; ++i) layers.push_back('x');
                for (int i = 0; i < b; ++i) layers.push_back('y');
                for (int i = 0; i < d; ++i) layers.push_back('c');
                shuffle(layers.begin(), layers.end());

                for (char ch : layers) {
                    if (ch == 'x') prg.push_back("loop x");
                    else if (ch == 'y') prg.push_back("loop y");
                    else {
                        int c = rnd.next(2, 5);
                        prg.push_back("loop " + to_string(c));
                    }
                }

                int basicsNum = rnd.next(1, 2);
                for (int i = 0; i < basicsNum; ++i)
                    prg.push_back("basic");

                for (size_t i = 0; i < layers.size(); ++i)
                    prg.push_back("endloop");

                if (rnd.next(0, 1))
                    prg.push_back("basic"); // outside loops: constant term

                prg.push_back("endprogram");
                break;
            }
            // Type 3: sum of two monomials (e.g., x + y, x^2 + y^2)
            case 3: {
                auto makeVarBlock = [&](string v) -> vector<string> {
                    vector<string> b;
                    if (rnd.next(0, 1)) { // optional constant wrapper
                        int c = rnd.next(2, 5);
                        b.push_back("loop " + to_string(c));
                        b.push_back("loop " + v);
                        b.push_back("basic");
                        b.push_back("endloop");
                        b.push_back("endloop");
                    } else {
                        b.push_back("loop " + v);
                        b.push_back("basic");
                        b.push_back("endloop");
                    }
                    return b;
                };

                auto makeQuadBlock = [&](string v) -> vector<string> {
                    vector<string> b;
                    b.push_back("loop " + v);
                    b.push_back("loop " + v);
                    b.push_back("basic");
                    b.push_back("endloop");
                    b.push_back("endloop");
                    return b;
                };

                if (rnd.next(0, 1) == 0) {
                    // x + y
                    string v1 = "x", v2 = "y";
                    if (rnd.next(0, 1)) swap(v1, v2);
                    vector<vector<string>> blocks;
                    blocks.push_back(makeVarBlock(v1));
                    blocks.push_back(makeVarBlock(v2));
                    if (rnd.next(0, 1)) swap(blocks[0], blocks[1]);
                    for (auto &b : blocks)
                        for (auto &s : b)
                            prg.push_back(s);
                } else {
                    // x^2 + y^2
                    string v1 = "x", v2 = "y";
                    if (rnd.next(0, 1)) swap(v1, v2);
                    vector<string> b1 = makeQuadBlock(v1);
                    vector<string> b2 = makeQuadBlock(v2);
                    if (rnd.next(0, 1)) {
                        for (auto &s : b1) prg.push_back(s);
                        for (auto &s : b2) prg.push_back(s);
                    } else {
                        for (auto &s : b2) prg.push_back(s);
                        for (auto &s : b1) prg.push_back(s);
                    }
                }
                prg.push_back("endprogram");
                break;
            }
            // Type 4: x^2 + xy + y^2 (tests mixed-term simplification)
            case 4: {
                prg.push_back("loop x");
                prg.push_back("loop x");
                prg.push_back("basic");
                prg.push_back("endloop");
                prg.push_back("endloop");

                prg.push_back("loop x");
                prg.push_back("loop y");
                prg.push_back("basic");
                prg.push_back("endloop");
                prg.push_back("endloop");

                prg.push_back("loop y");
                prg.push_back("loop y");
                prg.push_back("basic");
                prg.push_back("endloop");
                prg.push_back("endloop");

                prg.push_back("endprogram");
                break;
            }
            // Type 5: empty loops then basics outside (O(1), tests empty-loop handling)
            case 5: {
                string v1 = rnd.next(0, 1) ? "x" : "y";
                string v2 = (v1 == "x" ? "y" : "x");

                prg.push_back("loop " + v1);
                bool nestSecond = (rnd.next(0, 1) == 1);
                if (nestSecond) {
                    prg.push_back("loop " + v2);
                    if (rnd.next(0, 1)) {
                        int c = rnd.next(2, 4);
                        prg.push_back("loop " + to_string(c));
                        prg.push_back("endloop");
                    }
                    prg.push_back("endloop"); // closes v2
                }
                prg.push_back("endloop"); // closes v1

                int nb = rnd.next(1, 2);
                for (int i = 0; i < nb; ++i)
                    prg.push_back("basic");
                prg.push_back("endprogram");
                break;
            }
            // Type 6: mix of non-empty and empty loops
            case 6: {
                string vx = "x", vy = "y";
                if (rnd.next(0, 1)) swap(vx, vy);
                bool constWrap = (rnd.next(0, 1) == 1);

                prg.push_back("loop " + vx);
                if (constWrap) {
                    int c = rnd.next(2, 5);
                    prg.push_back("loop " + to_string(c));
                }

                prg.push_back("loop " + vy);
                prg.push_back("basic");
                prg.push_back("endloop"); // closes vy with basic

                prg.push_back("loop " + vy);
                prg.push_back("endloop"); // empty vy loop

                if (constWrap)
                    prg.push_back("endloop"); // closes const

                prg.push_back("endloop"); // closes vx
                prg.push_back("endprogram");
                break;
            }
            // Type 7: constant * variable loop + empty variable loop
            case 7: {
                string var1 = rnd.next(0, 1) ? "x" : "y";
                string var2 = (var1 == "x" ? "y" : "x");

                int c1 = rnd.next(2, 5);
                prg.push_back("loop " + to_string(c1));
                prg.push_back("loop " + var1);
                int bcnt = rnd.next(1, 2);
                for (int i = 0; i < bcnt; ++i)
                    prg.push_back("basic");
                prg.push_back("endloop");
                prg.push_back("endloop");

                prg.push_back("loop " + var2);
                int c2 = rnd.next(2, 5);
                prg.push_back("loop " + to_string(c2));
                prg.push_back("endloop");
                prg.push_back("endloop");

                prg.push_back("endprogram");
                break;
            }
            // Type 8: dominated term from nested loops (e.g., x + x^2 or x + xy)
            case 8: {
                string outer = rnd.next(0, 1) ? "x" : "y";
                string innerSame = outer;
                string innerCross = (outer == "x" ? "y" : "x");
                bool same = (rnd.next(0, 1) == 0);
                string inner = same ? innerSame : innerCross;

                prg.push_back("loop " + outer);
                prg.push_back("basic");
                prg.push_back("loop " + inner);
                prg.push_back("basic");
                prg.push_back("endloop");
                prg.push_back("endloop");
                prg.push_back("endprogram");
                break;
            }
        }

        for (string &s : prg)
            println(s);
        if (tc + 1 < K)
            printf("\n");
    }

    return 0;
}
