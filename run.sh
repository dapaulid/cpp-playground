#!/usr/bin/env bash
emrun --browser=chrome --hostname=localhost --kill_exit --browser_args="--headless --remote-debugging-port=0 --disable-gpu --disable-software-rasterizer" build/example.html