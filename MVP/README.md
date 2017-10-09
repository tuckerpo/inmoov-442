# MVP Plugin
- Move entire MVP folder into choreonoid/sample
- Use "cmake ." then "ccmake ." and turn flag BUILD_InMoovPlugin to ON
- Press "C" to configure and "G" to generate
- Use "make" to build choreonoid
- Open choreonoid in choreonoid/bin and load the project InMoov.cnoid in choreonoid/sample/MVP
- Plugin and models should now be loaded

  - Plugin buttons are on the toolbar of choreonoid near the top
  - Buttons must be pressed multiple times to continue walking simulation

  - "SR1" buttons can only be used with the SR1 model. Use it by clicking on SR1 on the left of choreonoid to highlight it.
  - "SR1 Walk" simulates a walking animation for SR1 model.
  - "SR1 RotateRLEG" rotates SR1 model's right leg counter clockwise.
  - "SR1 RotateLLEG" rotates SR1 model's left leg counter clockwise.

  - "LEGS" buttons must be used with the LEGS model. Use it by clicking on LEGS on the left of choreonoid to highlight it.
  - "LEGS Walk" simulates a walking animation for LEGS model.
  - "LEGS Reset" resets the LEGS model back to neutral/standing position.
