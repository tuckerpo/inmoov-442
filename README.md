# inmoov-442
dual kinematics/graphics repository for a plug-in for the choreonoid humanoid robotics simulation tool found at choreonoid.org

done (partially) as coursework for CSE442 Software Engineering @ UB

To use our plugin first install Ubuntu 14.04 or Ubuntu 16.04

Then open a terminal and do:

sudo apt-get install git
git clone -b main https://github.com/TheNergaL/inmoov-442.git
git clone https://github.com/s-nakaoka/choreonoid.git
#At this point, ensure that you are inside the choreonoid directory
git pull
misc/script/install-requisites-ubuntu-14.04.sh #Note that this may take some time to run this script. You will also be prompted to enter your sudo password. If you are running a free virtual machine, the password should available from the publisher site. If you run Ubuntu native, enter your sudo password.
cp inmoov-442/CMakeCache.txt choreonoid
cp inmoov-442/Prototype choreonoid/sample/
#Again, ensure you are in the choreonoid directory here
cmake .
make 
#Note that this (make) will take a considerable amount of time
./bin/choreonoid
#At this point, the Choreonoid simulator should be up and running
Close the simulator, and go back to the terminal. Ensure that you are in the /choreonoid/.. directory.
Type:
ccmake .
This should open a list of possible CMake build flags. If you are instead prompted with a message to install ccmake, do so.
Navigate down the ccmake list to the BUILD_PROTOTYPE and flag it to ON by pressing the enter key (if it is not already flagged for building).
Now type:
make
This should now rebuild the project without our plug-in enabled.
Type:
./bin/choreonoid
Now the program is running with our working plug-in. To see how to interact with the GUI and get our plug-in to do something,
see the YouTube video.
If at any point you encounter an error with these commands, visit http://choreonoid.org/en/manuals/1.5/install/build-ubuntu.html 
for debugging information.

After executing these commands, follow the instructions in the youtube video.



