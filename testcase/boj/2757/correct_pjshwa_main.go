package main

import (
	"bufio"
	"fmt"
	"os"
)

var arr [7]int

func init() {
	a := 1
	for i := 0; i < 7; i++ {
		arr[i] = a
		a *= 26
	}
}

func main() {
	sc := bufio.NewScanner(os.Stdin)
	sc.Split(bufio.ScanLines)
	for {
		sc.Scan()
		line := sc.Bytes()
		flag := 0
		R := ""
		C := 0
		for _, c := range line {
			if c == 'R' || c == 'C' {
				flag++
				continue
			}
			if flag == 1 {
				R += string(c)
			} else {
				C *= 10
				C += int(c - '0')
			}
		}
		if C == 0 {
			break
		}
		st := make([]byte, 0)
		num := 0
		for i := 0; i < 7; i++ {
			num += arr[i]
			if C > num-1 {
				st = append(st, byte(65+((C-num)/arr[i])%26))
			} else {
				break
			}
		}
		for i := len(st) - 1; i >= 0; i-- {
			fmt.Printf("%c", st[i])
		}
		fmt.Println(R)
	}
}
