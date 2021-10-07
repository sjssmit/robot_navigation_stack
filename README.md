# robot_navigation_stack
**Example implementation of ros navigation stack on a differential drive robot**

**Objective:** Implement Navigation stack on a differential drive robot. Publish random goal position every 10 seconds to move_base.

**Robot used:** [Husky](http://wiki.ros.org/Robots/Husky)

This project was implemented on ROS melodic running on Ubuntu 18.04. Corresponding version of gazebo was used.

Install necessary packages for Husky navigation package using :

`sudo apt-get install ros-<ros-version>-husky-navigation ros-<ros-version>-husky-gazebo ros-<ros-version>-husky-viz`

To use the packages from this repo, create a ros workspace and clone the repo and build it as follows:
```
mkdir -p ~/myros_ws/src
cd ~/myros_ws/src
git clone https://github.com/sjssmit/robot_navigation_stack.git
cd ~/myros_ws
catkin_make
```
Source the environment using:
`source devel/setup.bash`

launch the gazebo, rviz and all the nodes using
`roslaunch robot robot.launch`

Yay! if everything works good, then gazebo and rviz will launch and random goals will be published every 10 seconds and the robot will move to achieve it.

If you are getting no laser scan recieved error, then it implies that Husky robot laser sensor is disabled. To enable this, change the environment variable to true (1), in  husky.urdf.xacro file found in 

`/opt/ros/<ros-version>/share/husky_description/urdf/husky.urdf.xacro`  
such that the final form looks like:

`<xacro:arg name="laser_enabled" default="$(optenv HUSKY_LMS1XX_ENABLED 1)" />`

### Acknowledgment
[ClearpathRobotics](http://wiki.ros.org/ClearpathRobotics)
