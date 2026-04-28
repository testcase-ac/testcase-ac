package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	var n, k int
	fmt.Scan(&n, &k)

	sc := bufio.NewScanner(os.Stdin)
	sc.Split(bufio.ScanLines)
	sc.Scan()
	board := sc.Bytes()

	cnt := 0

	for i, c := range board {
		if c != 'P' {
			continue
		}

		for j := -k; j <= k; j++ {
			if i+j >= 0 && i+j < n && board[i+j] == 'H' {
				cnt++
				board[i+j] = '.'
				break
			}
		}
	}

	fmt.Println(cnt)
}
