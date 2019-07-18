#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ros/ros.h>
#include <cstring>
#include <iostream>
#include <rosbag/bag.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Int16MultiArray.h>

#include <rosbag/view.h>
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH


std::vector<geometry_msgs::Pose> LayerPoints;
std::vector<double> TCPvelocity;
std::vector<double> TCPaccelration;
std::vector<double> HotendTemp;
std::vector<float> extrudelength;
std::vector<short int> process_step;
short int p_s;
geometry_msgs::Pose lp;
//
float exl;
float vel;
float acc;
float he_temp;

bool extrude=false;
std::string::size_type sz;     // alias of size_t

using namespace std;

vector<string> split(char* str,const char* delim)
{
    char* saveptr;
    char* token = strtok_r(str,delim,&saveptr);

    vector<string> result;

    while(token != NULL)
    {
        result.push_back(token);
        token = strtok_r(NULL,delim,&saveptr);
    }
    return result;
}

int main () {
  string line;
  const char *delimiter=" ";
  //char moveMsg="G1";
  lp.position.y=250.0;
  ifstream gcodefile ("/home/frederic/Documents/G-Codes/MonigluSmall.gcode");
  if (gcodefile.is_open())
  {
    int n=0;
    while ( getline (gcodefile,line))
    {
      //cout << "line number:" << '\n';
      //cout << n << '\n';
      //getline (gcodefile,line);
      if (line.size()!=0){
        char cline[line.size()+1];
        strcpy(cline,line.c_str());
        vector<string> line_members=split(cline,delimiter);
        //cout << line << '\n';
        //cout << line_members[0].c_str() << '\n';
        if (line_members[0]=="G1") {//move command
          //cout << line_members[0].c_str() << '\n';
          for (int i=1;i<line_members.size();i++){
            if ( line_members[i].at(0)=='X'){
              //cout << lp << '\n';
              lp.position.x=stof(line_members[i].substr(1,line_members[i].length()),&sz);
            }
            if ( line_members[i].at(0)=='Y'){
              lp.position.y=stof(line_members[i].substr(1,line_members[i].length()),&sz);
            }
            if ( line_members[i].at(0)=='Z'){
              lp.position.z=stof(line_members[i].substr(1,line_members[i].length()),&sz);
            }
            if ( line_members[i].at(0)=='E'){
              extrude=true;
              exl=stof(line_members[i].substr(1,line_members[i].length()),&sz);
            }
            if ( line_members[i].at(0)=='F'){
              vel=stof(line_members[i].substr(1,line_members[i].length()),&sz);
            }
          }
          if (extrude){
            extrude=false;
            p_s=1;
          }
          else{p_s=0;}

        }

        else {
          if (line_members[0]==";"){
            //can safe some comments here;
          }
          if (line_members[0]=="M104"){//set extruder temperature
            p_s=104;
            he_temp=stof(line_members[1].substr(1,line_members[1].length()),&sz);
          }
          if (line_members[0]=="M106"){//set fan speed
            p_s=106;
          }
          if (line_members[0]=="G28"){//startposition
            p_s=28;
          }
          if (line_members[0]=="M107"){//set fan speed to zero
            p_s=107;
          }
          if (line_members[0]=="M109"){//wait for temperature reached
            p_s=109;
          }
          if (line_members[0]=="G92"){//set position no move
            p_s=92;
            if ( line_members[1].at(0)=='E'){
            exl=stof(line_members[1].substr(1,line_members[1].length()),&sz);
            //cout << "G92: exl:"<< '\n';
            //cout << exl<< '\n';
          }}
          if (line_members[0]=="M204"){//set acceleration
            p_s=204;
          }
          if (line_members[0]=="M84"){//disable motors
            p_s=84;
            //acc=stof(line_members[1].substr(1,line_members[1].length()),&sz);
          }
        }
        process_step.push_back(p_s);
        TCPvelocity.push_back(vel);
        TCPaccelration.push_back(acc);
        HotendTemp.push_back(he_temp);
        extrudelength.push_back(exl);
        LayerPoints.push_back(lp);
    }
    n+=1;
  }}
    gcodefile.close();
cout << "create_msgs..."<<'\n';
    std_msgs::Float64MultiArray   TCPvelocity_msg;
    std_msgs::Float64MultiArray   TCPaccelration_msg;
    std_msgs::Float64MultiArray   HotendTemp_msg;
    std_msgs::Float32MultiArray   extrudelength_msg;
    std_msgs::Int16MultiArray   process_msg;
    geometry_msgs::PoseArray LayerPoints_msg;
cout << "write msgs..."<<'\n';
    process_msg.data=process_step;
    LayerPoints_msg.poses=LayerPoints;
    TCPvelocity_msg.data=TCPvelocity;
    TCPaccelration_msg.data=TCPaccelration;
    HotendTemp_msg.data=HotendTemp;
    extrudelength_msg.data=extrudelength;
cout << "msg_written"<<'\n';
    //cout << extrudelength_msg<< '\n';
    ros::Time::init();
    rosbag::Bag bag;
    bag.open("Pointbag_test.bag", rosbag::bagmode::Write);
    cout << "ROSBAG OPEN"<<'\n';
    bag.write("Points",ros::Time::now(), LayerPoints_msg);
    bag.write("Acceleration", ros::Time::now(), TCPaccelration_msg);
    bag.write("HotendTemp", ros::Time::now(), HotendTemp_msg);
    bag.write("Velocity",ros::Time::now(),TCPvelocity_msg);
    bag.write("Extruderlength", ros::Time::now(), extrudelength_msg);
    bag.write("Process_step", ros::Time::now(), process_msg);

   bag.close();
   cout << "ROSBAG Closed"<<'\n';
//cout << TCPvelocity.size() << '\n';
//cout << TCPaccelration.size() << '\n';
//cout << extrudelength.size() << '\n';
//cout << LayerPoints.size() << '\n';
for (size_t i = 0; i < 200; i++) {
  cout << extrudelength[i] << '\n';
}

  return 0;
}
