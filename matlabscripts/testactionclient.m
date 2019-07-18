[client,goalMsg] = rosactionclient('/trajectory_execution');
goalMsg.StartPose.Position.X=0.3
goalMsg.StartPose.Position.Y=0.1;
goalMsg.StartPose.Position.Z=0.1;
goalMsg.StartPose.Orientation.X=2.4;
goalMsg.StartPose.Orientation.Y=-2.4;
goalMsg.StartPose.Orientation.Z=2.4;
goalMsg.GoalPose.Position.X=0.3;
goalMsg.GoalPose.Position.Y=0.0;
goalMsg.GoalPose.Position.Z=0.1;
goalMsg.GoalPose.Orientation.X=2.4;
goalMsg.GoalPose.Orientation.Y=-2.4;
goalMsg.GoalPose.Orientation.Z=2.4;
goalMsg.VelocityVector=ones(1,200)*0.07;
goalMsg.Frequenz=50;

[resultMsg,state,status] = sendGoalAndWait(client,goalMsg)
