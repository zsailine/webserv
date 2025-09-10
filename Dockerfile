FROM debian:bullseye-slim

# Installer siege et quelques utilitaires
RUN apt-get update && \
    apt-get install -y siege curl && \
    rm -rf /var/lib/apt/lists/*

# Siege s’exécute en ligne de commande
ENTRYPOINT ["siege"]
