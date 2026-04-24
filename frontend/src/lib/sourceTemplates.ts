import type { LanguageValue } from "../types";

const DEFAULT_CPP_TEMPLATE = `#include <bits/stdc++.h>
using namespace std;

int main() {
    // your solution
    return 0;
}
`;

const DEFAULT_C_TEMPLATE = `#include <stdio.h>

int main(void) {
    // your solution
    return 0;
}
`;

const DEFAULT_PYTHON_TEMPLATE = `import sys

def main():
    data = sys.stdin.read().split()
    # your solution

if __name__ == "__main__":
    main()
`;

const DEFAULT_JAVA_TEMPLATE = `import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // your solution
    }
}
`;

const DEFAULT_NODEJS_TEMPLATE = `const fs = require("fs");
const input = fs.readFileSync(0, "utf8").trim();
// your solution
`;

const DEFAULT_GO_TEMPLATE = `package main

import (
    "bufio"
    "fmt"
    "os"
)

func main() {
    in := bufio.NewReader(os.Stdin)
    _ = in
    fmt.Print("")
}
`;

const DEFAULT_KOTLIN_TEMPLATE = `import java.io.BufferedReader
import java.io.InputStreamReader

fun main() {
    val br = BufferedReader(InputStreamReader(System.\`in\`))
    // your solution
}
`;

const DEFAULT_RUST_TEMPLATE = `use std::io::{self, Read};

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    // your solution
}
`;

const DEFAULT_CSHARP_TEMPLATE = `using System;

var parts = Console.ReadLine()!.Split();
var a = int.Parse(parts[0]);
var b = int.Parse(parts[1]);
Console.WriteLine(a + b);
`;

export function defaultSource(language: LanguageValue): string {
  switch (language) {
    case "c11":
    case "c99":
      return DEFAULT_C_TEMPLATE;
    case "python3":
    case "pypy3":
      return DEFAULT_PYTHON_TEMPLATE;
    case "java":
      return DEFAULT_JAVA_TEMPLATE;
    case "nodejs":
      return DEFAULT_NODEJS_TEMPLATE;
    case "golang":
      return DEFAULT_GO_TEMPLATE;
    case "kotlin":
      return DEFAULT_KOTLIN_TEMPLATE;
    case "rust2021":
      return DEFAULT_RUST_TEMPLATE;
    case "csharp":
      return DEFAULT_CSHARP_TEMPLATE;
    default:
      return DEFAULT_CPP_TEMPLATE;
  }
}
