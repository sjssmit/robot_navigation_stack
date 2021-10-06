#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <stdlib.h>
#include <random>
#include <tf2/LinearMath/Quaternion.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


float randnumber(double LO, double HI){

  double r = LO + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(HI - LO)));

  return r;

};


int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  //we'll send a goal to the robot
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  srand (time(NULL));

  ros::Rate r(0.10);
  while (ros::ok())
  {
     
     goal.target_pose.pose.position.x = randnumber(-10.0, 10.0);
     goal.target_pose.pose.position.y = randnumber(-10.0, 10.0);

  
     tf2::Quaternion myQuat;
     myQuat.setRPY( 0, 0, randnumber(0.0 , 2*3.14) );
     goal.target_pose.pose.orientation.x = myQuat[0];
     goal.target_pose.pose.orientation.y = myQuat[1];
     goal.target_pose.pose.orientation.z = myQuat[2];
     goal.target_pose.pose.orientation.w = myQuat[3];
    

     ROS_INFO("Sending goal: ");
     std::cout << "Pose: x: " << goal.target_pose.pose.position.x << "  y: " << goal.target_pose.pose.position.y << "  z: " << goal.target_pose.pose.position.z << std::endl;
     std::cout << "Ornt: x: " << goal.target_pose.pose.orientation.x << "  y: " << goal.target_pose.pose.orientation.y << "  z: " << goal.target_pose.pose.orientation.z << "  w: " << goal.target_pose.pose.orientation.w << std::endl;
     ac.sendGoal(goal);

     //ac.waitForResult();

    //  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    //     ROS_INFO("Hooray, the base moved");
    //  else
    //     ROS_INFO("The base failed to move for some reason");

     r.sleep();
  }


  return 0;
}