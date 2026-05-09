import type { ReactNode } from "react";

import { useI18n } from "@/lib/i18n";
import { useSiteConfig } from "@/lib/siteConfig";

const INLINE_LINK_PATTERN = /\[([^\]]+)\]\((https?:\/\/[^)\s]+)\)/g;

export default function SiteBanner() {
  const { locale } = useI18n();
  const { banner } = useSiteConfig();
  const message = banner?.enabled ? banner.messages[locale] : undefined;

  if (!message) return null;

  return (
    <div className="border-b bg-accent text-accent-foreground">
      <div className="container py-2 text-xs leading-5 sm:text-sm sm:leading-6">
        {renderInlineLinks(message)}
      </div>
    </div>
  );
}

function renderInlineLinks(text: string): ReactNode[] {
  const nodes: ReactNode[] = [];
  let lastIndex = 0;

  for (const match of text.matchAll(INLINE_LINK_PATTERN)) {
    const [source, label, href] = match;
    const matchIndex = match.index ?? 0;

    if (matchIndex > lastIndex) {
      nodes.push(text.slice(lastIndex, matchIndex));
    }

    nodes.push(
      <a key={matchIndex} href={href} target="_blank" rel="noreferrer">
        {label}
      </a>,
    );

    lastIndex = matchIndex + source.length;
  }

  if (lastIndex < text.length) {
    nodes.push(text.slice(lastIndex));
  }

  return nodes;
}
