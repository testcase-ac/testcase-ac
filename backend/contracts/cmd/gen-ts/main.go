package main

import (
	"bytes"
	"flag"
	"fmt"
	"go/ast"
	"go/parser"
	"go/token"
	"log"
	"os"
	"path/filepath"
	"reflect"
	"runtime"
	"strconv"
	"strings"
	"unicode"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

var enumTypes = []string{
	"ErrorType",
	"Language",
	"Operation",
	"CaseProviderType",
	"Verdict",
	"TruncationKind",
	"StressStatus",
}

var structTypes = []reflect.Type{
	reflect.TypeOf(contracts.CaseProvider{}),
	reflect.TypeOf(contracts.StressEvent{}),
	reflect.TypeOf(contracts.OutputTextMetadata{}),
	reflect.TypeOf(contracts.TextWithMetadata{}),
	reflect.TypeOf(contracts.GeneratedBy{}),
	reflect.TypeOf(contracts.Counterexample{}),
	reflect.TypeOf(contracts.ExecutionFailedCase{}),
	reflect.TypeOf(contracts.CorrectCase{}),
	reflect.TypeOf(contracts.EventRecord{}),
	reflect.TypeOf(contracts.StressResult{}),
}

func main() {
	defaultSource, defaultOutput, err := defaultPaths()
	if err != nil {
		log.Fatal(err)
	}

	sourcePath := flag.String("source", defaultSource, "Go contracts source file")
	outputPath := flag.String("out", defaultOutput, "generated TypeScript output file")
	flag.Parse()

	enumValues, err := parseEnumValues(*sourcePath)
	if err != nil {
		log.Fatal(err)
	}

	var out bytes.Buffer
	out.WriteString("// Code generated from backend/contracts. DO NOT EDIT.\n\n")
	for _, typeName := range enumTypes {
		values := enumValues[typeName]
		if len(values) == 0 {
			log.Fatalf("no values found for enum type %s", typeName)
		}
		writeEnum(&out, typeName, values)
	}
	for _, typ := range structTypes {
		writeInterface(&out, typ)
	}

	if err := os.MkdirAll(filepath.Dir(*outputPath), 0755); err != nil {
		log.Fatal(err)
	}
	if err := os.WriteFile(*outputPath, out.Bytes(), 0644); err != nil {
		log.Fatal(err)
	}
}

func defaultPaths() (string, string, error) {
	_, file, _, ok := runtime.Caller(0)
	if !ok {
		return "", "", fmt.Errorf("cannot determine generator path")
	}
	dir := filepath.Dir(file)
	source := filepath.Clean(filepath.Join(dir, "..", "..", "contracts.go"))
	output := filepath.Clean(filepath.Join(dir, "..", "..", "..", "..", "frontend", "src", "generated", "contracts.ts"))
	return source, output, nil
}

func parseEnumValues(sourcePath string) (map[string][]string, error) {
	fileSet := token.NewFileSet()
	parsed, err := parser.ParseFile(fileSet, sourcePath, nil, 0)
	if err != nil {
		return nil, err
	}

	wanted := make(map[string]struct{}, len(enumTypes))
	for _, typeName := range enumTypes {
		wanted[typeName] = struct{}{}
	}

	values := make(map[string][]string, len(enumTypes))
	for _, decl := range parsed.Decls {
		genDecl, ok := decl.(*ast.GenDecl)
		if !ok || genDecl.Tok != token.CONST {
			continue
		}
		for _, spec := range genDecl.Specs {
			valueSpec, ok := spec.(*ast.ValueSpec)
			if !ok {
				continue
			}
			ident, ok := valueSpec.Type.(*ast.Ident)
			if !ok {
				continue
			}
			typeName := ident.Name
			if _, ok := wanted[typeName]; !ok {
				continue
			}
			for i := range valueSpec.Names {
				if i >= len(valueSpec.Values) {
					continue
				}
				lit, ok := valueSpec.Values[i].(*ast.BasicLit)
				if !ok || lit.Kind != token.STRING {
					continue
				}
				value, err := strconv.Unquote(lit.Value)
				if err != nil {
					return nil, err
				}
				values[typeName] = append(values[typeName], value)
			}
		}
	}
	return values, nil
}

func writeEnum(out *bytes.Buffer, typeName string, values []string) {
	fmt.Fprintf(out, "export const %s = [\n", constArrayName(typeName))
	for _, value := range values {
		fmt.Fprintf(out, "  %q,\n", value)
	}
	fmt.Fprintf(out, "] as const;\n\n")
	fmt.Fprintf(out, "export type %s = (typeof %s)[number];\n\n", typeName, constArrayName(typeName))
}

func writeInterface(out *bytes.Buffer, typ reflect.Type) {
	fmt.Fprintf(out, "export interface %s {\n", typ.Name())
	for i := 0; i < typ.NumField(); i++ {
		field := typ.Field(i)
		name, optional, skip := jsonField(field)
		if skip {
			continue
		}
		marker := ":"
		if optional {
			marker = "?:"
		}
		fmt.Fprintf(out, "  %s%s %s;\n", name, marker, tsType(field.Type))
	}
	out.WriteString("}\n\n")
}

func jsonField(field reflect.StructField) (string, bool, bool) {
	tag := field.Tag.Get("json")
	if tag == "-" {
		return "", false, true
	}
	if tag == "" {
		return lowerFirst(field.Name), false, false
	}
	parts := strings.Split(tag, ",")
	if parts[0] == "-" {
		return "", false, true
	}
	name := parts[0]
	if name == "" {
		name = lowerFirst(field.Name)
	}
	optional := false
	for _, part := range parts[1:] {
		if part == "omitempty" {
			optional = true
			break
		}
	}
	return name, optional, false
}

func tsType(typ reflect.Type) string {
	switch typ.Kind() {
	case reflect.Pointer:
		return tsType(typ.Elem()) + " | null"
	case reflect.Slice, reflect.Array:
		return tsType(typ.Elem()) + "[]"
	}
	if typ.PkgPath() == reflect.TypeOf(contracts.StressEvent{}).PkgPath() && typ.Name() != "" {
		return typ.Name()
	}
	switch typ.Kind() {
	case reflect.String:
		return "string"
	case reflect.Bool:
		return "boolean"
	case reflect.Int, reflect.Int8, reflect.Int16, reflect.Int32, reflect.Int64,
		reflect.Uint, reflect.Uint8, reflect.Uint16, reflect.Uint32, reflect.Uint64,
		reflect.Float32, reflect.Float64:
		return "number"
	default:
		log.Fatalf("unsupported Go type %s", typ)
		return "unknown"
	}
}

func constArrayName(typeName string) string {
	var out []rune
	for i, r := range typeName {
		if i > 0 && unicode.IsUpper(r) {
			out = append(out, '_')
		}
		out = append(out, unicode.ToUpper(r))
	}
	return string(out) + "_VALUES"
}

func lowerFirst(value string) string {
	if value == "" {
		return value
	}
	runes := []rune(value)
	runes[0] = unicode.ToLower(runes[0])
	return string(runes)
}
