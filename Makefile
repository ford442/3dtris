EMCC_PATH=~/emsdk/emsdk_env.sh

.PHONY: browser
browser:
	bash -c "cd cpp && source ${EMCC_PATH} && make bin/js/game.js"
	rm -rf browser/build/*
	mkdir -p browser/build
	cp cpp/bin/js/game.js browser/build/game.js
	cp cpp/bin/js/game.wasm browser/build/game.wasm
