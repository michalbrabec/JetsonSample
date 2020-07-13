# JetsonSample

Small sample application for Nvidia Jetson Nano focused mainly on the remote build, deployment and debugging.

## Windows Setup

- Install [WSL2](https://docs.microsoft.com/en-us/windows/wsl/install-win10)
- Install latest Ubuntu distribution for WSL
- Download the Nvidia Jetson toolchain [here](https://developer.nvidia.com/embedded/dlc/l4t-gcc-7-3-1-toolchain-64-bit)
- In WSL, install the following libraries required by GDB for Jetson Nano
  - sudo apt-get install libncurses5
  - sudo apt-get install libpython2.7
- Install Visual Studio Code for Windows [here](https://code.visualstudio.com/Download)
- In vscode, install the extension [Remote- WSL](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl)
- In vscode, open a new window in WSL
- In remote WSL vscode, install the extension [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) under WSL:Ubuntu
- Clone this repository somewhere to windows FS
- In remote WSL vscode, open the root folder (/mnt/c/...)
- Commands:
  - Build Ctrl+Shift+B
  - Debug F5
 
