import { Languages, Menu, Moon, Sun } from "lucide-react";
import { Link, Outlet } from "react-router-dom";

import { Button } from "@/components/ui/button";
import SiteBanner from "@/components/SiteBanner";
import {
  DropdownMenu,
  DropdownMenuContent,
  DropdownMenuItem,
  DropdownMenuLabel,
  DropdownMenuRadioGroup,
  DropdownMenuRadioItem,
  DropdownMenuSeparator,
  DropdownMenuTrigger,
} from "@/components/ui/dropdown-menu";
import { useI18n } from "./lib/i18n";
import { useTheme } from "./lib/theme";

const githubUrl = import.meta.env.VITE_GITHUB_REPO_URL ?? "https://github.com";

export default function App() {
  const { t } = useI18n();
  return (
    <div className="min-h-screen bg-background text-foreground">
      <header className="border-b bg-background/95">
        <div className="container flex flex-nowrap items-center gap-x-1 py-3 sm:gap-x-3">
          <Link to="/" className="text-lg font-semibold text-foreground hover:no-underline sm:-translate-y-px sm:text-xl">
            {t("app.title")}
          </Link>
          <nav className="hidden items-center sm:flex">
            <Button asChild variant="ghost" size="sm" className="h-9 px-3 text-foreground hover:no-underline">
              <Link to="/stats">{t("nav.stats")}</Link>
            </Button>
            <Button asChild variant="ghost" size="sm" className="h-9 px-3 text-foreground hover:no-underline">
              <a href="https://help.testcase.ac" target="_blank" rel="noreferrer">
                {t("nav.help")}
              </a>
            </Button>
          </nav>
          <div className="ml-auto hidden items-center gap-2 sm:flex">
            <Button asChild variant="ghost" size="sm" className="h-9 text-foreground hover:no-underline">
              <a href={githubUrl} target="_blank" rel="noreferrer">
                <GitHubIcon />
                GitHub
              </a>
            </Button>
            <LanguageSelect />
            <ThemeToggle />
          </div>
          <MobileMenu />
        </div>
      </header>
      <SiteBanner />
      <main className="container py-8">
        <Outlet />
      </main>
    </div>
  );
}

function MobileMenu() {
  const { locale, setLocale, t } = useI18n();
  const { theme, toggleTheme } = useTheme();
  const themeLabel = theme === "light" ? t("theme.toggle.toDark") : t("theme.toggle.toLight");

  return (
    <DropdownMenu>
      <DropdownMenuTrigger asChild>
        <Button
          type="button"
          variant="outline"
          size="icon"
          aria-label={t("nav.menu")}
          title={t("nav.menu")}
          className="ml-auto h-9 w-9 sm:hidden"
        >
          <Menu />
        </Button>
      </DropdownMenuTrigger>
      <DropdownMenuContent align="end" className="w-56 sm:hidden">
        <DropdownMenuItem asChild>
          <Link to="/stats" className="text-popover-foreground hover:no-underline">{t("nav.stats")}</Link>
        </DropdownMenuItem>
        <DropdownMenuItem asChild>
          <a href="https://help.testcase.ac" target="_blank" rel="noreferrer" className="text-popover-foreground hover:no-underline">
            {t("nav.help")}
          </a>
        </DropdownMenuItem>
        <DropdownMenuItem asChild>
          <a href={githubUrl} target="_blank" rel="noreferrer" className="text-popover-foreground hover:no-underline">
            <GitHubIcon />
            GitHub
          </a>
        </DropdownMenuItem>
        <DropdownMenuSeparator />
        <DropdownMenuLabel>{t("language.toggle.label")}</DropdownMenuLabel>
        <DropdownMenuRadioGroup
          value={locale}
          onValueChange={(value) => setLocale(value === "ko" ? "ko" : "en")}
        >
          <DropdownMenuRadioItem value="en">{t("language.option.en")}</DropdownMenuRadioItem>
          <DropdownMenuRadioItem value="ko">{t("language.option.ko")}</DropdownMenuRadioItem>
        </DropdownMenuRadioGroup>
        <DropdownMenuSeparator />
        <DropdownMenuItem onSelect={toggleTheme}>
          {theme === "light" ? <Moon /> : <Sun />}
          {themeLabel}
        </DropdownMenuItem>
      </DropdownMenuContent>
    </DropdownMenu>
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
      className="h-9 w-9"
    >
      {theme === "light" ? <Moon /> : <Sun />}
    </Button>
  );
}

function GitHubIcon() {
  return (
    <svg viewBox="0 0 24 24" fill="currentColor" aria-hidden="true">
      <path d="M12 2C6.477 2 2 6.477 2 12c0 4.419 2.865 8.167 6.839 9.489.5.09.682-.218.682-.482 0-.237-.009-.866-.014-1.7-2.782.604-3.369-1.341-3.369-1.341-.455-1.156-1.11-1.464-1.11-1.464-.908-.62.069-.608.069-.608 1.003.071 1.531 1.03 1.531 1.03.892 1.529 2.341 1.087 2.91.831.091-.646.349-1.087.635-1.337-2.221-.253-4.555-1.111-4.555-4.944 0-1.091.39-1.984 1.029-2.683-.103-.253-.446-1.27.098-2.647 0 0 .84-.269 2.75 1.025A9.58 9.58 0 0 1 12 6.832a9.58 9.58 0 0 1 2.504.337c1.909-1.294 2.748-1.025 2.748-1.025.546 1.377.203 2.394.1 2.647.64.699 1.028 1.592 1.028 2.683 0 3.842-2.337 4.687-4.566 4.935.359.309.679.92.679 1.855 0 1.338-.012 2.419-.012 2.748 0 .267.18.578.688.48A10.003 10.003 0 0 0 22 12c0-5.523-4.477-10-10-10Z" />
    </svg>
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
          className="h-8 w-8 gap-0 px-0 text-xs font-medium sm:h-9 sm:w-auto sm:gap-1 sm:px-2"
        >
          <Languages className="h-4 w-4 shrink-0 text-muted-foreground" />
          <span className="hidden uppercase sm:inline">{shortLabel}</span>
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
