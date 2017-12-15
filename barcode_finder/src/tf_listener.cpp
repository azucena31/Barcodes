#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <visualization_msgs/Marker.h>
#include "std_msgs/String.h"

//Messages from the REFILLS project
#include <refills_msgs/Barcode.h>

#include <fstream>
using namespace std;
ofstream myfile;

int main(int argc, char** argv){

  ros::init(argc, argv, "tf_listener");
  ros::NodeHandle node;
   

  myfile.open("/home/azucena/barcode/listener.txt", std::ofstream::out | std::ofstream::trunc);

  tf::TransformListener listener;

  ros::Rate rate(10.0);
  while (node.ok()){
  
  ros::Time stamp_time;
  tf::StampedTransform transform;

    try{

      listener.waitForTransform("/shelf", "/barcode", ros::Time(0), ros::Duration(0.1));
      listener.lookupTransform("/shelf", "/barcode", ros::Time(0), transform);
      stamp_time = transform.stamp_;
  
      myfile << stamp_time << " ";
      myfile << transform.getOrigin().x() *100 << " ";
      myfile << transform.getOrigin().y() *100 << " ";
      myfile << transform.getOrigin().z() *100 << "\n";

    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
      ros::Duration(0.1).sleep();
    }

    rate.sleep();
  }

myfile.close();

  return 0;
};
