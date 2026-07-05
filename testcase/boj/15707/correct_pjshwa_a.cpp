#include <stdio.h>
#include <string.h>
long long a, b, r;
char tmp1[22], tmp2[22];

bool compare(char s[]) {
	int len = strlen(s);
	if (len > 19) return true;
	else if (len < 19) return false;
	else return strcmp(s, "9223372036854775807") > 0;
}
int main() {
	scanf("%21s", tmp1);
	scanf("%21s", tmp2);
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
