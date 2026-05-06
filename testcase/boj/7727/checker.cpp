//GPT 코드
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// s1에 대해 s2가 subsequence인지 검사
bool is_subsequence(const string& s, const string& sub) {
	int i = 0;
	for (char c : s) {
		if (i < (int)sub.size() && c == sub[i]) ++i;
	}
	return i == (int)sub.size();
}

int main(int argc, char* argv[]) {
	registerTestlibCmd(argc, argv);
    int n=inf.readInt();
    int m=inf.readInt();
	string a = inf.readToken(); // 입력 문자열 1
	string b = inf.readToken(); // 입력 문자열 2

	int expected_len = ans.readInt();       // 정답: LCS 길이
	string expected_lcs = ans.readLine();   // 정답: LCS 문자열 (쓰진 않음)

	int user_len = ouf.readInt();           // 참가자 출력: LCS 길이
	string user_lcs;
	if (ouf.seekEof()) {
		// 두 번째 줄 없이 끝났음
		user_lcs = "";
	} else {
		user_lcs = ouf.readLine();         // 참가자 출력: LCS 문자열
	}

	// 길이와 내용이 일치해야 함
	if ((int)user_lcs.size() != user_len)
		quitf(_wa, "Length mismatch: declared %d but string has length %d", user_len, (int)user_lcs.size());

	if (user_len != expected_len)
		quitf(_wa, "Incorrect LCS length: expected %d, found %d", expected_len, user_len);

	// 알파벳 소문자 이외 문자 포함시
	for (char c : user_lcs)
		if (c < 'a' || c > 'z')
			quitf(_wa, "Invalid character in LCS string: %c", c);

	if (!is_subsequence(a, user_lcs))
		quitf(_wa, "Output is not a subsequence of first input string");

	if (!is_subsequence(b, user_lcs))
		quitf(_wa, "Output is not a subsequence of second input string");

	quitf(_ok, "Correct LCS of length %d", user_len);
}
