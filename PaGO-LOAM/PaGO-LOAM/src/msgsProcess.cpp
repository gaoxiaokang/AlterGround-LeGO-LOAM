#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include "cloud_msgs/ground_estimate.h"


cloud_msgs::ground_estimate ground_estimate_msg;


void groundCallback(const sensor_msgs::PointCloud2ConstPtr& cloud_msg)
{

  // 使用您的地面估计数据填充消息字段
  ground_estimate_msg.header = cloud_msg->header;
  ground_estimate_msg.ground = *cloud_msg;
 
  // 发布地面估计消息
  
}

void pointsCallback(const sensor_msgs::PointCloud2ConstPtr& cloud_msg)
{
 
    ground_estimate_msg.curr = *cloud_msg;
}



int main(int argc, char** argv)
{
  ros::init(argc, argv, "ground_estimate_node");
  ros::NodeHandle nh;
  ros::Publisher ground_pub;
  // 订阅点云话题
  // ros::Subscriber sub_pc_ground = nh.subscribe<sensor_msgs::PointCloud2>("patchworkpp/ground", 1, boost::bind(callback, _1, NULL));
  // ros::Subscriber sub_velodyne_points = nh.subscribe<sensor_msgs::PointCloud2>("points_raw", 1, boost::bind(callback, NULL, _1));
  ground_pub = nh.advertise<cloud_msgs::ground_estimate>("benchmark/ground_estimate", 5000);
  ros::Subscriber pc_ground_sub = nh.subscribe("patchworkpp/ground", 100, groundCallback);
  ros::Subscriber pc_points_sub = nh.subscribe("points_raw", 100, pointsCallback);
  ground_pub.publish(ground_estimate_msg);
  
  
  
  ros::spin();
  return 0;
}
