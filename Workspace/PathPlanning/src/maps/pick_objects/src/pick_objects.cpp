#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define SimpleActionClient For Move Base
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv)
{
  	// Initialize the simple_navigation_goals node
  	ros::init(argc, argv, "pick_objects");
	
	//tell the action client that we want to spin a thread by default
	MoveBaseClient ac("move_base", true);
	
	// Wait 5 sec for move_base action server to come up
	while(!ac.waitForServer(ros::Duration(5.0)))
	{
		ROS_INFO("Waiting For move_base Action Server");
	}
	
	move_base_msgs::MoveBaseGoal goal;
	
	// set up the frame parameters
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();
	
	// Define a position and orientation for the robot to reach
	goal.target_pose.pose.position.x = 2.0;
	goal.target_pose.pose.position.y = 2.0;
	goal.target_pose.pose.orientation.w = 1.0;
	
	// Send the goal position and orientation for the robot to reach
	ROS_INFO("Sending Goal Position...");
	ac.sendGoal(goal);
	
	// Wait an infinite time for the results
	ac.waitForResult();
	
	// Check if the robot reached its goal
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
	{
		ROS_INFO("Goal Position Reached!");
	}
	else
	{
		ROS_INFO("Unable To Reach Goal Position.");
	}
	
	if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
	{
		ros::Duration(5).sleep();
		
        goal.target_pose.header.frame_id = "map";
		goal.target_pose.header.stamp = ros::Time::now();
		// Define another position and orientation for the robot to reach
		
		goal.target_pose.pose.position.x = -2.0;
		goal.target_pose.pose.position.y = 3.0;
		goal.target_pose.pose.orientation.w = 1.0;
		
		// Send the goal position and orientation for the robot to reach
		ROS_INFO("Sending Second Goal Position...");
		ac.sendGoal(goal);
		
		// Wait an infinite time for the results
		ac.waitForResult();
		
		// Check if the robot reached its goal
		if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
		{
			ROS_INFO("Second Goal Position Reached!");
		}
    	else
		{
			ROS_INFO("Unable To Reach Second Goal Position.");
		}
  	}
	
	return 0;
}