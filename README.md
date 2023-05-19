# ROS Noetic on Ubuntu 22.04
Instructions for installing ROS Noetic on Ubuntu 22.04

1. Install utils
`sudo apt-get install htop python3-pip net-tools curl`
2. Install mamba
`curl -L -O "https://github.com/conda-forge/miniforge/releases/latest/download/Mambaforge-$(uname)-$(uname -m).sh"`
`bash Mambaforge-$(uname)-$(uname -m).sh`
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
`conda deactivate`
`conda activate ros_env`
