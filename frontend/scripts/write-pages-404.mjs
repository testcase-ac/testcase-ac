import fs from "node:fs";
import path from "node:path";

function normalizeBasePath(rawBasePath) {
  let basePath = (rawBasePath || "/").trim();
  if (!basePath.startsWith("/")) basePath = `/${basePath}`;
  if (!basePath.endsWith("/")) basePath = `${basePath}/`;
  return basePath;
}

const basePath = normalizeBasePath(process.env.VITE_BASE_PATH);
const outputDir = process.argv[2] || "dist";
const outputPath = path.resolve(process.cwd(), outputDir, "404.html");

const html = `<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>testcase.ac</title>
    <script>
      (function () {
        var basePath = ${JSON.stringify(basePath)};
        var pathname = window.location.pathname;
        var routePath = pathname;

        if (basePath !== "/" && pathname.startsWith(basePath.slice(0, -1))) {
          routePath = pathname.slice(basePath.length - 1) || "/";
        }

        var params = new URLSearchParams();
        params.set("__tc_path", routePath);
        if (window.location.search.length > 1) {
          params.set("__tc_search", window.location.search.slice(1));
        }
        if (window.location.hash.length > 1) {
          params.set("__tc_hash", window.location.hash.slice(1));
        }

        window.location.replace(basePath + "?" + params.toString());
      })();
    </script>
  </head>
  <body></body>
</html>
`;

fs.mkdirSync(path.dirname(outputPath), { recursive: true });
fs.writeFileSync(outputPath, html);
