#include <cstdio>

int main(void){
	int ah, am, as, bh, bm, bs;
	scanf("%d : %d : %d", &ah, &am, &as);
	scanf("%d : %d : %d", &bh, &bm, &bs);

  int res = (bh - ah) * 3600 + (bm - am) * 60 + (bs - as);
  printf("%d", res < 0 ? res + 86400 : res);
}
