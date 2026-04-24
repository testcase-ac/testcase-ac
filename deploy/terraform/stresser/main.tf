terraform {
  required_version = ">= 1.5.0"
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 5.0"
    }
  }
}

provider "aws" {
  region = var.aws_region
}

data "aws_availability_zones" "available" {
  state = "available"
}

data "aws_caller_identity" "current" {}

resource "aws_ecr_repository" "stresser" {
  name                 = var.ecr_repository_name
  image_tag_mutability = "MUTABLE"
  force_delete         = true

  image_scanning_configuration {
    scan_on_push = true
  }
}

data "aws_iam_policy_document" "lambda_assume_role" {
  statement {
    actions = ["sts:AssumeRole"]
    principals {
      type        = "Service"
      identifiers = ["lambda.amazonaws.com"]
    }
  }
}

resource "aws_iam_role" "stresser_exec" {
  name               = "${var.function_name}-exec"
  assume_role_policy = data.aws_iam_policy_document.lambda_assume_role.json
}

data "aws_iam_policy_document" "stresser_runtime" {
  statement {
    sid = "WriteExistingLambdaLogStreams"
    actions = [
      "logs:CreateLogStream",
      "logs:PutLogEvents",
    ]
    resources = [
      "arn:aws:logs:${var.aws_region}:${data.aws_caller_identity.current.account_id}:log-group:/aws/lambda/${var.function_name}:*",
    ]
  }

  statement {
    sid = "ManageVpcNetworkInterfaces"
    actions = [
      "ec2:DescribeNetworkInterfaces",
      "ec2:DescribeSubnets",
      "ec2:DeleteNetworkInterface",
      "ec2:AssignPrivateIpAddresses",
      "ec2:UnassignPrivateIpAddresses",
    ]
    resources = ["*"]
  }

  statement {
    sid     = "CreateNetworkInterfacesInIsolatedVpc"
    actions = ["ec2:CreateNetworkInterface"]
    resources = concat(
      ["arn:aws:ec2:${var.aws_region}:${data.aws_caller_identity.current.account_id}:network-interface/*"],
      aws_subnet.stresser[*].arn,
      [aws_security_group.stresser_no_egress.arn],
    )
  }
}

resource "aws_iam_role_policy" "stresser_runtime" {
  name   = "${var.function_name}-runtime"
  role   = aws_iam_role.stresser_exec.id
  policy = data.aws_iam_policy_document.stresser_runtime.json
}

resource "aws_cloudwatch_log_group" "stresser" {
  name              = "/aws/lambda/${var.function_name}"
  retention_in_days = 14
}

resource "aws_vpc" "stresser" {
  cidr_block           = var.vpc_cidr_block
  enable_dns_hostnames = false
  enable_dns_support   = false

  tags = {
    Name = "${var.function_name}-isolated"
  }
}

resource "aws_subnet" "stresser" {
  count = 2

  vpc_id            = aws_vpc.stresser.id
  cidr_block        = cidrsubnet(aws_vpc.stresser.cidr_block, 8, count.index)
  availability_zone = data.aws_availability_zones.available.names[count.index]

  tags = {
    Name = "${var.function_name}-isolated-${count.index + 1}"
  }
}

resource "aws_security_group" "stresser_no_egress" {
  name        = "${var.function_name}-no-egress"
  description = "No outbound access for submitted code"
  vpc_id      = aws_vpc.stresser.id

  # Run submitted code in isolated Lambda ENIs with no outbound network path.
  egress = []
}

resource "aws_lambda_function" "stresser" {
  function_name = var.function_name
  role          = aws_iam_role.stresser_exec.arn
  package_type  = "Image"
  image_uri     = "${aws_ecr_repository.stresser.repository_url}:${var.image_tag}"
  architectures = [var.lambda_architecture]
  memory_size   = var.memory_mb
  timeout       = var.timeout_seconds

  vpc_config {
    subnet_ids         = aws_subnet.stresser[*].id
    security_group_ids = [aws_security_group.stresser_no_egress.id]
  }

  depends_on = [
    aws_cloudwatch_log_group.stresser,
    aws_iam_role_policy.stresser_runtime,
  ]
}

data "aws_iam_policy_document" "lambda_invoke" {
  statement {
    actions   = ["lambda:InvokeFunction"]
    resources = [aws_lambda_function.stresser.arn]
  }
}

resource "aws_iam_user" "backend_invoker" {
  name = var.iam_user_name
}

resource "aws_iam_user_policy" "backend_invoker" {
  name   = "${var.iam_user_name}-lambda-invoke"
  user   = aws_iam_user.backend_invoker.name
  policy = data.aws_iam_policy_document.lambda_invoke.json
}

resource "aws_iam_access_key" "backend_invoker" {
  user = aws_iam_user.backend_invoker.name
}
