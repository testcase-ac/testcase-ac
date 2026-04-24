import path from "node:path";
import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";
import tailwindcss from "@tailwindcss/vite";

// `base` is read at build time so GH Pages deployments can set it to
// "/testcase-ac/" without code changes.
export default defineConfig({
  plugins: [react(), tailwindcss()],
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
