% Create serial port object, myserialport
myserialport = serial('COM3', 'BaudRate', 115200);
% Connects serial port object, myserialport, to the device
fopen(myserialport);
% Read ASCII data from device, and format as text
fscanf(myserialport,'%i');

% disp(i)
% plot()

%Disconnect serial port object from device
fclose(myserialport);