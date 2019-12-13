clc
clear all

listing = dir("*.txt");
inserting_time = [];
finding_time = [];
nearest_time =[];

for i=1:length(listing)
    T = readtable(listing(i).name);
    A = table2array(T);
    if(isempty(A))
        continue
    end
    inserting_time = cat(1,inserting_time,mean(A(:,1)));
    finding_time = cat(1,finding_time,mean(A(:,2)));
    nearest_time = cat(1,nearest_time,mean(A(:,3)));
    figure
    histogram(A(:,2))
end

N =[1000000,100000, 1000, 100 ];
figure
subplot(3,1,1)
plot(N,inserting_time)
grid minor
title("Average time per permutation")
ylabel("Avg Insert Time [sec]")
subplot(3,1,2)
plot(N,finding_time)
grid minor
ylabel("Avg Find Time [sec]")
subplot(3,1,3)
plot(N,nearest_time)
grid minor
ylabel("Avg Nearest. Time [sec]")
xlabel("Permutation Number")


