# Deploy

The scripts and Terraform in this directory are the production deployment
defaults used by testcase.ac. Personal forks or other
environments may need adjustments.

- `api.sh` builds the backend API, syncs testcase data, and switches the
  blue/green slot. GitHub Actions authenticates through AWS OIDC and requests
  temporary Lightsail SSH credentials; Lambda invocation credentials remain in
  a root-owned persistent environment file on the host.
- `stresser.sh` builds the stresser runtime image and updates the ECR/Lambda
  deployment while provisioning its Terraform-managed infrastructure.
- `stresser-release.sh` publishes an already-tested local image and updates the
  existing Lambda without changing infrastructure. GitHub Actions uses this
  path after relevant changes reach `main`.
- `terraform/` defines the stresser deployment infrastructure.

When the deployment platform changes, we strongly recommend keeping those
changes inside this `deploy/` directory when possible. This keeps application
code and production deployment configuration clearly separated.
