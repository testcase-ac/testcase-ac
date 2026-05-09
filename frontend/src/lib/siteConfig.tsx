import {
  createContext,
  useContext,
  useMemo,
  type ReactNode,
} from "react";

import type { Locale } from "./i18n";

type BannerMessages = Partial<Record<Locale, string>>;

export type SiteBannerConfig = {
  enabled: boolean;
  messages: BannerMessages;
};

type SiteConfig = {
  banner?: SiteBannerConfig;
};

type SiteConfigContextValue = {
  config: SiteConfig;
};

const SiteConfigContext = createContext<SiteConfigContextValue | null>(null);
const DEFAULT_SITE_CONFIG: SiteConfig = {};
const SITE_CONFIG_ELEMENT_ID = "site-config";

export function SiteConfigProvider({ children }: { children: ReactNode }) {
  const config = useMemo(readSiteConfig, []);
  const value = useMemo(() => ({ config }), [config]);

  return <SiteConfigContext.Provider value={value}>{children}</SiteConfigContext.Provider>;
}

export function useSiteConfig(): SiteConfig {
  const context = useContext(SiteConfigContext);
  if (!context) {
    throw new Error("useSiteConfig must be used within SiteConfigProvider");
  }
  return context.config;
}

function readSiteConfig(): SiteConfig {
  const element = document.getElementById(SITE_CONFIG_ELEMENT_ID);
  const source = element?.textContent;
  if (!source) return DEFAULT_SITE_CONFIG;

  try {
    return parseSiteConfig(JSON.parse(source));
  } catch (error) {
    console.warn("Failed to parse site config", error);
    return DEFAULT_SITE_CONFIG;
  }
}

function parseSiteConfig(value: unknown): SiteConfig {
  if (!isRecord(value)) return DEFAULT_SITE_CONFIG;

  return {
    banner: parseBannerConfig(value.banner),
  };
}

function parseBannerConfig(value: unknown): SiteBannerConfig | undefined {
  if (!isRecord(value)) return undefined;

  const enabled = value.enabled === true;
  const messages = parseBannerMessages(value.messages);
  if (!enabled || Object.keys(messages).length === 0) return undefined;

  return { enabled, messages };
}

function parseBannerMessages(value: unknown): BannerMessages {
  if (!isRecord(value)) return {};

  const messages: BannerMessages = {};
  if (typeof value.en === "string" && value.en.trim()) {
    messages.en = value.en;
  }
  if (typeof value.ko === "string" && value.ko.trim()) {
    messages.ko = value.ko;
  }
  return messages;
}

function isRecord(value: unknown): value is Record<string, unknown> {
  return typeof value === "object" && value !== null && !Array.isArray(value);
}
