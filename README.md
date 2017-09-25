# InMoov-442
Dual kinematics/graphics repository for a plug-in for the choreonoid humanoid robotics simulation tool found at http://choreonoid.org

Done (partially) as coursework for CSE442 Software Engineering @ UB

## Installing our Choreonoid plugin

- ### Install Ubuntu 14.04 or Ubuntu 16.04

- ### Clone Choreonoid and our project repository:

  - Open the terminal and run

    > sudo apt-get install git

    > git clone -b main https://github.com/TheNergaL/inmoov-442.git

    > git clone https://github.com/s-nakaoka/choreonoid.git
    
- ### Install necessary libraries and update repository

  - Ensure that you are inside the choreonoid directory and run

    > git pull

    > misc/script/install-requisites-ubuntu-14.04.sh
  
    - ##### Note that this may take some time to run this script. You will also be prompted to enter your sudo password. If you are running a free virtual machine, the password should available from the publisher site. If you run Ubuntu native, enter your sudo password.

- ### Copy plugin into choreonoid directory

  - Go into the inmoov-442 directory and run

    > cp -r Prototype ~/choreonoid/sample/
    
- ### Configure Choreonoid CMAKE build flags to include plugin

  - Again, ensure you are in the choreonoid directory and run

    > cmake .
  
    > ccmake .

    - This should open a list of possible CMake build flags. If you are instead prompted with a message to install ccmake, do so.
  
    - Navigate down the ccmake list to the BUILD_PROTOTYPE and flag it to ON by pressing the ENTER key (if it is not already flagged for  building).
  
    - Save the configuration by pressing C and then generate the configuration by pressing G.
  
- ### Build and run Choreonoid

  - Again, ensure you are in the choreonoid directory here and run
  
    > make
  
      - ##### Note that this will take a considerable amount of time
      
  - Run Choreonoid after using this command

    > ./bin/choreonoid

### The Choreonoid simulator should be up and running


Now the program is running with our working plug-in. To see how to interact with the GUI and get our plug-in to do something, follow the instructions in the YouTube video found here: https://youtu.be/8YtfI-X9g58

If at any point you encounter an error with these commands, visit http://choreonoid.org/en/manuals/1.5/install/build-ubuntu.html for debugging information.




