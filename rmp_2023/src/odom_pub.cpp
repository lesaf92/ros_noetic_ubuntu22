// Simulated odometry publisher
// Assumes that the robot follows the given velocity commands 
// Basically read in the velocity command values and then transmit them as 
// odometry
// 


#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>

double vx = 0.0;
double vy = 0.0;
double vth = 0.00;

// Initialize a callback to get velocity values:
//
void Odocallback( const geometry_msgs::TwistConstPtr& cmd_vel) {

  ROS_INFO( "Velocity_Recieved_by_OdomNode");
  vx = cmd_vel->linear.x;
  vy = cmd_vel->linear.y;
  vth = cmd_vel->angular.z;

}


int main( int argc, char** argv) {

  ros::init(argc, argv, "odometry_publisher");

  ros::NodeHandle n;
  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
  ros::Subscriber sub = n.subscribe("cmd_vel", 1000, Odocallback);
  tf::TransformBroadcaster odom_broadcaster;

  double x = 0.0;
  double y = 0.0;
  double th = 0.0;

  //double vx = 0.0;
  //double vy = 0.0;
  //double vth = 0.0;

  ros::Time current_time, last_time;
  current_time = ros::Time::now();
  last_time = ros::Time::now();


  //ros::spin();
  ros::Rate r(20.0);
  while (n.ok()) {


    current_time = ros::Time::now();
    //vx = cmd_vel.linear.x;
    ///vy = cmd_vel.linear.y;
    //vth = cmd_vel.angular.z;

    double dt = (current_time - last_time).toSec();
    double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
    double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
    double delta_th = vth * dt;

    x += delta_x ;
    y += delta_y ;
    th += delta_th;

    // odometry is 6DOF so we'll need a quaternion created from yaw
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

    // first, we'll publish the transform over tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    odom_trans.transform.translation.x = x;
    odom_trans.transform.translation.y = y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    // send the transform
    odom_broadcaster.sendTransform(odom_trans);

    // next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    // set the position
    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    // set the velocity
    odom.child_frame_id = "base_link";
    odom.twist.twist.linear.x = vx;
    odom.twist.twist.linear.y = vy;
    odom.twist.twist.angular.z = vth;

    // publish the message
    odom_pub.publish(odom);

    last_time = current_time;

    ros::spinOnce();
    r.sleep();
   }

}
