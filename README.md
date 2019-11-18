# How to setup Emscripten
<br>
$ mkdir build && cd build <br>
$ ../emsdk/upstream/emscripten/emconfigure cmake .. <br>
$ ../emsdk/upstream/emscripten/emmake make <br>
$ cd ..
$ python3 -m http.server <br>
