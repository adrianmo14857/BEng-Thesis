import os

sudoPass = 'Ares12#$'
sudocommand = 'chmod 666 /dev/ttyACM0'

os.system('echo %s|sudo -S %s' %(sudoPass,sudocommand))

os.system("gnome-terminal -x rosrun rosserial_python serial_node.py _baud:=57600 _port:=/dev/ttyACM0")

os.system("gnome-terminal -x roslaunch rplidar_ros rplidar.launch")

os.system("gnome-terminal -x roslaunch realsense2_camera rs_camera.launch")