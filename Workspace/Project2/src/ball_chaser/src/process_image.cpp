#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>
using namespace std;

ros::ServiceClient client;

void drive_bot(float lin_x, float ang_z)
{
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;
    if (!client.call(srv))
        {
            ROS_ERROR("Unable to call service");
        }
}

void process_image_callback(const sensor_msgs::Image img)
{

    int i;
    
    int ball_pos;
    int ball_pos_mid;
    int ball_pos_tot = 0;
    int white_px = 0;
    
    for (i = 0; i + 2 < img.data.size(); i = i + 3)
    {
        if ((img.data[i] == 255) && (img.data[i+1] == 255) && (img.data[i+2] == 255))
        {
            ball_pos = (i % (img.width * 3)) / 3;
            white_px++;
            ball_pos_tot += ball_pos;
            
        }
    }
    
    if (white_px == 0)
    {
        drive_bot(0, 0);
    }
    else
    {
        ball_pos_mid = ball_pos_tot / white_px;
        
        
        if(ball_pos_mid < img.width / 3)
        {
            drive_bot(0.1, 0.5);
        }
        else if(ball_pos_mid > img.width * 2 / 3)
        {
            drive_bot(0.1, -0.5);
        }
        else
        {
            drive_bot(0.1, 0);
        }
    }


}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);
    ros::spin();
    return 0;
}
