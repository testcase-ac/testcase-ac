import type { ChangeEvent, FocusEvent, InputHTMLAttributes } from "react";

import { Input } from "@/components/ui/input";

type InputNumberProps = Omit<
  InputHTMLAttributes<HTMLInputElement>,
  "max" | "min" | "onChange" | "step" | "type" | "value"
> & {
  fallback: number;
  max: number;
  min: number;
  onChange: (value: number) => void;
  step?: number;
  value: number;
};

function clampIntegerRange(value: number, fallback: number, min: number, max: number): number {
  const finiteValue = Number.isFinite(value) ? value : fallback;
  const normalized = Number.isFinite(finiteValue) ? finiteValue : min;
  return Math.min(max, Math.max(min, Math.floor(normalized)));
}

function normalizeRawNumberInput(input: HTMLInputElement, fallback: number, min: number, max: number): number {
  const next = Number(input.value);
  const normalized = Number.isFinite(next) ? next : clampIntegerRange(next, fallback, min, max);
  // React can skip a render when raw text changes but the parsed number does not, such as 1 -> 01.
  input.value = String(normalized);
  return normalized;
}

export default function InputNumber({
  fallback,
  max,
  min,
  onBlur,
  onChange,
  step = 1,
  value,
  ...props
}: InputNumberProps) {
  function handleChange(event: ChangeEvent<HTMLInputElement>) {
    onChange(normalizeRawNumberInput(event.currentTarget, fallback, min, max));
  }

  function handleBlur(event: FocusEvent<HTMLInputElement>) {
    const normalized = clampIntegerRange(Number(event.currentTarget.value), fallback, min, max);
    event.currentTarget.value = String(normalized);
    onChange(normalized);
    onBlur?.(event);
  }

  return (
    <Input
      {...props}
      type="number"
      min={min}
      max={max}
      step={step}
      value={value}
      onChange={handleChange}
      onBlur={handleBlur}
    />
  );
}
