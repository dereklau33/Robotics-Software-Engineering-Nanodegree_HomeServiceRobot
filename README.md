# Robotics Software Engineering Nanodegree: Home Service Robot

# Goal
In this project, I combined previous aspects of localization and mapping with navigation and path planning to create a robot that can autonomously map an unknown environment and navigate and plan its own path to pick up and drop off virtual objects. 

# Summary of Tasks
Model real world environments in Gazebo through the Building Editor

Interface SLAM with a Wall Follower node to autnomously map the environment

Reach multiple goals with the correct given orientation throughout the map through the ROS navigation stack

Model virutal objects with markers and deploy with ROS

# Project Requirements
Ubuntu 16.04 LTS
ROS Kinetic
Gazebo >= 7.0  

# Project Setup
Run Update On Linux Command Line:   
```bash
$ sudo apt-get update && sudo apt-get upgrade -y
``` 

# Run Instructions
Create a workspace:    
```bash
$ mkdir -p ~/home/workspace/
$ cd /home/workspace/
```   

Clone repository:
```bash
$ git clone https://github.com/dereklau33/Robotics-Software-Engineering-Nanodegree_HomeServiceRobot
```

Build package:  
```bash
$ cd ..
$ source devel/setup.bash
$ catkin_make
```

To test the localization and mapping (AMCL) aspect of the project, launch the shell script file:
```bash
./test_slam.sh
```   
A keyboard teleop node will appear in one of the terminals allowing you to control the robot with your keyboard. 

To test the navigation aspect of the project, launch the shell script file:
```bash
./test_navigation.sh
```  

To run the full project, launch the shell script file:
```bash
./home_navigations.sh
```  

The robot will start in a predefined initial position and navigate a path towards the object displayed by the green cube. When it reaches the cube, it will disappear representing that the cube has been "picked up". The robot then moves to another location where the cube will reappear, representing the cube has been "dropped off". 

The ROS navigation stack used to create the path of the robot and avoid obstacles is based on Dijkstra's algorithm, similar to Uniform Cost Search. 
