#include <ros/ros.h>
#include <std_srvs/SetBool.h>
#include <geometry_msgs/Twist.h>

class vel_stopper
{
public:
    vel_stopper();
    ros::NodeHandle nh_;
    bool traffic_vel_callback(std_srvs::SetBool::Request &traf_req,
                              std_srvs::SetBool::Response &traf_resp);
    bool stop_vel_callback(std_srvs::SetBool::Request &stop_req,
                           std_srvs::SetBool::Response &stop_resp);
    void cmd_callback(const geometry_msgs::Twist::ConstPtr& cmd_vel_msg);
    void send_vel();
private:
    geometry_msgs::Twist pub_vel,vel;
    ros::Publisher vel_pub;
    ros::ServiceServer traffic_call,stop_call;
    bool traffic_vel_flg = false;
    bool stop_vel_flg = false;

};
vel_stopper::vel_stopper() :
nh_()
{
    traffic_call = nh_.advertiseService("traffic_service", 
                                        &vel_stopper::traffic_vel_callback,this);
    stop_call = nh_.advertiseService("stop_service",
                                        &vel_stopper::stop_vel_callback,this);
    vel_pub =nh_.advertise<geometry_msgs::Twist>("stop_vel",1);
}

bool vel_stopper::traffic_vel_callback(std_srvs::SetBool::Request &traf_req,
                                       std_srvs::SetBool::Response &traf_resp)
{
    traffic_vel_flg = traf_req.data;
    traf_resp.message = "true";
    traf_resp.success = true;
    ROS_INFO("traffic mode!");
}
bool vel_stopper::stop_vel_callback(std_srvs::SetBool::Request &stop_req,
                                    std_srvs::SetBool::Response &stop_resp)
{
    stop_vel_flg = stop_req.data;
    stop_resp.message = "true";
    stop_resp.success = true;
    ROS_INFO("stop mode!");
}

void vel_stopper::cmd_callback(const geometry_msgs::Twist::ConstPtr& cmd_vel_msg)
{
    vel.linear.x = cmd_vel_msg->linear.x;
    vel.angular.x = cmd_vel_msg->angular.z;
}
void vel_stopper::send_vel()
{
    if(stop_vel_flg && !traffic_vel_flg)
    {
        pub_vel.linear.x = 0.0;
        pub_vel.angular.z = 0.0;
        ROS_INFO("stop mode now!");
    }
    if(traffic_vel_flg && !stop_vel_flg)
    {
        pub_vel.linear.x = vel.linear.x + 0.4;
        ROS_INFO("traffic mode now!");
    }
    else
    {
        ROS_INFO("take~~~???");
    }
}

int main(int argc, char** argv){
  ros::init(argc, argv, "vel_stopper_node");
 // ros::Rate loop_rate(1);
  vel_stopper vel_stop;
  ros::Rate loop_rate(1);
     while (ros::ok())
        {
            vel_stop.send_vel();
            ros::spinOnce();                                         
            loop_rate.sleep();
       }      
        
    return 0;
    }
