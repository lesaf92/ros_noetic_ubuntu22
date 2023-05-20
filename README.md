# ROS Noetic on Ubuntu 22.04
Instructions for installing ROS Noetic on Ubuntu 22.04

## Install

1. Install utils
```shell
sudo apt-get install htop python3-pip net-tools curl
```
2. Install mamba
```shell
curl -L -O "https://github.com/conda-forge/miniforge/releases/latest/download/Mambaforge-$(uname)-$(uname -m).sh"
bash Mambaforge-$(uname)-$(uname -m).sh
```
3. Install and configure robostack
```shell
mamba create -n ros_env python=3.9 -c conda-forge
mamba activate ros_env
conda config --env --add channels conda-forge
conda config --env --add channels robostack-staging
# remove the defaults channel just in case, this might return an error if it is not in the list which is ok
conda config --env --remove channels defaults
mamba install ros-noetic-desktop-full
mamba install catkin_tools
mamba install rosdep
rosdep init
rosdep update
```
4. Put at the end of your `bashrc` file
```shell
conda deactivate
conda activate ros_env
```
5. Open a new terminal and test `roscore`, if everything went fine ROS should be installed successfully
6. Always do the following steps in the `ros_env` environment
7. Install the necessary ROS packages using `conda install -c robostack <package>`, eventually it will ask for installing additional packages, just confirm and carry on
```shell
conda install -c robostack ros-noetic-gmapping
conda install -c robostack ros-noetic-amcl
conda install -c robostack ros-noetic-move-base
conda install -c robostack ros-noetic-map-server
```


## Disabling env

To prevent loading the env for every new terminal session, comment the section below in your `bashrc`
```shell
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
