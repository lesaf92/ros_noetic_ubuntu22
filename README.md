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
... (still updating)

## Creating catkin workspace
After ROS and all packages are installed, create a catkin workspace to enable local custom packages
1. Create the folder and initialization
```shell
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
catkin_init_workspace
cd ~/catkin_ws
catkin_make
echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
source ~/.bashrc
```
2. In a new terminal, download or clone to `catkin_ws/src` the folder `rmp_2023` in this repository
3. Go back to `catkin_ws` and run `catkin_make`
4. Run the test launch file, you should see the robot Pioneer in the Gazebo environment
```shell
roslaunch rmp_2023 rmp_test.launch
```

## Disabling env (in case ROS is not needed anymore)

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
