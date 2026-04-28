#include <stdio.h>
long long a, b, r;
char tmp1[21], tmp2[21];

bool compare(char s[]) {
	if (s[20]) return true;
	else if (!s[19]) return false;
	else return s > "9223372036854775807";
}
int main() {
	scanf("%s", &tmp1);
	scanf("%s", &tmp2);
	scanf("%lld", &r);

	if (tmp1[0] == '0' || tmp2[0] == '0') printf("0");
	else if (compare(tmp1) || compare(tmp2)) printf("overflow");
	else {
		for (int i = 0; tmp1[i]; i++) {
			a *= 10;
			a += tmp1[i] - 48;
		}
		for (int i = 0; tmp2[i]; i++) {
			b *= 10;
			b += tmp2[i] - 48;
		}
		if (a > (r / b)) printf("overflow");
		else printf("%lld", a * b);
	}

	return 0;
}

