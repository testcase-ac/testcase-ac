import {
  createContext,
  useContext,
  useMemo,
  useState,
  useEffect,
  type ReactNode,
} from "react";

import {
  isCppLanguageValue,
  isLanguageValue,
  type CppLanguageValue,
  type LanguageValue,
} from "../types";

export type Theme = "light" | "dark";
export type Locale = "en" | "ko";

interface StoredSettings {
  theme: Theme;
  locale: Locale;
  useLanguageAutodetect: boolean;
  lastManualLanguage: LanguageValue;
  lastManualCppLanguage: CppLanguageValue;
}

interface PersistentSettingsContextValue extends StoredSettings {
  setTheme: (theme: Theme) => void;
  setLocale: (locale: Locale) => void;
  setUseLanguageAutodetect: (value: boolean) => void;
  setLastManualLanguage: (language: LanguageValue) => void;
  setLastManualCppLanguage: (language: CppLanguageValue) => void;
}

const STORAGE_KEY = "testcase-ac.settings";
const LEGACY_THEME_KEY = "testcase-ac.theme";
const LEGACY_LOCALE_KEY = "testcase-ac.locale";

const PersistentSettingsContext = createContext<PersistentSettingsContextValue | null>(null);

function readStoredObject(): Record<string, unknown> | null {
  if (typeof window === "undefined") return null;
  try {
    const raw = window.localStorage.getItem(STORAGE_KEY);
    if (!raw) return null;
    const parsed = JSON.parse(raw);
    return parsed && typeof parsed === "object" ? (parsed as Record<string, unknown>) : null;
  } catch {
    return null;
  }
}

function readLegacyValue(key: string): string | null {
  if (typeof window === "undefined") return null;
  try {
    return window.localStorage.getItem(key);
  } catch {
    return null;
  }
}

function readTheme(value: unknown): Theme | null {
  return value === "light" || value === "dark" ? value : null;
}

function readLocale(value: unknown): Locale | null {
  return value === "en" || value === "ko" ? value : null;
}

function fallbackLocale(): Locale {
  if (typeof window === "undefined") return "en";
  const nav = window.navigator?.language?.toLowerCase() ?? "";
  return nav.startsWith("ko") ? "ko" : "en";
}

function readInitialSettings(): StoredSettings {
  const stored = readStoredObject();
  const theme = readTheme(stored?.theme) ?? readTheme(readLegacyValue(LEGACY_THEME_KEY)) ?? "light";
  const locale = readLocale(stored?.locale) ?? readLocale(readLegacyValue(LEGACY_LOCALE_KEY)) ?? fallbackLocale();
  const useLanguageAutodetect =
    typeof stored?.useLanguageAutodetect === "boolean" ? stored.useLanguageAutodetect : true;
  const storedLastManualLanguage = String(stored?.lastManualLanguage ?? "");
  const lastManualLanguage = isLanguageValue(storedLastManualLanguage)
    ? storedLastManualLanguage
    : "cpp23";
  const storedLastManualCppLanguage = String(stored?.lastManualCppLanguage ?? "");
  const lastManualCppLanguage = isCppLanguageValue(storedLastManualCppLanguage)
    ? storedLastManualCppLanguage
    : isCppLanguageValue(lastManualLanguage)
      ? lastManualLanguage
    : "cpp23";

  return {
    theme,
    locale,
    useLanguageAutodetect,
    lastManualLanguage,
    lastManualCppLanguage,
  };
}

export function PersistentSettingsProvider({ children }: { children: ReactNode }) {
  const [settings, setSettings] = useState<StoredSettings>(readInitialSettings);

  useEffect(() => {
    try {
      window.localStorage.setItem(STORAGE_KEY, JSON.stringify(settings));
    } catch {
      // localStorage may be unavailable; ignore.
    }
  }, [settings]);

  const value = useMemo<PersistentSettingsContextValue>(
    () => ({
      ...settings,
      setTheme: (theme) => setSettings((current) => ({ ...current, theme })),
      setLocale: (locale) => setSettings((current) => ({ ...current, locale })),
      setUseLanguageAutodetect: (useLanguageAutodetect) =>
        setSettings((current) => ({ ...current, useLanguageAutodetect })),
      setLastManualLanguage: (lastManualLanguage) =>
        setSettings((current) => ({ ...current, lastManualLanguage })),
      setLastManualCppLanguage: (lastManualCppLanguage) =>
        setSettings((current) => ({ ...current, lastManualCppLanguage })),
    }),
    [settings],
  );

  return (
    <PersistentSettingsContext.Provider value={value}>{children}</PersistentSettingsContext.Provider>
  );
}

export function usePersistentSettings(): PersistentSettingsContextValue {
  const ctx = useContext(PersistentSettingsContext);
  if (!ctx) throw new Error("usePersistentSettings must be used inside PersistentSettingsProvider");
  return ctx;
}
