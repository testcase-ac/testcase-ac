import { renderToStaticMarkup } from "react-dom/server";
import { expect, it } from "vitest";

import { I18nProvider } from "@/lib/i18n";
import { PersistentSettingsProvider } from "@/lib/persistentSettings";
import ProblemStatusBadge from "./ProblemStatusBadge";

function renderStatus(runnable: boolean, hasGenerator: boolean, outputOnly: boolean) {
  return renderToStaticMarkup(
    <PersistentSettingsProvider>
      <I18nProvider>
        <ProblemStatusBadge
          runnable={runnable}
          hasGenerator={hasGenerator}
          outputOnly={outputOnly}
        />
      </I18nProvider>
    </PersistentSettingsProvider>,
  );
}

it("shows only the most relevant problem warning", () => {
  expect(renderStatus(true, false, false)).toContain("No Generator");
  expect(renderStatus(true, false, true)).not.toContain("No Generator");
  expect(renderStatus(false, false, false)).toContain("Not Runnable");
  expect(renderStatus(false, false, false)).not.toContain("No Generator");
});
