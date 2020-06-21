fileID = fopen('X_FUNC_1_1.txt','r');
formatSpec = '%f';
x = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_FUNC_1_1.txt','r');
formatSpec = '%f';
y = fscanf(fileID,formatSpec);
fclose(fileID);

figure
plot(x,y)
title('Funkcja p(t) dla N=2, A = 8, B = 1, C = 3')
xlabel('t')
ylabel('p(t)')

%AMPLITUDE MODULATION


fileID = fopen('X_FUNC_1_2.txt','r');
formatSpec = '%f';
a = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_FUNC_1_2.txt','r');
formatSpec = '%f';
b = fscanf(fileID,formatSpec);
fclose(fileID);

figure
plot(a,b)
title('Modulacja amplitudy dla p(t) dla N=2, A = 8, B = 1, C = 3,ka=0.5,kp=0.5')
xlabel('t')
ylabel('p(t)')

%PHASE MODULATION


fileID = fopen('X_FUNC_1_3.txt','r');
formatSpec = '%f';
c = fscanf(fileID,formatSpec);
fclose(fileID);
%Y_FUNC_1_3.txt
fileID = fopen('Y_FUNC_1_3.txt','r');
formatSpec = '%f';
d = fscanf(fileID,formatSpec);
fclose(fileID);

figure
plot(c,d)
title('Modulacja fazy dla p(t) dla N=2, A = 8, B = 1, C = 3,ka=0.5,kp=0.5')
xlabel('t')
ylabel('p(t)')

%PHASE SPECTRUM
fileID = fopen('X_FUNC_1_4.txt','r');
formatSpec = '%f';
a = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_FUNC_1_4.txt','r');
formatSpec = '%f';
b = fscanf(fileID,formatSpec);
fclose(fileID);

figure
bar(a,b)
title('Widmo zp(t) , A = 8, B = 1, C = 3,ka=0.5,kp=0.5')
xlabel('f[Hz]')
ylabel('Amplituda')

%AMPLITUDE SPECTRUM


fileID = fopen('X_FUNC_1_5.txt','r');
formatSpec = '%f';
a = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_FUNC_1_5.txt','r');
formatSpec = '%f';
b = fscanf(fileID,formatSpec);
fclose(fileID);

figure
bar(a,b)
title('Widmo za(t), A = 8, B = 1, C = 3,ka=0.5,kp=0.5')
xlabel('f[Hz]')
ylabel('Amplituda')





%FUNC 2 






%INFORMATION SIGNAL

fileID = fopen('X_FUNC_2_1.txt','r');
formatSpec = '%f';
x = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_FUNC_2_1.txt','r');
formatSpec = '%f';
y = fscanf(fileID,formatSpec);
fclose(fileID);

figure
plot(x,y)
title('Funkcja p(t) dla N=2, A = 8, B = 1, C = 3,ka=6,kp=2')
xlabel('t')
ylabel('p(t)')

%AMPLITUDE MODULATION


fileID = fopen('X_FUNC_2_2.txt','r');
formatSpec = '%f';
a = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_FUNC_2_2.txt','r');
formatSpec = '%f';
b = fscanf(fileID,formatSpec);
fclose(fileID);

figure
plot(a,b)
title('Modulacja amplitudy dla p(t) dla N=2, A = 8, B = 1, C = 3,ka=6,kp=2')
xlabel('t')
ylabel('p(t)')

%PHASE MODULATION


fileID = fopen('X_FUNC_2_3.txt','r');
formatSpec = '%f';
c = fscanf(fileID,formatSpec);
fclose(fileID);
%Y_FUNC_1_3.txt
fileID = fopen('Y_FUNC_2_3.txt','r');
formatSpec = '%f';
d = fscanf(fileID,formatSpec);
fclose(fileID);

figure
plot(c,d)
title('Modulacja fazy dla p(t) dla N=2, A = 8, B = 1, C = 3,ka=6,kp=2')
xlabel('t')
ylabel('p(t)')

%AMPLITUDE SPECTRUM
fileID = fopen('X_FUNC_2_4.txt','r');
formatSpec = '%f';
a = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_FUNC_2_4.txt','r');
formatSpec = '%f';
b = fscanf(fileID,formatSpec);
fclose(fileID);

figure
bar(a,b)
title('Widmo zp(t) , A = 8, B = 1, C = 3,ka=6,kp=2')
xlabel('f[Hz]')
ylabel('Amplitude')

%PHASE SPECTRUM


fileID = fopen('X_FUNC_2_5.txt','r');
formatSpec = '%f';
a = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_FUNC_2_5.txt','r');
formatSpec = '%f';
b = fscanf(fileID,formatSpec);
fclose(fileID);

figure
bar(a,b)
title('Widmo za(t), A = 8, B = 1, C = 3,ka=6,kp=2')
xlabel('f[Hz]')
ylabel('Amplituda')



%FUNC 3



%INFORMATION SIGNAL

fileID = fopen('X_FUNC_3_1.txt','r');
formatSpec = '%f';
x = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_FUNC_3_1.txt','r');
formatSpec = '%f';
y = fscanf(fileID,formatSpec);
fclose(fileID);

figure
plot(x,y)
title('Funkcja p(t) dla N=2, A = 8, B = 1, C = 3,ka=100,kp=25')
xlabel('t')
ylabel('p(t)')

%AMPLITUDE MODULATION


fileID = fopen('X_FUNC_3_2.txt','r');
formatSpec = '%f';
a = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_FUNC_3_2.txt','r');
formatSpec = '%f';
b = fscanf(fileID,formatSpec);
fclose(fileID);

figure
plot(a,b)
title('Modulacja amplitudy dla p(t) dla N=2, A = 8, B = 1, C = 3,ka=100,kp=25')
xlabel('t')
ylabel('p(t)')

%PHASE MODULATION


fileID = fopen('X_FUNC_3_3.txt','r');
formatSpec = '%f';
c = fscanf(fileID,formatSpec);
fclose(fileID);
%Y_FUNC_1_3.txt
fileID = fopen('Y_FUNC_3_3.txt','r');
formatSpec = '%f';
d = fscanf(fileID,formatSpec);
fclose(fileID);

figure
plot(c,d)
title('Modulacja fazy dla p(t) dla N=2, A = 8, B = 1, C = 3,ka=100,kp=25')
xlabel('t')
ylabel('p(t)')

%AMPLITUDE SPECTRUM
fileID = fopen('X_FUNC_3_4.txt','r');
formatSpec = '%f';
a = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_FUNC_3_4.txt','r');
formatSpec = '%f';
b = fscanf(fileID,formatSpec);
fclose(fileID);

figure
bar(a,b)
title('Widmo zp(t) , A = 8, B = 1, C = 3,ka=100,kp=25')
xlabel('f[Hz]')
ylabel('Amplituda')

%PHASE SPECTRUM


fileID = fopen('X_FUNC_3_5.txt','r');
formatSpec = '%f';
a = fscanf(fileID,formatSpec);
fclose(fileID);

fileID = fopen('Y_FUNC_3_5.txt','r');
formatSpec = '%f';
b = fscanf(fileID,formatSpec);
fclose(fileID);

figure
bar(a,b)
title('Widmo za(t), A = 8, B = 1, C = 3,ka=100,kp=25')
xlabel('f[Hz]')
ylabel('Amplituda')