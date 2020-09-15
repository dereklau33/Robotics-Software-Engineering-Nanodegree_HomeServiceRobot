#!/bin/sh
path_catkin_ws="/home/workspace/catkin_ws"

# launch world.launch
xterm -e "cd ${path_catkin_ws} && source devel/setup.bash && roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 3
# launch amcl.launch
xterm -e "cd ${path_catkin_ws} && source devel/setup.bash && roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 3
# launch view_navigation.launch
xterm -e "cd ${path_catkin_ws} && source devel/setup.bash && roslaunch turtlebot_rviz_launchers view_navigation.launch" 


