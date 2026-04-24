import { describe, expect, it } from "vitest";

import { guessLanguage, resolveDetectedLanguage } from "./languageDetection";

const javaCodes = [
  `public class Main {
  public static void main(String[] args) {
    System.out.println("Hello, World!");
  }
}`,
  `class Main {}`,
];

const pythonCodes = [
  `def hello():
  print("Hello, World!")

if __name__ == "__main__":
  hello()`,
  `print("Hello")`,
  `print("Hello, World!")`,
];

const cppCodes = [
  `#include <iostream>
using namespace std;

int main() {
  cout << "Hello, World!" << endl;
  return 0;
}`,
  `#include <cstdio>
int main() {
  printf("Hello, World!");
  return 0;
}`,
  `#include <iostream>`,
  `void print(const std::string& msg) {
  std::cout << msg << std::endl;
}`,
  `#include<cstdio>
int main() {
  printf("Hello, World!");
  return 0;
}`,
];

const nodejsCodes = [
  `const fs = require('fs');
console.log("Hello, World!");`,
  `console.log("Hello");`,
];

const c11Codes = [
  `#include <stdio.h>
int main() {
  printf("Hello, World!");
  return 0;
}`,
  `#include <stdio.h>`,
  `#include <stdio.h>

int main()
{
    int M;
    scanf("%d", &M);
    while(M--){
        input();
    }

    return 0;
}

void input(){
    // do something..
}`,
];

const csharpCodes = [
  `using System;
class Program {
  static void Main(string[] args) {
    Console.WriteLine("Hello, World!");
  }
}`,
  `using System;
class Program
{
    static void Main()
    {
      var sw = new StreamWriter(Console.OpenStandardOutput());
      sw.WriteLine("Hello, World!");
    }
}`,
  `using System;
using System.IO;
using System.Text;

public class BaekJoon
{
    public static void Main()
    {
        StreamReader sr = new StreamReader(new BufferedStream(Console.OpenStandardInput()));
        StreamWriter sw = new StreamWriter(new BufferedStream(Console.OpenStandardOutput()));
        StringBuilder sb = new StringBuilder();
        sw.Write(sb);
        sw.Flush();
    }
}`,
];

const goCodes = [
  `package main
import "fmt"
func main() {
  fmt.Println("Hello, World!")
}`,
  `package main

import (
    "bufio"
    "fmt"
    "os"
)

var reader *bufio.Reader = bufio.NewReader(os.Stdin)
var writer *bufio.Writer = bufio.NewWriter(os.Stdout)

func main() {
    defer writer.Flush()

    var T int
    fmt.Fscan(reader, &T)
    for i := 0; i < T; i++ {
        var A, B int
        fmt.Fscan(reader, &A, &B)
        fmt.Fprintln(writer, A+B)
    }
}`,
];

const kotlinCodes = [
  `fun main() {
  println("Hello, World!")
}`,
  `fun main(args: Array<String>) {
  val input = readLine()
  println("Hello, World!")
}`,
  `val x = 10
val y = 20
println(x + y)`,
  `import java.util.Scanner

fun main(args: Array<String>) {
    val sc: Scanner = Scanner(System.\`in\`)
    var a = sc.nextInt()
    var b = sc.nextInt()
    if(a == 1)
      a = 0
    println(a+b)
}`,
  `fun main() {
    val br = System.\`in\`.bufferedReader()
    // ..
    print(maxLength)
}`,
];

const rustCodes = [
  `fn main() {
  println!("Hello, World!");
}`,
  `use std::io;

fn main() {
  let mut input = String::new();
  io::stdin().read_line(&mut input).expect("Failed to read line");
  println!("Hello, {}!", input.trim());
}`,
  `let x = 10;
let y = 20;
println!("{}", x + y);`,
  `let mut count = 0;
count += 1;
println!("{}", count);`,
  `println!("Hello");`,
];

const specialCases = [
  { code: "", expected: null, description: "empty input" },
  {
    code: `// This is a comment
/* This is a multi-line comment */`,
    expected: null,
    description: "input with only comments",
  },
];

describe("guessLanguage", () => {
  javaCodes.forEach((code, index) => {
    it(`detects Java correctly (case ${index + 1})`, () => {
      expect(guessLanguage(code)).toBe("java");
    });
  });

  pythonCodes.forEach((code, index) => {
    it(`detects Python correctly (case ${index + 1})`, () => {
      expect(guessLanguage(code)).toBe("python3");
    });
  });

  cppCodes.forEach((code, index) => {
    it(`detects C++ correctly (case ${index + 1})`, () => {
      expect(guessLanguage(code)).toBe("cpp");
    });
  });

  nodejsCodes.forEach((code, index) => {
    it(`detects Node.js correctly (case ${index + 1})`, () => {
      expect(guessLanguage(code)).toBe("nodejs");
    });
  });

  c11Codes.forEach((code, index) => {
    it(`detects C11 correctly (case ${index + 1})`, () => {
      expect(guessLanguage(code)).toBe("c11");
    });
  });

  csharpCodes.forEach((code, index) => {
    it(`detects C# correctly (case ${index + 1})`, () => {
      expect(guessLanguage(code)).toBe("csharp");
    });
  });

  goCodes.forEach((code, index) => {
    it(`detects Go correctly (case ${index + 1})`, () => {
      expect(guessLanguage(code)).toBe("golang");
    });
  });

  kotlinCodes.forEach((code, index) => {
    it(`detects Kotlin correctly (case ${index + 1})`, () => {
      expect(guessLanguage(code)).toBe("kotlin");
    });
  });

  rustCodes.forEach((code, index) => {
    it(`detects Rust correctly (case ${index + 1})`, () => {
      expect(guessLanguage(code)).toBe("rust2021");
    });
  });

  it("does not misclassify C++ print helpers as Python", () => {
    const cppWithPrint = `void print(const std::string& msg) {
  std::cout << msg << std::endl;
}`;
    expect(guessLanguage(cppWithPrint)).not.toBe("python3");
  });

  specialCases.forEach(({ code, expected, description }) => {
    it(`handles ${description}`, () => {
      expect(guessLanguage(code)).toBe(expected);
    });
  });
});

describe("resolveDetectedLanguage", () => {
  it("routes generic C++ detection to the last manual C++ version", () => {
    expect(resolveDetectedLanguage("cpp", "cpp17")).toBe("cpp17");
  });

  it("falls back to cpp23 when there is no remembered C++ version yet", () => {
    expect(resolveDetectedLanguage("cpp", "cpp23")).toBe("cpp23");
  });

  it("passes non-C++ languages through unchanged", () => {
    expect(resolveDetectedLanguage("kotlin", "cpp20")).toBe("kotlin");
  });
});
