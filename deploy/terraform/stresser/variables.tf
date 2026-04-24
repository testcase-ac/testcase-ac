variable "aws_region" {
  type    = string
  default = "ap-northeast-2"
}

variable "ecr_repository_name" {
  type    = string
  default = "testcase-ac-stresser"
}

variable "function_name" {
  type    = string
  default = "testcase-ac-stresser"
}

variable "image_tag" {
  type    = string
  default = "latest"
}

variable "memory_mb" {
  type    = number
  default = 1796
}

variable "timeout_seconds" {
  type    = number
  default = 110
}

variable "vpc_cidr_block" {
  type    = string
  default = "10.42.0.0/16"
}

variable "lambda_architecture" {
  type    = string
  default = "x86_64"

  validation {
    condition     = contains(["x86_64", "arm64"], var.lambda_architecture)
    error_message = "lambda_architecture must be either x86_64 or arm64."
  }
}

variable "iam_user_name" {
  type    = string
  default = "testcase-ac-backend-invoker"
}
