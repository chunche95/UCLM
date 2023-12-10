#!/bin/bash

docker run -d \
    --name="rabbit2" \
    --hostname="rabbit2"\
    -e RABBITMQ_ERLANG_COOKIE="secret string" \
    -e RABBITMQ_NODENAME="rabbit2" \
    --volume="$(pwd)/rabbitmq.config:/etc/rabbitmq/rabbitmq.config" \
    --volume="$(pwd)/definitions.json:/etc/rabbitmq/definitions.json" \
    --link="192.168.1.71:rabbit1" \
    rabbitmq:3-management

docker run -d \
    --name="rabbit3" \
    --hostname="rabbit3"\
    -e RABBITMQ_ERLANG_COOKIE="secret string" \
    -e RABBITMQ_NODENAME="rabbit3" \
    --volume="(pwd)/rabbitmq.config:/etc/rabbitmq/rabbitmq.config" \
    --volume="(pwd)/definitions.json:/etc/rabbitmq/definitions.json" \
    --link="192.168.1.71:rabbit1" \
    --link="rabbit2:rabbit2" \
    rabbitmq:3-management
