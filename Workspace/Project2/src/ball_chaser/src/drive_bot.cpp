#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"

using namespace std;

ros::Publisher motor_command_publisher;

bool drive_request(ball_chaser::DriveToTarget::Request& request, ball_chaser::DriveToTarget::Response& result) 
{
    geometry_msgs::Twist motor_command;
    motor_command.linear.x = request.linear_x;
    motor_command.angular.z = request.angular_z;
    motor_command_publisher.publish(motor_command);
    result.msg_feedback = "Driving Bot";
    ROS_INFO_STREAM(result.msg_feedback);

    return true;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "drive_bot");
    ros::NodeHandle n;
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot", drive_request);
    ros::spin();

    return 0;
}