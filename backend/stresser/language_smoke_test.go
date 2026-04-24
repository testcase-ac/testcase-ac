package main

import "github.com/testcase-ac/testcase-ac/backend/contracts"

type languageSmokeCase struct {
	Name                string
	Lang                contracts.Language
	Program             string
	Singlegen           string
	Input               string
	Want                string
	RequiredExecutables []string
	RequiredPaths       []string
}

func supportedLanguageSmokeCases() []languageSmokeCase {
	cppProgram := `#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    cout << a + b << "\n";
    return 0;
}
`
	cProgram := `#include <stdio.h>

int main(void) {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", a + b);
    return 0;
}
`
	pythonProgram := `a, b = map(int, input().split())
print(a + b)
`
	javaProgram := `import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int a = Integer.parseInt(st.nextToken());
        int b = Integer.parseInt(st.nextToken());
        System.out.println(a + b);
    }
}
`
	nodeProgram := `const fs = require("fs");
const tokens = fs.readFileSync(0, "utf8").trim().split(/\s+/);
const a = Number(tokens[0] || 0);
const b = Number(tokens[1] || 0);
console.log(a + b);
`
	goProgram := `package main

import "fmt"

func main() {
    var a, b int
    fmt.Scan(&a, &b)
    fmt.Println(a + b)
}
`
	kotlinProgram := `import java.util.StringTokenizer

fun main() {
    val st = StringTokenizer(readln())
    val a = st.nextToken().toInt()
    val b = st.nextToken().toInt()
    println(a + b)
}
`
	rustProgram := `use std::io::{self, Read};

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();
    let a: i32 = it.next().unwrap().parse().unwrap();
    let b: i32 = it.next().unwrap().parse().unwrap();
    println!("{}", a + b);
}
`
	csharpProgram := `using System;

var parts = Console.ReadLine()!.Split();
var a = int.Parse(parts[0]);
var b = int.Parse(parts[1]);
Console.WriteLine(a + b);
`
	cppSinglegen := `#include <iostream>
int main() {
    std::cout << "1 2\n";
    return 0;
}
`
	cSinglegen := `#include <stdio.h>

int main(void) {
    printf("1 2\n");
    return 0;
}
`
	pythonSinglegen := `print("1 2")`
	javaSinglegen := `public class Main {
    public static void main(String[] args) {
        System.out.println("1 2");
    }
}
`
	nodeSinglegen := `console.log("1 2");`
	goSinglegen := `package main

import "fmt"

func main() {
    fmt.Println("1 2")
}
`
	kotlinSinglegen := `fun main() {
    println("1 2")
}
	`
	rustSinglegen := `fn main() {
    println!("1 2");
}
`
	csharpSinglegen := `using System;

Console.WriteLine("1 2");
`

	return []languageSmokeCase{
		{Name: "cpp23", Lang: contracts.LanguageCpp23, Program: cppProgram, Singlegen: cppSinglegen, Input: "1 2\n", Want: "3", RequiredExecutables: []string{"g++"}},
		{Name: "cpp20", Lang: contracts.LanguageCpp20, Program: cppProgram, Singlegen: cppSinglegen, Input: "1 2\n", Want: "3", RequiredExecutables: []string{"g++"}},
		{Name: "cpp17", Lang: contracts.LanguageCpp17, Program: cppProgram, Singlegen: cppSinglegen, Input: "1 2\n", Want: "3", RequiredExecutables: []string{"g++"}},
		{Name: "cpp14", Lang: contracts.LanguageCpp14, Program: cppProgram, Singlegen: cppSinglegen, Input: "1 2\n", Want: "3", RequiredExecutables: []string{"g++"}},
		{Name: "c11", Lang: contracts.LanguageC11, Program: cProgram, Singlegen: cSinglegen, Input: "1 2\n", Want: "3", RequiredExecutables: []string{"gcc"}},
		{Name: "c99", Lang: contracts.LanguageC99, Program: cProgram, Singlegen: cSinglegen, Input: "1 2\n", Want: "3", RequiredExecutables: []string{"gcc"}},
		{Name: "python3", Lang: contracts.LanguagePython3, Program: pythonProgram, Singlegen: pythonSinglegen, Input: "1 2\n", Want: "3", RequiredExecutables: []string{python313Command}},
		{Name: "pypy3", Lang: contracts.LanguagePyPy3, Program: pythonProgram, Singlegen: pythonSinglegen, Input: "1 2\n", Want: "3", RequiredExecutables: []string{"pypy3"}},
		{Name: "java", Lang: contracts.LanguageJava, Program: javaProgram, Singlegen: javaSinglegen, Input: "1 2\n", Want: "3", RequiredExecutables: []string{"javac", "java"}},
		{Name: "nodejs", Lang: contracts.LanguageNodeJS, Program: nodeProgram, Singlegen: nodeSinglegen, Input: "1 2\n", Want: "3", RequiredExecutables: []string{"node"}},
		{Name: "golang", Lang: contracts.LanguageGolang, Program: goProgram, Singlegen: goSinglegen, Input: "1 2\n", Want: "3", RequiredExecutables: []string{"go"}},
		{Name: "kotlin", Lang: contracts.LanguageKotlin, Program: kotlinProgram, Singlegen: kotlinSinglegen, Input: "1 2\n", Want: "3", RequiredExecutables: []string{"kotlinc-jvm", "java"}},
		{Name: "rust2021", Lang: contracts.LanguageRust2021, Program: rustProgram, Singlegen: rustSinglegen, Input: "1 2\n", Want: "3", RequiredExecutables: []string{"rustc"}},
		{Name: "csharp", Lang: contracts.LanguageCSharp, Program: csharpProgram, Singlegen: csharpSinglegen, Input: "1 2\n", Want: "3", RequiredExecutables: []string{"dotnet"}, RequiredPaths: []string{"/var/task/CsharpApp"}},
	}
}
