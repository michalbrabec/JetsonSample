# JetsonSample

Small sample application for Nvidia Jetson Nano focused mainly on the remote build, deployment and debugging.

## Jetson Nano Setup

- Prepare the Jetson microSD card according to the following [instructions](https://developer.nvidia.com/embedded/learn/get-started-jetson-nano-devkit#write)
- Boot Jetson Nano with keyboard and display to verif basic functionality
- Setup SSH connection including the [keys](https://www.digitalocean.com/community/tutorials/how-to-set-up-ssh-keys--2) for connection without password
- Connect to the same network and verify connection over SSH

## Windows Setup

- Install [WSL2](https://docs.microsoft.com/en-us/windows/wsl/install-win10)
- Install latest Ubuntu distribution for WSL
- Download the Nvidia Jetson toolchain [here](https://developer.nvidia.com/embedded/dlc/l4t-gcc-7-3-1-toolchain-64-bit)
  - Extract the archive into /opt/
- In WSL, install the following libraries required by GDB for Jetson Nano
  - sudo apt-get install libncurses5
  - sudo apt-get install libpython2.7
- Install Visual Studio Code for Windows [here](https://code.visualstudio.com/Download)
- In vscode, install the extension [Remote- WSL](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl)
- In vscode, open a new window in WSL
- In remote WSL vscode, install the extension [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) under WSL:Ubuntu
- Clone this repository somewhere to windows FS
- In remote WSL vscode, open the root folder (/mnt/c/...)
- Important commands:
  - Build Ctrl+Shift+B
  - Debug F5
 
