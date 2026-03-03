mkdir build
cd build
# The -DCMAKE_EXPORT_COMPILE_COMMANDS=ON is the key for clangd
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
# Link the generated file to the root so clangd finds it
ln -s compile_commands.json ..
