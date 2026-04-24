import { createRequire } from "node:module";

const require = createRequire(new URL("../../frontend/package.json", import.meta.url));
const { chromium } = require("playwright");

const frontendUrl = process.env.E2E_FRONTEND_URL;
if (!frontendUrl) {
  throw new Error("E2E_FRONTEND_URL is required");
}

function stage(message) {
  console.log(`[e2e] ${message}`);
}

function pass(message) {
  console.log(`[e2e] PASS - ${message}`);
}

async function assertVisible(page, locator, label, timeout = 30000) {
  try {
    await locator.waitFor({ state: "visible", timeout });
    pass(`${label} is visible`);
  } catch (error) {
    throw new Error(`Expected visible ${label}: ${error.message}`);
  }
}

async function assertUrl(page, pattern, label) {
  await page.waitForURL(pattern);
  pass(`${label}: ${page.url()}`);
}

const browser = await chromium.launch({ headless: true });
try {
  const context = await browser.newContext();
  const page = await context.newPage();

  stage(`open ${frontendUrl}`);
  await page.goto(frontendUrl, { waitUntil: "domcontentloaded" });
  pass(`frontend loaded: ${page.url()}`);

  stage("assert problem list has BOJ 1000");
  const problemLink = page.locator('a[href="/problems/boj/1000"]').first();
  await assertVisible(page, problemLink, "BOJ 1000 problem link");
  await assertVisible(page, page.getByText("A+B").first(), "A+B title");

  stage("click into BOJ 1000");
  await problemLink.click();
  await assertUrl(page, "**/problems/boj/1000", "navigated to BOJ 1000");
  await assertVisible(page, page.getByRole("heading", { name: /1000|A\+B/ }).first(), "problem heading");

  stage("submit placeholder wrong solution");
  await page.locator('button[type="submit"]').click();

  stage("wait for counterexample result");
  await assertVisible(
    page,
    page.getByText(/Counterexample found|반례를 찾았습니다/).first(),
    "counterexample found status",
    180000,
  );
  await assertVisible(page, page.getByText(/Input|입력/).first(), "counterexample input");
  await assertVisible(page, page.getByText(/Your output|내 출력/).first(), "target output");
  await assertVisible(page, page.getByText(/Correct output|정답 출력/).first(), "correct output");

  stage("smoke E2E passed");
} finally {
  await browser.close();
}
