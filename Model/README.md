# Plugin for Model
- Move InMoovPlugin folder into choreonoid/sample
- Use ccmake to turn the flag BUILD_PROTOTYPE_INMOOV to on
- Configure and generate
- Use make to rebuild choreonoid
- Open choreonoid and load the project InMoov.cnoid
- Plugin and model should be loaded with two buttons "Walk" and "Reset"
  - Must press "Walk" multiple times to see complete walking simulation
  - "Reset" button resets the model back to neutral/standing position
