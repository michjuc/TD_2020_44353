file = fopen('output.txt');
X=[-10:0.01:10];
A=textscan(file,'%f');
Array=A{1,1};
p_1=figure;
plot(X,Array)
print(p_1,'Plot_1','-dpng')
fclose(file);

step=1/22050;
X=[0:step:1-step];

file = fopen('2_1.txt');
A=textscan(file,'%f');
Array=A{1,1};
p_2 = figure;
plot(X,Array)
print(p_2,'Plot_2','-dpng')
fclose(file);

file = fopen('2_2.txt');
A=textscan(file,'%f');
Array=A{1,1};
p_3 = figure;
plot(X,Array)
print(p_3,'Plot_3','-dpng')
fclose(file);

file = fopen('2_3.txt');
A = textscan(file,'%f');
Array = A{1,1};
p_4 = figure;
plot(X,Array)
print(p_4,'Plot_4','-dpng')
fclose(file);

file = fopen('2_4.txt');
A = textscan(file,'%f');
Array = A{1,1};
p_5 = figure;
plot(X,Array)
print(p_5,'Plot_5','-dpng')
fclose(file);

file = fopen('2_5.txt');
A = textscan(file,'%f');
Array = A{1,1};
p_6 = figure;
plot(X,Array)
print(p_6,'Plot_6','-dpng')
fclose(file);