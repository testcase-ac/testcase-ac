output "ecr_repository_url" {
  value = aws_ecr_repository.stresser.repository_url
}

output "lambda_function_name" {
  value = aws_lambda_function.stresser.function_name
}

output "lambda_function_arn" {
  value = aws_lambda_function.stresser.arn
}

output "access_key_id" {
  value = aws_iam_access_key.backend_invoker.id
}

output "secret_access_key" {
  value     = aws_iam_access_key.backend_invoker.secret
  sensitive = true
}

output "iam_user_arn" {
  value = aws_iam_user.backend_invoker.arn
}
