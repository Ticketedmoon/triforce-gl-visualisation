
# Ubuntu (Change me if you have a different package manager)
sudo apt install unzip
sudo apt-get install libxrandr-dev -y
sudo apt-get install libxinerama-dev -y
sudo apt-get install libxcursor-dev -y
sudo apt-get install libxi-dev -y

mkdir -p deps/

cd deps/

# glfw
git clone https://github.com/glfw/glfw.git

# irrKlang
wget "https://www.ambiera.at/downloads/irrKlang-64bit-1.6.0.zip" -O "irrKlang.zip"
unzip ./irrKlang.zip
rm *.zip
mv irrKlang-64* irrKlang

cd glfw

cmake -G "Unix Makefiles"
make

cd ../../
mkdir -p build

cmake .

cd ./build
make