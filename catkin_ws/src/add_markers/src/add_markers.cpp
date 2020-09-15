#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h> 

//Initialize Variables
float x_odom = 0;
float y_odom = 0;
float x_dist = 0;
float y_dist = 0;
float dist = 0;
float tolerance = 0.57;

void odom_cb (const::nav_msgs::Odometry::ConstPtr& msg)
  {
   x_odom = msg->pose.pose.position.x;
   y_odom = msg->pose.pose.position.y;
   ROS_WARN_ONCE("Received Nav Messages");
  }

int main( int argc, char** argv )
{

  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odom_sub = n.subscribe("/odom", 100, odom_cb);
  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;
  uint32_t step_number = 0;
  
  while (marker_pub.getNumSubscribers() < 1)
  {
    if (!ros::ok())
    {
      return 0;
    }
    ROS_WARN_ONCE("Please create a subscriber to the marker");
    sleep(3);
  }

  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "basic_shapes";
  marker.id = 0;

  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 1.0;
  marker.scale.y = 1.0;
  marker.scale.z = 1.0;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0; 
  
// Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = shape;

  while (ros::ok())
  {
    if (step_number == 0) {
      // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
      marker.action = visualization_msgs::Marker::ADD;

      // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
      marker.pose.position.x = -2.0;
      marker.pose.position.y = 1.0;
      marker.pose.position.z = 0;
      marker.pose.orientation.x = 0.0;
      marker.pose.orientation.y = 0.0;
      marker.pose.orientation.z = 0.0;
      marker.pose.orientation.w = 1.0;

      marker_pub.publish(marker);
      step_number++;
    }
    else if (step_number == 1) {
      ROS_WARN("Picking up object...");
      sleep(1);

      x_dist = fabs(-2 - x_odom);
      y_dist = fabs(1 - y_odom);
      dist = sqrt(pow(x_dist,2) + (pow(y_dist,2)));  

   
      if(dist < tolerance){
        step_number++;
      }
    }
    else if (step_number == 2) {
      ROS_WARN_ONCE("Object is picked up!");
      sleep(1);
      marker.action = visualization_msgs::Marker::DELETE;
      marker_pub.publish(marker);
      step_number++;       
    }
    else if (step_number == 3) {
      ROS_WARN("Dropping off object...");  
      sleep(1);
          
      x_dist = fabs(3 - x_odom);
      y_dist = fabs(1 - y_odom);
      dist = sqrt(pow(x_dist,2) + (pow(y_dist,2)));


      if(dist < tolerance){
        step_number++;
      }
    }

    else if (step_number == 4) {
      ROS_WARN_ONCE("Object is dropped off!"); 
      sleep(1);
      marker.action = visualization_msgs::Marker::ADD;

      // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
      marker.pose.position.x = 3.0;
      marker.pose.position.y = 1.0;
      marker.pose.position.z = 0;
      marker.pose.orientation.x = 0.0;
      marker.pose.orientation.y = 0.0;
      marker.pose.orientation.z = 0.0;
      marker.pose.orientation.w = 1.0;

      marker_pub.publish(marker);

      step_number++;
    }
    else if (step_number == 5) {
      ROS_WARN_ONCE("Done");
      sleep(100);      
      marker.action = visualization_msgs::Marker::DELETE;      
      marker_pub.publish(marker);      
 
      break;
    }


    ros::spinOnce();

    r.sleep();
  }
}
