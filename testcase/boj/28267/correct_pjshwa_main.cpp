#include<vector>
#include<string>
#include "gardened_halved.h"

typedef std::vector<int> int1d;
typedef std::vector<int1d> int2d;
typedef std::string str;

std::vector<int> C;
int it = 0, fn = 0;

void combination(int idx, int cnt1, int cnt2, str& M) {
	if (fn) return;

  if (idx == 0) {
		str U = "";
		for (int e : C) {
			if (e) U += 'R';
			else U += 'U';
		}

		++it;
		if (U == M) fn = 1;
		return;
  }

	C.push_back(0);
	if (cnt1) combination(idx - 1, cnt1 - 1, cnt2, M);
	C.pop_back();

	C.push_back(1);
	if (cnt2) combination(idx - 1, cnt1, cnt2 - 1, M);
	C.pop_back();
}

int goal; str ans;
void combination_backtrack(int idx, int cnt1, int cnt2) {
  if (idx == 0) {
		str U = "";
		for (int e : C) {
			if (e) U += 'R';
			else U += 'U';
		}

		if (++it == goal) ans = U;
  }

	C.push_back(0);
	if (cnt1) combination_backtrack(idx - 1, cnt1 - 1, cnt2);
	C.pop_back();

	C.push_back(1);
	if (cnt2) combination_backtrack(idx - 1, cnt1, cnt2 - 1);
	C.pop_back();
}

int2d grow_tree(int K, str M) {
	int N = M.size() / 2;

	if (K == 1) {
		if (M == "UURR" || M == "URUR") return { {0, 1} };
		if (M == "RRUU" || M == "RURU") return { {1, 0} };
		if (M == "RUUR") return { {0, 0} };
		if (M == "URRU") return { {1, 1} };
	}

	it = fn = 0; C.clear();
	combination(2 * N, N, N, M);

	int Q = N * N, w = 0; int2d V;
	for (int i = 0; i < Q; i++) for (int j = 0; j < Q; j++) {
		if (i == j) continue;
		if (++w == it) {
			V.push_back({ i / N, i % N });
			V.push_back({ j / N, j % N });
			return V;
		}
	}
	return V;
}

str restore_route(int N, int2d T) {
	if (T.size() == 1) {
		if (T[0][0] == 1 && T[0][1] == 0 && T[0][2] == 0) return "RRUU";
		if (T[0][0] == 1 && T[0][1] == 0 && T[0][2] == 1) return "RURU";
		if (T[0][0] == 0 && T[0][1] == 0 && T[0][2] == 0) return "RUUR";
		if (T[0][0] == 0 && T[0][1] == 1 && T[0][2] == 1) return "UURR";
		if (T[0][0] == 0 && T[0][1] == 1 && T[0][2] == 0) return "URUR";
		if (T[0][0] == 1 && T[0][1] == 1 && T[0][2] == 0) return "URRU";
	}

	int Q = N * N, w = 0, f = 0;
	for (int i = 0; i < Q; i++) {
		for (int j = 0; j < Q; j++) {
			if (i == j) continue;

			w++;
			if (i / N == T[0][0] && i % N == T[0][1] && j / N == T[1][0] && j % N == T[1][1]) f = 1;
			if (f) break;
		}
		if (f) break;
	}

	it = fn = 0; goal = w; C.clear();
	combination_backtrack(2 * N, N, N);
	return ans;
}
