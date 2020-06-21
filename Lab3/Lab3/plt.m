
fileID = fopen('X_0_1.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);

fileID = fopen('Y_0_1.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);
 
figure
plot(x,y)
title('Funkcja s(t), A = 8, B = 1, C = 3, fs=271[Hz],n=813')
xlabel('t')
ylabel('s(t)')
 
fileID = fopen('X_0_2.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);
 
fileID = fopen('Y_0_2.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);
 
figure
bar(x,y)
title('DFT(s(t)), A = 8, B = 1, C = 3, fs=271[Hz],n=813')
xlabel('Cz?stotliwo??[Hz]')
ylabel('Amplituda')
 
fileID = fopen('X_0_3.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);

fileID = fopen('Y_0_3.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);

figure
bar(x,y)
title('Wyznaczenie widma w skali decybelowej s(t)')
xlabel('Cz?stotliwo?c[Hz]')
ylabel('Amplituda')

fileID = fopen('X_0_4.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);
 
fileID = fopen('Y_0_4.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);
 
figure
plot(x,y)
title('Funkcja s(t) IDFT, A = 8, B = 1, C = 3, fs=271[Hz],n=813')
xlabel('t')
ylabel('s(t)')
 

% FUNKCJA X<---------------------------------------------------------------


fileID = fopen('X_1_1.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);

fileID = fopen('Y_1_1.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);

figure
plot(x,y)
title('Funkcja x(t), A = 8, B = 1, C = 3, fs=271[Hz],n=813')
xlabel('t')
ylabel('x(t)')

fileID = fopen('X_1_2.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);
 
fileID = fopen('Y_1_2.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);
 
figure
bar(x,y)
title('DFT(x(t)), A = 8, B = 1, C = 3, fs=271[Hz],n=813')
xlabel('Cz?stotliwo??[Hz]')
ylabel('Amplituda')

fileID = fopen('X_1_3.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);

fileID = fopen('Y_1_3.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);

figure
bar(x,y)
title('Wyznaczenie widma w skali decybelowej x(t)')
xlabel('Cz?stotliwo?c[Hz]')
ylabel('Amplituda')


%FUNKCJA Y<----------------------------------------------------------------


fileID = fopen('X_2_1.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);

fileID = fopen('Y_2_1.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);
 
figure
plot(x,y)
title('Funkcja y(t), A = 8, B = 1, C = 3, fs=271[Hz],n=813')
xlabel('t')
ylabel('y(t)')

fileID = fopen('X_2_2.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);

fileID = fopen('Y_2_2.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);

figure
bar(x,y)
title('DFT(y(t)), A = 8, B = 1, C = 3, fs=271[Hz],n=813')
xlabel('Cz?stotliwo??[Hz]')
ylabel('Amplituda') 
 
fileID = fopen('X_2_3.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);
 
fileID = fopen('Y_2_3.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);
 
figure
bar(x,y)
title('Wyznaczenie widma w skali decybelowej y(t)')
xlabel('Cz?stotliwo?c[Hz]')
ylabel('Amplituda')


%FUNKCJA Z<----------------------------------------------------------------

fileID = fopen('X_3_1.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);

fileID = fopen('Y_3_1.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);

figure
plot(x,y)
title('Funkcja z(t), A = 8, B = 1, C = 3, fs=271[Hz],n=813')
xlabel('t')
ylabel('z(t)')

fileID = fopen('X_3_2.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);

fileID = fopen('Y_3_2.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);

figure
bar(x,y)
title('DFT(z(t)), A = 8, B = 1, C = 3, fs=271[Hz],n=813')
xlabel('Cz?stotliwo??[Hz]')
ylabel('Amplituda')


fileID = fopen('X_3_3.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);

fileID = fopen('Y_3_3.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);

figure
bar(x,y)
title('Wyznaczenie widma w skali decybelowej z(t)')
xlabel('Cz?stotliwo?c[Hz]')
ylabel('Amplituda')


%FUNKCJA U<----------------------------------------------------------------


fileID = fopen('X_4_1.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);

fileID = fopen('Y_4_1.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);
 
figure
plot(x,y)
title('Funkcja u(t), A = 8, B = 1, C = 3, fs=271[Hz],n=813')
xlabel('t')
ylabel('u(t)')

fileID = fopen('X_4_2.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);

fileID = fopen('Y_4_2.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);
 
figure
bar(x,y)
title('DFT(u(t)), A = 8, B = 1, C = 3, fs=271[Hz],n=813')
xlabel('Cz?stotliwo??[Hz]')
ylabel('Amplituda')
 
fileID = fopen('X_4_3.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);

fileID = fopen('Y_4_3.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);
 
figure
bar(x,y)
title('Wyznaczenie widma w skali decybelowej u(t)')
xlabel('Cz?stotliwo?c[Hz]')
ylabel('Amplituda')


%FUNKCJA P N=2<------------------------------------------------------------


fileID = fopen('X_6_1.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);
 
fileID = fopen('Y_6_1.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);

figure
plot(x,y)
title('Funkcja p(t) i N=2, A = 8, B = 1, C = 3, fs=271[Hz],n=813')
xlabel('t')
ylabel('p(t)')
 
fileID = fopen('X_6_2.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);

fileID = fopen('Y_6_2.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);
 
figure
bar(x,y)
title('DFT(p(t)) i N=2, A = 8, B = 1, C = 3, fs=271[Hz],n=813')
xlabel('Cz?stotliwo??[Hz]')
ylabel('Amplituda')
 
fileID = fopen('X_6_3.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);

fileID = fopen('Y_6_3.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);
 
figure
bar(x,y)
title('Wyznaczenie widma w skali decybelowej p(t) i N=2')
xlabel('Cz?stotliwo?c[Hz]')
ylabel('Amplituda')


%FUNKCJA P i N=4<----------------------------------------------------------


fileID = fopen('X_7_1.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);
 
fileID = fopen('Y_7_1.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);
 
figure
plot(x,y)
title('Funkcja p(t) i N=4, A = 8, B = 1, C = 3, fs=271[Hz],n=813')
xlabel('t')
ylabel('p(t)')
 
fileID = fopen('X_7_2.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);
 
fileID = fopen('Y_7_2.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);

figure
bar(x,y)
title('DFT(p(t)) i N=4, A = 8, B = 1, C = 3, fs=271[Hz],n=813')
xlabel('Cz?stotliwo??[Hz]')
ylabel('Amplituda') 

fileID = fopen('X_7_3.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);
 
fileID = fopen('Y_7_3.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);

figure
bar(x,y)
title('Wyznaczenie widma w skali decybelowej p(t) i N=4')
xlabel('Cz?stotliwo?c[Hz]')
ylabel('Amplituda')


%FUNKCJA P i N=81<---------------------------------------------------------


fileID = fopen('X_8_1.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);

fileID = fopen('Y_8_1.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);

figure
plot(x,y)
title('Funkcja p(t) i N=81, A = 8, B = 1, C = 3, fs=271[Hz],n=813')
xlabel('t')
ylabel('p(t)')
 
fileID = fopen('X_8_2.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);
 
fileID = fopen('Y_8_2.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);

figure
bar(x,y)
title('DFT(p(t)) i N=81, A = 8, B = 1, C = 3, fs=271[Hz],n=813')
xlabel('Cz?stotliwo??[Hz]')
ylabel('Amplituda')
 
fileID = fopen('X_8_3.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);

fileID = fopen('Y_8_3.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);
 
figure
bar(x,y)
title('Wyznaczenie widma w skali decybelowej p(t) i N=81')
xlabel('Cz?stotliwo?c[Hz]')
ylabel('Amplituda')


%FUNKCJA V<----------------------------------------------------------------

fileID = fopen('X1_5_1.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);
 
fileID = fopen('Y1_5_1.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);

figure
plot(x,y,'b')
title('Funkcja v(t), A = 8, B = 1, C = 3, fs=271[Hz],n=813')
xlabel('t')
ylabel('v(t)')

hold on
 
fileID = fopen('X2_5_1.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);
 
fileID = fopen('Y2_5_1.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);

plot(x,y,'b')
 
fileID = fopen('X3_5_1.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);
 
fileID = fopen('Y3_5_1.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);

plot(x,y,'b')
 
fileID = fopen('X_5_2.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);

fileID = fopen('Y_5_2.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);

figure
bar(x,y)
title('DFT(v(t)), A = 8, B = 1, C = 3, fs=271[Hz],n=813')
xlabel('Cz?stotliwo??[Hz]')
ylabel('Amplituda')
 
fileID = fopen('X_5_3.txt','r');
formatSpec = '%f'
x = fscanf(fileID,formatSpec)
fclose(fileID);
 
fileID = fopen('Y_5_3.txt','r');
formatSpec = '%f'
y = fscanf(fileID,formatSpec)
fclose(fileID);

figure
bar(x,y)
title('Wyznaczenie widma w skali decybelowej v(t)')
xlabel('Cz?stotliwo?c[Hz]')
ylabel('Amplituda')