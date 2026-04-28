package main

import (
	"fmt"
)

func main() {
	var a, b, c, ans int
	fmt.Scan(&a, &b, &c)

	if (a&1) == 0 && (b&1) == 0 && (c&1) == 0 {
		ans = a * b * c
	} else {
		ans = 1

		if (a & 1) == 1 {
			ans *= a
		}
		if (b & 1) == 1 {
			ans *= b
		}
		if (c & 1) == 1 {
			ans *= c
		}
	}

	fmt.Println(ans)
}
