#!/bin/sh
path_catkin_ws="~/catkin_ws"

# launch world.launch
xterm -e "cd ${path_catkin_ws} && source devel/setup.bash && roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 3
# launch amcl.launch
xterm -e "cd ${path_catkin_ws} && source devel/setup.bash && roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 3
# launch view_navigation.launch
xterm -e "cd ${path_catkin_ws} && source devel/setup.bash && roslaunch add_markers view_navigation_home_service.launch" &
sleep 3
# launch pick_objects.cpp
xterm -e "cd ${path_catkin_ws} && source devel/setup.bash && rosrun pick_objects pick_objects" &
sleep 3 
# launch add_markers.cpp
xterm -e "cd ${path_catkin_ws} && source devel/setup.bash && rosrun add_markers add_markers" 
