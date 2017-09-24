# inmoov-442
dual kinematics/graphics repository for a plug-in for the choreonoid humanoid robotics simulation tool found at choreonoid.org

done (partially) as coursework for CSE442 Software Engineering @ UB

To use our plugin first install Ubuntu 14.04 or Ubuntu 16.04

Then open a terminal and do:

sudo apt-get install git
git clone -b main https://github.com/TheNergaL/inmoov-442.git
git clone https://github.com/s-nakaoka/choreonoid.git
git pull
misc/script/install-requisites-ubuntu-14.04.sh #Note that this may take some time to run this script
cp inmoov-442/CMakeCache.txt choreonoid
cp inmoov-442/Prototype choreonoid/sample/
cd choreonoid
cmake ..
make #Note that this will take a considerable amount of time
./bin/choreonoid

After executing these commands, follow the instructions in the youtube video.



