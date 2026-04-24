import CodeMirror, { EditorView, type Extension } from "@uiw/react-codemirror";
import { cpp } from "@codemirror/lang-cpp";
import { python } from "@codemirror/lang-python";
import { vscodeDark, vscodeLight } from "@uiw/codemirror-theme-vscode";

import { useTheme } from "../lib/theme";

function languageExtension(lang: string): Extension {
  // @codemirror/lang-cpp covers both C and C++ dialects.
  if (lang.startsWith("python") || lang === "pypy3") return python();
  return cpp();
}

interface Props {
  value: string;
  onChange: (value: string) => void;
  language: string;
  height?: string;
}

export default function CodeEditor({ value, onChange, language, height = "360px" }: Props) {
  const { theme } = useTheme();
  return (
    <CodeMirror
      value={value}
      onChange={onChange}
      height={height}
      theme={theme === "dark" ? vscodeDark : vscodeLight}
      extensions={[languageExtension(language), EditorView.lineWrapping]}
      basicSetup={{
        lineNumbers: true,
        highlightActiveLine: true,
        foldGutter: true,
        bracketMatching: true,
        closeBrackets: true,
        autocompletion: true,
        indentOnInput: true,
      }}
      className="code-editor-cm"
    />
  );
}
