import type { CppLanguageValue, LanguageValue } from "../types";

export type GuessedLanguage =
  | "java"
  | "cpp"
  | "c11"
  | "python3"
  | "nodejs"
  | "csharp"
  | "golang"
  | "kotlin"
  | "rust2021";

export function resolveDetectedLanguage(
  guessedLanguage: GuessedLanguage,
  lastManualCppLanguage: CppLanguageValue,
): LanguageValue {
  if (guessedLanguage === "cpp") {
    return lastManualCppLanguage;
  }
  return guessedLanguage;
}

// Directly migrated from ../testcase-ac/src/lib/utils.ts and patched to match
// this app's current language set.
export function guessLanguage(sourceCode: string): GuessedLanguage | null {
  // Check for Java first (distinct class/main method patterns)
  const javaClassRegex = /public\s+class\s+\w+\s*\{/;
  const javaMainRegex = /public\s+static\s+void\s+main\s*\(String\[\]\s+args\)\s*\{/;
  const hasJavaPattern =
    javaClassRegex.test(sourceCode) || javaMainRegex.test(sourceCode) || sourceCode.includes("System.out.println");

  if (hasJavaPattern && !sourceCode.includes("using System")) {
    return "java";
  }

  // Check for C++ before Python to prioritize namespace/headers
  const cppIncludeRegex = /#include\s*<(iostream|vector|map|string|cstdio)>/;
  const cppStreamOps = /(cout|cin)\s*(<<|>>)/;
  if (
    cppIncludeRegex.test(sourceCode) ||
    /using\s+namespace\s+std;/.test(sourceCode) ||
    cppStreamOps.test(sourceCode)
  ) {
    return "cpp";
  }

  // C11 check (strict C headers)
  if (/#include\s*<(stdio|stdlib|string|math)\.h>/.test(sourceCode) || /(printf|scanf)\s*\(/.test(sourceCode)) {
    return "c11";
  }

  // Enhanced Python check (avoids C++ function false positives)
  const pythonPrintRegex = /(^|[^\w.])print\(/;
  const simpleKotlinTest = /System|java/;
  const pythonFeatures = [
    /def\s+\w+\(.*\)\s*:/,
    /import\s+(?!java\b)\w+/,
    /from\s+\w+\s+import/,
    /if\s+__name__\s*==\s*['"]__main__['"]\s*:/,
    /except\s+\w+\s*:/,
    /elif\s+/,
  ];

  const hasPythonPrint = pythonPrintRegex.test(sourceCode);
  const hasOtherPythonFeatures = pythonFeatures.some((re) => re.test(sourceCode));
  const seemsLikeKotlin = simpleKotlinTest.test(sourceCode);

  if ((hasPythonPrint && !seemsLikeKotlin) || hasOtherPythonFeatures) {
    return "python3";
  }

  // Node.js check (console.log + module patterns)
  if (
    /console\.log\(/.test(sourceCode) ||
    /require\(['"]\w+['"]\)/.test(sourceCode) ||
    /module\.exports/.test(sourceCode)
  ) {
    return "nodejs";
  }

  if (
    sourceCode.includes("Console.WriteLine") ||
    sourceCode.includes("new StreamWriter(Console.OpenStandardOutput())") ||
    sourceCode.includes("using System;")
  ) {
    return "csharp";
  }

  if (sourceCode.includes("fmt.Println") || sourceCode.includes("fmt.Fscan") || sourceCode.includes("fmt.Fprintln")) {
    return "golang";
  }

  // Check for Rust patterns
  if (
    /fn\s+main\s*\(/.test(sourceCode) ||
    sourceCode.includes("println!(") ||
    /let\s+\w+\s*=/.test(sourceCode) ||
    /let\s+mut\s+\w+\s*=/.test(sourceCode) ||
    sourceCode.includes("std::io::stdin()") ||
    /use\s+std::/.test(sourceCode)
  ) {
    return "rust2021";
  }

  const simpleJavaRegex = /class\s+Main\s+/;
  if (simpleJavaRegex.test(sourceCode)) {
    return "java";
  }

  const kotlinFunMain = /fun\s+main\s*\(/.test(sourceCode);
  const kotlinReadLine = sourceCode.includes("readLine()");
  const kotlinVal = /val\s+\w+/.test(sourceCode);
  const kotlinImport = /import\s+java\./.test(sourceCode);

  if (kotlinFunMain || kotlinReadLine || kotlinVal || kotlinImport) {
    return "kotlin";
  }

  return null;
}
