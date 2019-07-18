loop=0;
while loop==0
     loop=license('checkout','Robotics_System_Toolbox');
     if loop==0
             'license_error:'
     end
     pause(30);
end

trajectory_optimation_srv;
testclient = rossvcclient('/matlab_srv/trj_opt_server')
opt_req=rosmessage(testclient)
opt_req.StartPose.Position.X=0.35;
opt_req.StartPose.Position.Y=0.35;
opt_req.StartPose.Position.Z=0.1;
opt_req.StartPose.Orientation.X=2.5436;
opt_req.StartPose.Orientation.Y=-1.9955;
opt_req.StartPose.Orientation.Z=2.5236;
opt_req.GoalPose.Position.X=0.35;
opt_req.GoalPose.Position.Y=-0.35;
opt_req.GoalPose.Position.Z=0.1;
opt_req.GoalPose.Orientation.X=2.5436;
opt_req.GoalPose.Orientation.Y=-1.9955;
opt_req.GoalPose.Orientation.Z=2.5236;
opt_req.Time.Data=4;
testresp = call(testclient,opt_req)