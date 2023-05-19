# ROS Noetic on Ubuntu 22.04
Instructions for installing ROS Noetic on Ubuntu 22.04

## Install

1. Install utils
```
sudo apt-get install htop python3-pip net-tools curl
```
2. Install mamba
```
curl -L -O "https://github.com/conda-forge/miniforge/releases/latest/download/Mambaforge-$(uname)-$(uname -m).sh"
bash Mambaforge-$(uname)-$(uname -m).sh
```
3. Install and configure robostack
```
mamba create -n ros_env python=3.9 -c conda-forge
mamba activate ros_env
conda config --env --add channels conda-forge
conda config --env --add channels robostack-staging
conda config --env --remove channels defaults
mamba install ros-noetic-desktop-full
mamba install catkin_tools
mamba install rosdep
rosdep init
rosdep update
```
4. Put at the end of your `bashrc` file
```
conda deactivate
conda activate ros_env
```

## Disabling env

To prevent loading the env for every new terminal session, comment the section below in your `bashrc`
```
# >>> conda initialize >>>
# !! Contents within this block are managed by 'conda init' !!
__conda_setup="$('/home/luiz/mambaforge/bin/conda' 'shell.bash' 'hook' 2> /dev/null)"
if [ $? -eq 0 ]; then
    eval "$__conda_setup"
else
    if [ -f "/home/luiz/mambaforge/etc/profile.d/conda.sh" ]; then
        . "/home/luiz/mambaforge/etc/profile.d/conda.sh"
    else
        export PATH="/home/luiz/mambaforge/bin:$PATH"
    fi
fi
unset __conda_setup

if [ -f "/home/luiz/mambaforge/etc/profile.d/mamba.sh" ]; then
    . "/home/luiz/mambaforge/etc/profile.d/mamba.sh"
fi
# <<< conda initialize <<<
conda deactivate
conda activate ros_env
```

## Uninstall

Follow instructions [here](https://github.com/conda-forge/miniforge#uninstallation)
