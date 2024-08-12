FROM debian:bullseye

WORKDIR /app

RUN apt-get update && apt-get install -y \
    build-essential \
    libreadline-dev \
    git \
    && rm -rf /var/lib/apt/lists/*

COPY . .

RUN make

CMD ["./minishell"]
