file = fopen('simple_tone_not_quantified.txt');
X = [0:3/769:(3-3/769)];
A=textscan(file,'%f');
Array=A{1,1};
p_1=figure;
plot(X,Array)
print(p_1,'Plot_1','-dpng')
fclose(file);

file = fopen('q_16.txt');
X = [0:3/769:(3-12/769)];
A=textscan(file,'%f');
Array=A{1,1};
p_2=figure;
plot(X,Array)
print(p_2,'Plot_2','-dpng')
fclose(file);

file = fopen('q_8.txt');
A=textscan(file,'%f');
Array=A{1,1};
p_3=figure;
plot(X,Array)
print(p_3,'Plot_3','-dpng')
fclose(file);

file = fopen('q_6.txt');
A=textscan(file,'%f');
Array=A{1,1};
p_4=figure;
plot(X,Array)
print(p_4,'Plot_4','-dpng')
fclose(file);

file = fopen('q_4.txt');
A=textscan(file,'%f');
Array=A{1,1};
p_5=figure;
plot(X,Array)
print(p_5,'Plot_5','-dpng')
fclose(file);