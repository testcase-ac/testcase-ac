// Command build-author-index materializes testcase Git attribution for backend startup.
package main

import (
	"flag"
	"fmt"
	"os"
	"strings"

	"github.com/testcase-ac/testcase-ac/backend/internal/authorindex"
)

func main() {
	repoRoot := flag.String("repo-root", "", "path to the repository root")
	outputPath := flag.String("output", "", "path to write the author index JSON")
	flag.Parse()

	if strings.TrimSpace(*repoRoot) == "" || strings.TrimSpace(*outputPath) == "" {
		fmt.Fprintln(os.Stderr, "usage: build-author-index -repo-root <repo-root> -output <output>")
		os.Exit(2)
	}

	index, err := authorindex.Build(*repoRoot)
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
	if err := authorindex.WriteFile(*outputPath, index); err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
}
