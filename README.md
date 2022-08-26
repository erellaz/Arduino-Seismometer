# Arduino Seismometer
Arduino based seismometer.
- Arduino ZeroMkr board (with SD Card slot for records saving), ZeroMKR board also has the highest (12 bits) Analog to Digital converter resolution of all current boards.
- GPS-MKR shield for precise timing of the events recorded and position of the module 
- External voltage divider to read both positive and negative voltage from the Geophone, as the Arduinos otherwise only reads positive voltage.

This project would deserve a complete write up and an "instructable" presentation. In the meantime, the main sketches and scripts are here.

![Tension diviser sketch - very simple](ArduinoSeis_clean.jpg)
![Operational amplifier sketch - slightly more advanced but better performances](Arduino_seismograph1.jpg)
![Operational amplifier sketch - 3 or 4 channels, for 3 geophone components + hydrophone component](Arduino_seismograph2.jpg)
!Capacitor sketch- an alternative , simple high impedence solution](Arduino_seismograph3.jpg)



