#include <sstream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"

enum link_list
{
    head_pub = 0,
    l_arm1,
    l_arm2,
    l_arm3,
    r_arm1,
    r_arm2,
    r_arm3,
    link_num,
};

int main(int argc,char **argv)
{
    ros::init(argc,argv,"control");
    
    ros::NodeHandle n;

    ros::Publisher yanshee_pub[link_num];

    yanshee_pub[head_pub] = n.advertise<std_msgs::Float64>("/yanshee/head_position_controller/command",100);

    yanshee_pub[l_arm1] = n.advertise<std_msgs::Float64>("/yanshee/left_arm1_position_controller/command",100);
    yanshee_pub[l_arm2] = n.advertise<std_msgs::Float64>("/yanshee/left_arm2_position_controller/command",100);
    yanshee_pub[l_arm3] = n.advertise<std_msgs::Float64>("/yanshee/left_arm3_position_controller/command",100);
    yanshee_pub[r_arm1] = n.advertise<std_msgs::Float64>("/yanshee/right_arm1_position_controller/command",100);
    yanshee_pub[r_arm2] = n.advertise<std_msgs::Float64>("/yanshee/right_arm2_position_controller/command",100);
    yanshee_pub[r_arm3] = n.advertise<std_msgs::Float64>("/yanshee/right_arm3_position_controller/command",100);

    std_msgs::Float64 msg[link_num];

    for(int i = 0;i<link_num;i++)
    {
        msg[i].data = 0;
    }
    float time = 0;
    ros::Rate loop_rate(100);
    while(ros::ok())
    {
        for(int i = 0;i<link_num;i++)
        {
            yanshee_pub[i].publish(msg[i]);
        }

        msg[l_arm1].data=3.14*(sin(time))/2;
        msg[r_arm1].data=-3.14*(sin(time))/2;
        ROS_INFO("data:%f",msg[l_arm1].data);
        ros::spinOnce();
        loop_rate.sleep();
        time+=0.02;
    }
    return 0;
}
