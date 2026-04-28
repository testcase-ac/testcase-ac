#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3000;
int A[MAX], B[MAX], C[MAX];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < N; ++i) cin >> B[i];
  for (int i = 0; i < N; ++i) cin >> C[i];

  for (int i = 0; i < N; ++i) {
    if (A[i] == B[i]) continue;

    // Either A brought A[i] or B brought B[i] front.
    {
      vector<int> Ap, Bp;
      for (int j = 0; j < N; j++) {
        if (A[j] != A[i]) Ap.push_back(A[j]);
        if (B[j] != A[i]) Bp.push_back(B[j]);
      }

      int am = A[i], bm = 0, cm = 0;
      for (int j = 0; j < N - 1; j++) {
        if (Ap[j] == Bp[j]) continue;
        bm = Bp[j]; break;
      }

      vector<int> Bpp, Cpp;
      for (int j = 0; j < N; j++) {
        if (B[j] != bm) Bpp.push_back(B[j]);
        if (C[j] != bm) Cpp.push_back(C[j]);
      }

      for (int j = 0; j < N - 1; j++) {
        if (Bpp[j] == Cpp[j]) continue;
        cm = Cpp[j]; break;
      }

      if (am == 0 || bm == 0 || cm == 0) continue;

      vector<int> Appp, Cppp;
      for (int j = 0; j < N; j++) {
        if (A[j] != am && A[j] != cm) Appp.push_back(A[j]);
        if (C[j] != am && C[j] != cm) Cppp.push_back(C[j]);
      }

      // A possible combination
      if (Appp == Cppp) {
        vector<int> Areal, Breal, Creal;
        for (int j = 0; j < N; j++) {
          if (A[j] != am) Areal.push_back(A[j]);
          if (B[j] != bm) Breal.push_back(B[j]);
          if (C[j] != cm) Creal.push_back(C[j]);
        }

        vector<int> adj[N + 1];
        int indegree[N + 1]{};
        for (int j = 0; j < N - 2; j++) {
          adj[Areal[j]].push_back(Areal[j + 1]);
          indegree[Areal[j + 1]]++;

          adj[Breal[j]].push_back(Breal[j + 1]);
          indegree[Breal[j + 1]]++;

          adj[Creal[j]].push_back(Creal[j + 1]);
          indegree[Creal[j + 1]]++;
        }

        queue<int> q;
        for (int j = 1; j <= N; j++) {
          if (indegree[j] == 0) q.push(j);
        }

        while (!q.empty()) {
          int u = q.front(); q.pop();
          cout << u << ' ';
          for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) q.push(v);
          }
        }
        cout << '\n';

        return;
      }
    }

    {
      vector<int> Ap, Bp;
      for (int j = 0; j < N; j++) {
        if (A[j] != B[i]) Ap.push_back(A[j]);
        if (B[j] != B[i]) Bp.push_back(B[j]);
      }

      int am = 0, bm = B[i], cm = 0;
      for (int j = 0; j < N - 1; j++) {
        if (Ap[j] == Bp[j]) continue;
        am = Ap[j]; break;
      }

      vector<int> App, Cpp;
      for (int j = 0; j < N; j++) {
        if (A[j] != am) App.push_back(A[j]);
        if (C[j] != am) Cpp.push_back(C[j]);
      }

      for (int j = 0; j < N - 1; j++) {
        if (App[j] == Cpp[j]) continue;
        cm = Cpp[j]; break;
      }

      if (am == 0 || bm == 0 || cm == 0) continue;

      vector<int> Bppp, Cppp;
      for (int j = 0; j < N; j++) {
        if (B[j] != bm && B[j] != cm) Bppp.push_back(B[j]);
        if (C[j] != bm && C[j] != cm) Cppp.push_back(C[j]);
      }

      // A possible combination
      if (Bppp == Cppp) {
        vector<int> Areal, Breal, Creal;
        for (int j = 0; j < N; j++) {
          if (A[j] != am) Areal.push_back(A[j]);
          if (B[j] != bm) Breal.push_back(B[j]);
          if (C[j] != cm) Creal.push_back(C[j]);
        }

        vector<int> adj[N + 1];
        int indegree[N + 1]{};
        for (int j = 0; j < N - 2; j++) {
          adj[Areal[j]].push_back(Areal[j + 1]);
          indegree[Areal[j + 1]]++;

          adj[Breal[j]].push_back(Breal[j + 1]);
          indegree[Breal[j + 1]]++;

          adj[Creal[j]].push_back(Creal[j + 1]);
          indegree[Creal[j + 1]]++;
        }

        queue<int> q;
        for (int j = 1; j <= N; j++) {2
          if (indegree[j] == 0) q.push(j);
        }

        while (!q.empty()) {
          int u = q.front(); q.pop();
          cout << u << ' ';
          for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) q.push(v);
          }
        }
        cout << '\n';

        return;
      }
    }

  }


}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
