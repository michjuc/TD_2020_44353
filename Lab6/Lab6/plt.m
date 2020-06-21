%CLK
fileID = fopen('X_CLK.txt','r');
formatSpec = '%f';
x = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_CLK.txt','r');
formatSpec = '%f';
y = fscanf(fileID,formatSpec);
fclose(fileID);

figure
stairs(x,y,'b','Linewidth',1.5)
title({'Sygna? CLK'})
xlabel('t[s]')
ylabel('CLK')
ylim([-2,2])

%TTL
fileID = fopen('X_TTL.txt','r');
formatSpec = '%f';
x = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_TTL.txt','r');
formatSpec = '%f';
y = fscanf(fileID,formatSpec);
fclose(fileID);

figure
stairs(x,y,'b','Linewidth',1.5)
title({'Sygna? TTL'})
xlabel('t[s]')
ylabel('TTL')
ylim([-2,2])

%Manchester
fileID = fopen('X_MAN.txt','r');
formatSpec = '%f';
x = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_MAN.txt','r');
formatSpec = '%f';
y = fscanf(fileID,formatSpec);
fclose(fileID);

figure
stairs(x,y,'b','Linewidth',1.5)
title({'Sygna? Manchester'})
xlabel('t[s]')
ylabel('Manchester')
ylim([-2,2])