mkdir -p build
rm compile_commands.json -f
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DVERBOSE=OFF .. # this is so clangd isnt a bitch, so it can see the definitions for header files
ln -s compile_commands.json ..                            # this too
