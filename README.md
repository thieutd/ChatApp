# ChatApp

## Setup Server on Ubuntu

### Step 1: Install Required Packages
```bash
sudo apt update
sudo apt install -y git build-essential cmake ninja-build zip unzip pkg-config autoconf bison flex postgresql redis-server
```

### Step 2: Install vcpkg Package Manager & Configure Environment Variables
```bash
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
cd ~/vcpkg
./bootstrap-vcpkg.sh
echo 'export VCPKG_ROOT="$HOME/vcpkg"' >> ~/.bashrc
echo 'export PATH="$VCPKG_ROOT:$PATH"' >> ~/.bashrc
source ~/.bashrc
```

### Step 3: Clone and Build Server
```bash
git clone https://github.com/thieutd/ChatApp ~/ChatApp
cd ~/ChatApp/Server
chmod +x overlay-ports/botan/configure
cmake --preset linux-gcc-static
cmake --build --preset linux-gcc-static-debug
```

### Step 4: Run the Server
```bash
cd build/linux-gcc-static/Debug
./ChatServer ../../../config.json
```

## Deployed Server
- https://drogonserver.eastasia.cloudapp.azure.com/
- APIs: https://www.postman.com/lunar-module-operator-29628276/server-apis/