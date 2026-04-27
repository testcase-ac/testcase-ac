import type { ProblemSummary, TypeMetadata } from "../types";

export function problemTypeLabel(problemType: string, typeMetadata: TypeMetadata | undefined): string {
  return typeMetadata?.label || problemType;
}

export function segmentLabel(typeMetadata: TypeMetadata | undefined, segment: string, depth: number): string {
  const segmentMetadata = typeMetadata?.segments?.[depth];
  const mappedLabel = segmentMetadata?.labels?.find((entry) => entry.value === segment)?.label;
  if (mappedLabel) {
    return mappedLabel;
  }
  return applySegmentTemplate(segmentMetadata?.label, segment);
}

export function pageTitle(
  problemType: string,
  segments: string[],
  typeMetadata: TypeMetadata | undefined,
): string {
  if (segments.length === 0) return problemTypeLabel(problemType, typeMetadata);
  const lastIndex = segments.length - 1;
  return segmentLabel(typeMetadata, segments[lastIndex], lastIndex);
}

export function compareProblems(
  typeMetadata: TypeMetadata | undefined,
  a: ProblemSummary,
  b: ProblemSummary,
): number {
  const aSegments = a.externalId.split("/");
  const bSegments = b.externalId.split("/");
  for (let i = 0; i < Math.max(aSegments.length, bSegments.length); i += 1) {
    const compared = compareSegment(typeMetadata, aSegments[i] ?? "", bSegments[i] ?? "", i);
    if (compared !== 0) return compared;
  }
  return 0;
}

export function compareSegment(
  typeMetadata: TypeMetadata | undefined,
  a: string,
  b: string,
  depth: number,
): number {
  const segmentLabels = typeMetadata?.segments?.[depth]?.labels;
  if (segmentLabels?.length) {
    const aIndex = segmentLabels.findIndex((entry) => entry.value === a);
    const bIndex = segmentLabels.findIndex((entry) => entry.value === b);
    if (aIndex !== -1 || bIndex !== -1) {
      return orderIndex(aIndex) - orderIndex(bIndex) || a.localeCompare(b);
    }
  }
  const aNumber = Number(a);
  const bNumber = Number(b);
  if (Number.isFinite(aNumber) && Number.isFinite(bNumber)) {
    return aNumber - bNumber;
  }
  return a.localeCompare(b);
}

function orderIndex(index: number): number {
  return index === -1 ? Number.MAX_SAFE_INTEGER : index;
}

function applySegmentTemplate(template: string | undefined, segment: string): string {
  if (!template) return segment;
  return template.includes("{}") ? template.replaceAll("{}", segment) : template;
}
