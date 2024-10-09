#/bin/sh

rm -f *.so dinoServer/*.so 2> /dev/null
rm -rf python/build python/dino/__pycache__ python/dino_game.egg-info 2> /dev/null
cd dino
make clean 2> /dev/null
cd ..
