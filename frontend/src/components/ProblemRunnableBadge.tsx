import { CircleAlert } from "lucide-react";

import { Badge } from "@/components/ui/badge";
import { useI18n } from "@/lib/i18n";

export default function ProblemRunnableBadge({ runnable }: { runnable: boolean }) {
  const { t } = useI18n();
  if (runnable) return null;

  return (
    <Badge
      variant="outline"
      className="w-fit shrink-0 gap-0.5 whitespace-nowrap border-muted-foreground/30 bg-muted/40 px-1.5 text-[11px] font-medium text-muted-foreground sm:gap-1 sm:text-xs"
    >
      <CircleAlert className="size-2.5 sm:size-3" aria-hidden />
      {t("home.runnable.no")}
    </Badge>
  );
}
