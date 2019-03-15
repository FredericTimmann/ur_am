#include <iostream>
#include <fstream>
#include <string>
#include <ros/ros.h>
#include <cstring>
#include <iostream>
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
  ifstream gcodefile ("/home/frederic/Documents/G-Codes/cube/20mm_cube.gcode");
  if (gcodefile.is_open())
  {
    while ( getline (gcodefile,line) )
    {
      if (line.size()!=0){
        char cline[line.size()+1];
        strcpy(cline,line.c_str());
        vector<string> line_members=split(cline,delimiter);
        //cout << line << '\n';
        //cout << line_members[0].c_str() << '\n';
        if (line_members[0]=="G1") {//move command
          //cout << line_members[0].c_str() << '\n';
          for (int i=1;i<line_members.size();i++){
            if (line_members[i].length()>3){
            //cout << line_members[i].at(2) << '\n';}}}
            cout << line_members[i].c_str() << '\n';}}}
        else if (line_members[0]==";"){}
        else {
          if (line_members[0]=="M101"){//extruder on
          }
          if (line_members[0]=="M103"){//extruder off
          }
          if (line_members[0]=="G28"){//startposition
          }
          if (line_members[0]=="M73"){//process percent
          }
          if (line_members[0]=="M204"){//acceleration
          }
        }

    }
    }
    gcodefile.close();

}
  else cout << "Unable to open file";
  return 0;
}
