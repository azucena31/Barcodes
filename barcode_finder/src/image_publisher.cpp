#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("barcode/image", 1);
  cv::Mat image = cv::imread(argv[1],  // "/home/azucena/barcode/images_2/image_2.jpg"
    CV_LOAD_IMAGE_COLOR);
  cv::waitKey(30);
  sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(),
    "rgb8", image).toImageMsg();

  ros::Duration(0.5).sleep();
  pub.publish(msg);
  ros::spin();
  return 0;
}
   
