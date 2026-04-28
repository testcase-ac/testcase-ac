// 백준 5568 : 카드 놓기
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <iostream>

using namespace std;

int answer = 0;
int n, k; // 카드의 개수 n, 선택할 카드의 개수 k
int *cards = new int[200]; // 카드 번호를 저장
int  *choice = new int[200]; // 선택된 k개의 카드
set<string> s;

// n개의 카드 중 k를 선택하는 함수
void comb(int count, int next) {
	if (count == k) { // k개를 모두 선택 했다면
		// 해당 집합으로 가능한 모든 순열을 구하고 이전에 나온 수와 겹치지 않는다면 set에 삽입
		sort(choice, choice + k);
		do {
			string num = "";
			for (int i = 0; i < k; i++) {
				num += to_string(choice[i]);
			}
			if (s.find(num) == s.end()) s.insert(num);
		} while (next_permutation(choice, choice+k));

		return;
	}

	for (int i = next; i < n; i++) {
		choice[count] = cards[i];
		comb(count + 1, i + 1);
	}
}

int main() {
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> cards[i];
	}

	// n개의 카드 중 k개를 택
	sort(cards, cards + n);
	comb(0, 0);

	// 답안 출력
	answer = s.size();
	cout << answer << endl;
}
