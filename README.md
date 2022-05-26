# Arduino-Obstacle_Avoiding_Car
Make your own Obstacle Avoiding Car using Arduino

## Result
![](https://i.imgur.com/YAkwJ2G.jpg)
Video:

## What materials you need to prepare
* car model (contain wheels and car body)
* Arduino Uno
* 3 HC-SR04
* 2 18650
* 4 DC motor
* switch button
* breadbord
* some Dupont lines

## How to do it
**Hardware**
* car body
You can design any shape you want through 3D printer ,buying stuff online and so on.
* switch
If you wanna press switch button to start, you could add this function.
ps. more detail information could see code
* drive system
Control DC motor through L298N
* power system
Because you need to support Arduino and DC motor,you'd better choose high voltage and high current betteries.
I recommend you choose 2 18650.

**Software**
We have 3 HC-SR04 so we would think a strategy we will face.
1 means sensor is closing to obstacle ,and 0 means no obstacle in the following discussion.

- 000 means no obstacle so car go forward.
- 001 means obstacle is on the right side so car have to turn left.
- 010 means obstacle is in frint of car so car have to turn left.
- 011 means obstacle is on the right side and in frint of car so car have to turn left.
- 100 car have to turn right.
- 101 car have to turn forward.
- 110 car have to turn right.
- 111 car have to turn around.
