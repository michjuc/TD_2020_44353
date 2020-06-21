%information signal
fileID = fopen('X_INF.txt','r');
formatSpec = '%f';
x = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_INF.txt','r');
formatSpec = '%f';
y = fscanf(fileID,formatSpec);
fclose(fileID);

figure
stairs(x,y)
title({'Sygna? informacyjny m(t) dla liter A-Z','fs=100Hz,A=1,Tb=1s,fi=pi','10 bitów'})
xlabel('t')
ylabel('m(t)')

%TEN BITS

%ask modulation
fileID = fopen('X_ASK_NORM.txt','r');
formatSpec = '%f';
x = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_ASK_NORM.txt','r');
formatSpec = '%f';
y = fscanf(fileID,formatSpec);
fclose(fileID);

figure
plot(x,y)
title({'Kluczowanie amplitudy m(t) dla liter A-Z','fs=100Hz,A=1,Tb=1s,fi=pi','10 bitów'})
xlabel('t')
ylabel('za(t)')



%fsk modulation
fileID = fopen('X_FSK_NORM.txt','r');
formatSpec = '%f';
x = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_FSK_NORM.txt','r');
formatSpec = '%f';
y = fscanf(fileID,formatSpec);
fclose(fileID);

figure
plot(x,y)
title({'Kluczowanie cz?stotliwo?ci m(t) dla liter A-Z','fs=100Hz,A=1,Tb=1s,fi=pi','10 bitów'})
xlabel('t')
ylabel('zf(t)')



%psk modulation
fileID = fopen('X_PSK_NORM.txt','r');
formatSpec = '%f';
x = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_PSK_NORM.txt','r');
formatSpec = '%f';
y = fscanf(fileID,formatSpec);
fclose(fileID);

figure
plot(x,y)
title({'Kluczowanie fazy m(t) dla liter A-Z','fs=100Hz,A=1,Tb=1s,fi=pi','10 bitów'})
xlabel('t')
ylabel('zp(t)')

%WHOLE SIGNAL


%ask modulation
fileID = fopen('X_ASK_whl.txt','r');
formatSpec = '%f';
x = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_ASK_whl.txt','r');
formatSpec = '%f';
y = fscanf(fileID,formatSpec);
fclose(fileID);

figure
plot(x,y)
title({'Kluczowanie amplitudy m(t) dla liter A-Z','fs=100Hz,A=1,Tb=1s,fi=pi','Ca?y sygna?'})
xlabel('t')
ylabel('za(t)')



%fsk modulation
fileID = fopen('X_FSK_whl.txt','r');
formatSpec = '%f';
x = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_FSK_whl.txt','r');
formatSpec = '%f';
y = fscanf(fileID,formatSpec);
fclose(fileID);

figure
plot(x,y)
title({'Kluczowanie cz?stotliwo?ci m(t) dla liter A-Z','fs=100Hz,A=1,Tb=1s,fi=pi','Ca?y sygna?'})
xlabel('t')
ylabel('zf(t)')



%psk modulation
fileID = fopen('X_PSK_whl.txt','r');
formatSpec = '%f';
x = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_PSK_whl.txt','r');
formatSpec = '%f';
y = fscanf(fileID,formatSpec);
fclose(fileID);

figure
plot(x,y)
title({'Kluczowanie fazy m(t) dla liter A-Z ','fs=100Hz,A=1,Tb=1s,fi=pi','Ca?y sygna?'})
xlabel('t')
ylabel('zp(t)')



%SPECTURMS




%ask spectrum
fileID = fopen('X_ASK_SPEC.txt','r');
formatSpec = '%f';
x = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_ASK_SPEC.txt','r');
formatSpec = '%f';
y = fscanf(fileID,formatSpec);
fclose(fileID);

figure
bar(x,y)
title({'Widmo amplitudowe za(t) dla liter A-Z','fs=100Hz,A=1,Tb=1s,fi=pi'})
xlabel('f[Hz]')
ylabel('Amplituda')


%fsk spectrum
fileID = fopen('X_FSK_SPEC.txt','r');
formatSpec = '%f';
x = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_FSK_SPEC.txt','r');
formatSpec = '%f';
y = fscanf(fileID,formatSpec);
fclose(fileID);

figure
bar(x,y)
title({'Widmo amplitudowe zf(t) dla liter A-Z','fs=100Hz,A=1,Tb=1s,fi=pi'})
xlabel('f[Hz]')
ylabel('Amplituda')


%psk spectrum
fileID = fopen('X_PSK_SPEC.txt','r');
formatSpec = '%f';
x = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_PSK_SPEC.txt','r');
formatSpec = '%f';
y = fscanf(fileID,formatSpec);
fclose(fileID);

figure
bar(x,y)
title({'Widmo amplitudowe zp(t) dla liter A-Z','fs=100Hz,A=1,Tb=1s,fi=pi'})
xlabel('f[Hz]')
ylabel('Amplituda')