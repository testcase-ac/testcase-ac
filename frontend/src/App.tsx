import { Languages, Moon, Sun } from "lucide-react";
import { Link, Outlet } from "react-router-dom";

import { Button } from "@/components/ui/button";
import {
  DropdownMenu,
  DropdownMenuContent,
  DropdownMenuRadioGroup,
  DropdownMenuRadioItem,
  DropdownMenuTrigger,
} from "@/components/ui/dropdown-menu";
import { useI18n } from "./lib/i18n";
import { useTheme } from "./lib/theme";

export default function App() {
  const { t } = useI18n();
  return (
    <div className="min-h-screen bg-background text-foreground">
      <header className="border-b bg-background/95">
        <div className="container flex flex-wrap items-center gap-x-3 gap-y-2 py-5">
          <Link to="/" className="text-2xl font-semibold text-foreground hover:no-underline">
            {t("app.title")}
          </Link>
          <div className="ml-auto flex items-center gap-2">
            <LanguageSelect />
            <ThemeToggle />
          </div>
        </div>
      </header>
      <main className="container py-8">
        <Outlet />
      </main>
      <footer className="container border-t py-6 text-center text-sm text-muted-foreground">
        {t("app.footer.openSource")}{" "}
        <a
          href={import.meta.env.VITE_GITHUB_REPO_URL ?? "https://github.com"}
          target="_blank"
          rel="noreferrer"
        >
          {t("app.footer.github")}
        </a>
      </footer>
    </div>
  );
}

function ThemeToggle() {
  const { theme, toggleTheme } = useTheme();
  const { t } = useI18n();
  const label = theme === "light" ? t("theme.toggle.toDark") : t("theme.toggle.toLight");
  return (
    <Button
      type="button"
      variant="ghost"
      size="icon"
      aria-label={label}
      title={label}
      onClick={toggleTheme}
    >
      {theme === "light" ? <Moon /> : <Sun />}
    </Button>
  );
}

function LanguageSelect() {
  const { locale, setLocale, t } = useI18n();
  const shortLabel = locale === "ko" ? "KR" : "EN";

  return (
    <DropdownMenu>
      <DropdownMenuTrigger asChild>
        <Button
          type="button"
          variant="ghost"
          size="sm"
          aria-label={t("language.toggle.label")}
          title={t("language.toggle.label")}
          className="h-9 gap-1 px-2 text-xs font-medium"
        >
          <Languages className="h-4 w-4 shrink-0 text-muted-foreground" />
          <span className="uppercase">{shortLabel}</span>
        </Button>
      </DropdownMenuTrigger>
      <DropdownMenuContent align="end">
        <DropdownMenuRadioGroup
          value={locale}
          onValueChange={(value) => setLocale(value === "ko" ? "ko" : "en")}
        >
          <DropdownMenuRadioItem value="en">{t("language.option.en")}</DropdownMenuRadioItem>
          <DropdownMenuRadioItem value="ko">{t("language.option.ko")}</DropdownMenuRadioItem>
        </DropdownMenuRadioGroup>
      </DropdownMenuContent>
    </DropdownMenu>
  );
}
