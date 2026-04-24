#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Disjoint set union
struct DSU {
    vector<int> p, r;
    DSU(int n): p(n), r(n,0) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x]==x?x:p[x]=find(p[x]); }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a==b) return;
        if (r[a]<r[b]) swap(a,b);
        p[b] = a;
        if (r[a]==r[b]) r[a]++;
    }
};

static bool isLetter(char c) { return (c>='a'&&c<='z')||(c>='A'&&c<='Z'); }
static bool isDigit(char c) { return c>='0'&&c<='9'; }

// Parse a formula string s into eqs and neqs (pairs of terms), collecting terms in seenTerms.
// On any parse error, calls stream.quitf(_wa,...) (or _fail if stream is ans).
void parseFormula(const string &s,
                  vector<pair<string,string>> &eqs,
                  vector<pair<string,string>> &neqs,
                  InStream &stream,
                  const unordered_set<string> &allowedTerms = {},
                  bool checkAllowed = false)
{
    size_t pos = 0, n = s.size();
    if (n == 0) stream.quitf(_wa, "empty formula");
    while (pos < n) {
        // parse left operand
        size_t start = pos;
        if (isLetter(s[pos])) {
            while (pos<n && isLetter(s[pos])) pos++;
        } else {
            // integer
            if (s[pos]=='-') {
                pos++;
                if (pos>=n || !isDigit(s[pos]))
                    stream.quitf(_wa, "invalid integer at position %d", int(start));
            }
            if (s[pos]=='0') {
                pos++;
            } else {
                if (!isDigit(s[pos])) stream.quitf(_wa, "invalid integer at position %d", int(start));
                while (pos<n && isDigit(s[pos])) pos++;
            }
        }
        string left = s.substr(start, pos-start);
        // operator
        if (pos+1 >= n) stream.quitf(_wa, "expected operator at position %d", int(pos));
        bool isEq = false;
        if (s[pos]=='=' && s[pos+1]=='=') isEq = true;
        else if (s[pos]=='!' && s[pos+1]=='=') isEq = false;
        else stream.quitf(_wa, "expected '==' or '!=' at position %d", int(pos));
        pos += 2;
        // parse right operand
        start = pos;
        if (pos>=n) stream.quitf(_wa, "missing right operand at position %d", int(pos));
        if (isLetter(s[pos])) {
            while (pos<n && isLetter(s[pos])) pos++;
        } else {
            if (s[pos]=='-') {
                pos++;
                if (pos>=n || !isDigit(s[pos]))
                    stream.quitf(_wa, "invalid integer at position %d", int(start));
            }
            if (s[pos]=='0') {
                pos++;
            } else {
                if (!isDigit(s[pos])) stream.quitf(_wa, "invalid integer at position %d", int(start));
                while (pos<n && isDigit(s[pos])) pos++;
            }
        }
        string right = s.substr(start, pos-start);
        // record
        if (isEq) eqs.emplace_back(left, right);
        else neqs.emplace_back(left, right);
        // optional &&
        if (pos == n) break;
        if (pos+1>=n || s[pos] != '&' || s[pos+1] != '&')
            stream.quitf(_wa, "expected '&&' at position %d", int(pos));
        pos += 2;
    }
    if (eqs.empty() && neqs.empty()) stream.quitf(_wa, "empty formula");
    // check allowed terms if needed
    if (checkAllowed) {
        for (auto &pr : eqs) {
            if (!allowedTerms.count(pr.first))
                stream.quitf(_wa, "unknown term '%s'", pr.first.c_str());
            if (!allowedTerms.count(pr.second))
                stream.quitf(_wa, "unknown term '%s'", pr.second.c_str());
        }
        for (auto &pr : neqs) {
            if (!allowedTerms.count(pr.first))
                stream.quitf(_wa, "unknown term '%s'", pr.first.c_str());
            if (!allowedTerms.count(pr.second))
                stream.quitf(_wa, "unknown term '%s'", pr.second.c_str());
        }
    }
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read original formula
    string S = inf.readToken();
    // Parse it to collect allowed terms
    vector<pair<string,string>> S_eqs, S_neqs;
    unordered_set<string> allowedTerms;
    parseFormula(S, S_eqs, S_neqs, inf /* won't actually quit */);
    // build allowedTerms
    for (auto &pr : S_eqs) {
        allowedTerms.insert(pr.first);
        allowedTerms.insert(pr.second);
    }
    for (auto &pr : S_neqs) {
        allowedTerms.insert(pr.first);
        allowedTerms.insert(pr.second);
    }
    // Map terms to ids
    unordered_map<string,int> termToId;
    termToId.reserve(allowedTerms.size());
    int tid = 0;
    for (auto &t : allowedTerms)
        termToId[t] = tid++;
    int K = tid;
    // Mark constants
    vector<bool> isConst(K, false);
    for (auto &p : termToId) {
        const string &t = p.first;
        int id = p.second;
        if (t[0]=='-' || isDigit(t[0])) isConst[id] = true;
    }

    // Read jury answer
    if (ans.seekEof())
        ans.quitf(_fail, "jury output missing");
    string A = ans.readToken();
    vector<pair<string,string>> A_eqs_s, A_neqs_s;
    parseFormula(A, A_eqs_s, A_neqs_s, ans, allowedTerms, true);
    // Read participant answer
    if (ouf.seekEof())
        ouf.quitf(_wa, "participant output missing");
    string P = ouf.readToken();
    vector<pair<string,string>> P_eqs_s, P_neqs_s;
    parseFormula(P, P_eqs_s, P_neqs_s, ouf, allowedTerms, true);

    // Helper to build closure
    auto buildClosure = [&](const vector<pair<string,string>> &E_s,
                            const vector<pair<string,string>> &N_s,
                            DSU &dsu,
                            bool &sat,
                            set<pair<int,int>> &diseqs)
    {
        // equality unions
        for (auto &pr : E_s) {
            int u = termToId.at(pr.first);
            int v = termToId.at(pr.second);
            dsu.unite(u, v);
        }
        // constant conflict check
        sat = true;
        unordered_map<int,string> rootConst;
        for (int u = 0; u < K; u++) if (isConst[u]) {
            int ru = dsu.find(u);
            auto it = rootConst.find(ru);
            string sval = "";
            for (auto &pp : termToId) {
                if (pp.second == u) { sval = pp.first; break; }
            }
            if (it == rootConst.end()) {
                rootConst[ru] = sval;
            } else if (it->second != sval) {
                sat = false;
                return;
            }
        }
        // inequalities
        for (auto &pr : N_s) {
            int u = termToId.at(pr.first);
            int v = termToId.at(pr.second);
            int ru = dsu.find(u), rv = dsu.find(v);
            if (ru == rv) {
                sat = false;
                return;
            }
            if (ru > rv) swap(ru, rv);
            diseqs.emplace(ru, rv);
        }
    };

    // Build closures
    DSU dsuA(K), dsuP(K);
    bool satA=true, satP=true;
    set<pair<int,int>> deA, deP;
    buildClosure(A_eqs_s, A_neqs_s, dsuA, satA, deA);
    buildClosure(P_eqs_s, P_neqs_s, dsuP, satP, deP);

    // Compare satisfiability
    if (!satA) {
        if (!satP) quitf(_ok, "both unsatisfiable");
        else ouf.quitf(_wa, "expected unsatisfiable, found satisfiable");
    } else {
        if (!satP) ouf.quitf(_wa, "expected satisfiable, found unsatisfiable");
    }
    // Both satisfiable: compare partitions
    // Check partition equality
    unordered_map<int,int> mapAtoP, mapPtoA;
    for (int u = 0; u < K; u++) {
        int a = dsuA.find(u), p = dsuP.find(u);
        auto it = mapAtoP.find(a);
        if (it == mapAtoP.end()) mapAtoP[a] = p;
        else if (it->second != p) ouf.quitf(_wa, "difference in equality closure");
        auto it2 = mapPtoA.find(p);
        if (it2 == mapPtoA.end()) mapPtoA[p] = a;
        else if (it2->second != a) ouf.quitf(_wa, "difference in equality closure");
    }
    // Build canonical class ids (minimal term id in class)
    vector<int> canon(K);
    {
        unordered_map<int,int> r2min;
        for (int u = 0; u < K; u++) {
            int r = dsuA.find(u);
            auto it = r2min.find(r);
            if (it == r2min.end() || u < it->second)
                r2min[r] = u;
        }
        for (int u = 0; u < K; u++)
            canon[u] = r2min[dsuA.find(u)];
    }
    // Canonical disequalities
    set<pair<int,int>> cdA, cdP;
    for (auto &pr : deA) {
        int u = pr.first, v = pr.second;
        int cu = canon[u], cv = canon[v];
        if (cu > cv) swap(cu, cv);
        cdA.emplace(cu, cv);
    }
    for (auto &pr : deP) {
        int u = pr.first, v = pr.second;
        int cu = canon[mapPtoA[pr.first]], cv = canon[mapPtoA[pr.second]];
        // Actually, better to use dsuP but we remapped to A labels: easier is to
        // for each diseq (r1,r2) in dsuP, find minimal member in that class via P DSU
        // but since partitions identical, we can use canon array on equivalent A DSU
        cu = canon[dsuP.find(pr.first)];
        cv = canon[dsuP.find(pr.second)];
        if (cu > cv) swap(cu, cv);
        cdP.emplace(cu, cv);
    }
    // Compare diseq sets
    if (cdA != cdP) ouf.quitf(_wa, "difference in inequality closure");

    quitf(_ok, "formulas equivalent");
    return 0;
}
