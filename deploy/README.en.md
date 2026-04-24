# Deploy

The scripts and Terraform in this directory are the production deployment
defaults used by testcase.ac. Personal forks or other
environments may need adjustments.

- `api.sh` builds the backend API, syncs testcase data, and switches the
  blue/green slot.
- `stresser.sh` builds the stresser runtime image and updates the ECR/Lambda
  deployment.
- `terraform/` defines the stresser deployment infrastructure.

When the deployment platform changes, we strongly recommend keeping those
changes inside this `deploy/` directory when possible. This keeps application
code and production deployment configuration clearly separated.
