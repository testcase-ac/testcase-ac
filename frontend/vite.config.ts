import path from "node:path";
import fs from "node:fs";
import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";
import tailwindcss from "@tailwindcss/vite";

const siteConfigPath = path.resolve(__dirname, "site-config.json");

// `base` is read at build time so GH Pages deployments can set it to
// "/testcase-ac/" without code changes.
export default defineConfig({
  plugins: [inlineSiteConfig(), react(), tailwindcss()],
  base: process.env.VITE_BASE_PATH ?? "/",
  resolve: {
    alias: {
      "@": path.resolve(__dirname, "./src"),
    },
  },
  server: {
    port: 5173,
  },
  build: {
    // CodeMirror + language packs legitimately push the editor chunk
    // past the default warning threshold.
    chunkSizeWarningLimit: 700,
  },
});

function inlineSiteConfig() {
  return {
    name: "inline-site-config",
    transformIndexHtml() {
      return [
        {
          tag: "script",
          attrs: {
            id: "site-config",
            type: "application/json",
          },
          children: escapeScriptJson(fs.readFileSync(siteConfigPath, "utf8")),
          injectTo: "body-prepend" as const,
        },
      ];
    },
  };
}

function escapeScriptJson(source: string): string {
  return source.replace(/</g, "\\u003c");
}
