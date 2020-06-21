ileID = fopen('X_VALUES.txt','r');
formatSpec = '%f';
x = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('ASK_VALUES.txt','r');
formatSpec = '%f';
y = fscanf(fileID,formatSpec);
fclose(fileID);

figure
plot(x,y,'b')
title({'ASK_VALUES'})

fileID = fopen('X_VALUES.txt','r');
formatSpec = '%f';
x = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('ASK_INTEGRAL.txt','r');
formatSpec = '%f';
y = fscanf(fileID,formatSpec);
fclose(fileID);

figure
plot(x,y,'b')
title({'INTEGRAL ASK'})

fileID = fopen('X_VALUES.txt','r');
formatSpec = '%f';
x = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('ASK_MODIFIED.txt','r');
formatSpec = '%f';
y = fscanf(fileID,formatSpec);
fclose(fileID);
 
figure
plot(x,y,'b')
title({'MODIFIED ASK'})



