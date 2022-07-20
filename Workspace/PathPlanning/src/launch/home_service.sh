#!/bin/sh

xterm -e "cd /home/workspace/Project5 && source devel/setup.bash && roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/Project5/src/maps/hello3.world" &
sleep 5
xterm -e "cd /home/workspace/Project5 && source devel/setup.bash && roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/Project5/src/maps/map.yaml" &
sleep 5
xterm -e "cd /home/workspace/Project5 && source devel/setup.bash && roslaunch add_markers view_home_service_navigation.launch rviz_path:=/home/workspace/Project5/src/rvizConfig/NewRvizConfig.rviz" &
sleep 5
xterm -e "cd /home/workspace/Project5 && source devel/setup.bash && rosrun add_markers add_markers" &
sleep 5
xterm -e "cd /home/workspace/Project5 && source devel/setup.bash && rosrun pick_objects pick_objects" 