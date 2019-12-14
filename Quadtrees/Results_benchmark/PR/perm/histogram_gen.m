clc
clear all
close all

listing = dir("*.txt");
inserting_time = [];
finding_time = [];
nearest_time =[];

N =[1000000,100000, 1000, 100];
Occ = [10, 10,100, 100];

for i=1:length(listing)
    T = readtable(listing(i).name);
    A = table2array(T);
    if(isempty(A))
        continue
    end
    inserting_time = cat(1,inserting_time,mean(A(:,1)));
    finding_time = cat(1,finding_time,mean(A(:,2)));
    nearest_time = cat(1,nearest_time,mean(A(:,3)));
    figure(i)
    set(gcf,'units','points','position',[100,100,600,300])
%     set(gcf,'units','points','position',[0.5703 0.1100 0.3347 0.8150]);
    for j=1:2
        if j == 1
           tit = ['Insertion (Build) Time Histogram ', num2str(N(i)), ' Permutations'];
        else
           tit = ['Find Time Histogram ', num2str(N(i)), ' Permutations'];
        end
        y_txt = ['Number of Occurrences (out of ',num2str(Occ(i)),')'];
        subplot(1,2,j)
        hold on
        grid minor
        histogram(A(:,j))
        xlabel('Time to Build(seconds)')
        ylabel(y_txt)
        title(tit)
    end
    
end

X = categorical({'100','1000','100K','1M'});
figure(i+1)
subplot(2,1,1)
bar(X,(flip(inserting_time))),set(gca,'yscale','log')
grid minor
title("Average time per permutation")
ylabel("Avg Insert Time [sec]")
subplot(2,1,2)
bar(X,flip(finding_time))
grid minor
ylabel("Avg Find Time [sec]")
xlabel("Data Size Number")


