#include "ros/ros.h"
#include "rasp4b_core/SensorState.h"
#include <math.h>

double last_t=0;
int wrong_cnt=0;
void show_vel_callback(const rasp4b_core::SensorState::ConstPtr& msg)
{
	double now_t = msg->header.stamp.toSec();
	if(now_t - last_t > 0.0021)
	{
		wrong_cnt++;		
		ROS_WARN("wrong_seq:%d %d\n\n",msg->header.seq,wrong_cnt);	
	}
	last_t = now_t;
	double vel=(msg->r_velocity+msg->l_velocity)/2;
	if(fabs(vel)>2)
	{
		ROS_WARN("%f:%f %f %f",msg->header.stamp.toSec(),vel,msg->r_velocity,msg->l_velocity);	
	}
	else
	{
		printf("%f:%f\n",msg->header.stamp.toSec(),vel);
	}
}

int main(int argc, char **argv)
{
	ros::init(argc,argv,"show_encoder_vel");
	printf("This is show_encoder_vel\n");
	ros::NodeHandle n;

	ros::Subscriber vel_sub = n.subscribe("/loui_robot1/sensor_state",10000,show_vel_callback);
	ros::spin();
	return 0;

}
