
rosinit('http://frederic:11311/')
chatpub = rospublisher('/chatter','std_msgs/String');
msg.Data = '1test ph5ase';
send(chatpub,msg);
pause(0.1);
rosshutdown;