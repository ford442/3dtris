# 3D-tris

A game and an experiment on using WebGL, Emscripten and other interesting stuff.

## Building

The browser version can be built like this

 1. Install [Emscripten](https://kripken.github.io/emscripten-site/docs/getting_started/downloads.html)
 1. locate `emsdk_env.sh` and set that in the root `Makefile`
 1. Run `make browser` (also try `make test`)
 1. `cd browser`
 1. `python -m SimpleHTTPServer`
 1. Go to http://localhost:8000/ (and http://localhost:8000/test/)

## Copyright & License info

See `COPYRIGHT.md` for the licences of the included JS libraries.
