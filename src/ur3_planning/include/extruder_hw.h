#include <ros/ros.h>
#include "rosbag/bag.h"

class extruder {
private:
  double fan_speed; //Values from 0-255
  double feed_rate;
  double temperature; //desired temperature in °c
  double actual_temp; //actual temperature in °C
  bool state;         //state of extruder on/off

public:
  extruder (arguments);
  virtual ~extruder ();

  void on();
  void off();
  void set_fan_speed(double speed);
  void set_temperature(double temp);
  void set_feed_rate(double fdrate);
  double get_actual_temp();
  double get_temperature(){return temperature;}
  double get_feed_rate(){return feed_rate;}
  double get_fan_speed(){return fan_speed;}
  bool get_state(){return state;}
  void async_feed(bool f);
  void sync_feed(double feedtime);

};
void extruder::set_fan_speed(double speed){
  if (state==true) {
    if (speed>255){speed=255;}
    if (speed<0){speed=0;}
    fan_speed=speed;
    //TODO
    //send to Fan_controller
  }
  else {
    ROS_INFO("extruder is off! Turn state to true");
  }
}

void extruder::set_temperature(double temp){
  if (state==true) {
    if (temp>300){temp=300;}
    if (temp<0){temp=0;}
    temperature=temp;
    //TODO
    //send to temperature_controller
    }
  else {
    ROS_INFO("extruder is off! Turn state to true");
  }
}
void extruder::set_feed_rate(double fdrate){
  //if (fdrate>300){fdrate=300;}
  //if (fdrate<0){fdrate=0;}
  feed_rate=fdrate;
}
double extruder::get_actual_temp(){
  double current_temp;
  //TODO
  //read_from temperature_controller
  return current_temp;
}
void extruder::on(){
  state=true;
  //check for controllers
}
void extruder::off(){
  state=false;
  //stop all controllers
}
void extruder::async_feed(bool f){
  if (state==true) {
    if (f==true){
      //start feeding with feed_rate
    }
    else {
      //stop feeding
    }
  }
  else{
    ROS_INFO("extruder is off! Turn state to true");
  }
}
void extruder::sync_feed(double feedtime){
if (state==true) {
  if (f==true){
    //start feeding with for feedtime
    }
    else {
    //stop feeding
    }
  }
  else{
  ROS_INFO("extruder is off! Turn state to true");
  }
}
