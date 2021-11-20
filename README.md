# Build

## Install CUDA 10.2 (Ubuntu 18.04)

```
wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/cuda-ubuntu1804.pin
sudo mv cuda-ubuntu1804.pin /etc/apt/preferences.d/cuda-repository-pin-600
wget https://developer.download.nvidia.com/compute/cuda/10.2/Prod/local_installers/cuda-repo-ubuntu1804-10-2-local-10.2.89-440.33.01_1.0-1_amd64.deb
sudo dpkg -i cuda-repo-ubuntu1804-10-2-local-10.2.89-440.33.01_1.0-1_amd64.deb
sudo apt-key add /var/cuda-repo-10-2-local-10.2.89-440.33.01/7fa2af80.pub
sudo apt-get update
sudo apt-get -y install cuda
```

## Install ZED SDK (version 3.5)

Download SDK from this [link](https://www.stereolabs.com/developers/release/)

Run:

```
sudo chmod +x ZED...
./ZED...
```

### Realsense SDK

Run script in script folder (from JetsonHack)

[Link](https://github.com/IntelRealSense/realsense-ros)

## Clone this repo and build
```
catkin_make -DCMAKE_BUILD_TYPE=Release
```
# Run


```
roslaunch realsense2_camera rs_t265.launch
 roslaunch zed_wrapper zed2.launch
roslaunch data_collection data_collection.launch

```

## rosbag command line
```
rosbag record /ZED_2/zed2/zed_node/stereo/image_rect_color /ZED_2/zed2/zed_node/imu/data /ublox_rtk -O data.bag

rosbag record /ZED_2/zed2/zed_node/left_raw/image_raw_color /ZED_2/zed2/zed_node/right_raw/image_raw_color /ZED_2/zed2/zed_node/imu/data_raw /ublox_rtk -O data.bag

rosbag record /camera/odom/sample /camera/accel/sample /camera/gyro/sample /zed2/zed_node/odom /zed2/zed_node/imu/data_raw /zed2/zed_node/left/image_rect_color /zed2/zed_node/right/image_rect_color /zed2/zed_node/depth/depth_registered /ublox_rtk -O data.bag

```
