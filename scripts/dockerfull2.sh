#!/bin/bash

docker run --env USE_WAY_TOO_MUCH_RAM=1 --env USE_FULLNODE=1 --env USE_MULTICORE_READONLY=1 \
	-d -p 2002:2002 -p 8092:8092 -p 8093:8093 --name WeYouMe2 \
	WeYouMe/WeYouMe
