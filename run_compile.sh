g++ ./src/lib/**/*.cpp \
    ./src/main.cpp \
    ./src/lib/**/*.c \
    -o application.exe \
    -I./include \
    -I./deps/glfw/include \
    -L./deps/glfw/src \
    -I./deps/irrKlang/include \
    -L/usr/lib ./deps/irrKlang/bin/linux-gcc-64/libIrrKlang.so -pthread \
    -lglfw3 -lXrandr -lXcursor -lXi -lXinerama
