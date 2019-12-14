% histogram plots
clear
files = dir('.');
for file_num = 1:length(files)
    out(file_num) = contains(string(files(file_num).name), ".txt");
end

txt_files = files(out');
fig_num = 1;
for file_num = 1:length(txt_files)
    [n, remainder] = strtok(string(txt_files(file_num).name), "_");
    [d, remainder] = strtok(remainder, "_");
    if double(n) > 1000
        fileID = fopen(txt_files(file_num).name,'r');
        data = fscanf(fileID,'%f %f', [10 2]);
        fclose(fileID);
    else
        fileID = fopen(txt_files(file_num).name,'r');
        data = fscanf(fileID,'%f %f', [100 2]);
        fclose(fileID);
    end
    
    insert_times = data(:, 1);
    find_times = data(:, 2);
    
    
    [perm_str, remainder] = strtok(remainder, "_");
    
    if (strcmp("permuted", perm_str))
        perm_flag = 1;
    else
        perm_flag = 0;
    end
     
    size_n = double(n);
     if size_n == 100
         fig_num = 1;
         if perm_flag
            avg_insert(1, 2) = mean(insert_times);
            avg_find(1, 2) = mean(find_times);
         else
            avg_insert(1, 1) = mean(insert_times);
            avg_find(1, 1) = mean(find_times);
         end
     elseif size_n == 1000
         fig_num = 2;
         if perm_flag
            avg_insert(2, 2) = mean(insert_times);
            avg_find(2, 2) = mean(find_times);
         else
            avg_insert(2, 1) = mean(insert_times);
            avg_find(2, 1) = mean(find_times);
         end
     elseif size_n == 100000
         fig_num = 3;
         if perm_flag
            avg_insert(3, 2) = mean(insert_times);
            avg_find(3, 2) = mean(find_times);
         else
            avg_insert(3, 1) = mean(insert_times);
            avg_find(3, 1) = mean(find_times);
         end
     elseif size_n == 1000000
         fig_num = 4;
         if perm_flag
            avg_insert(4, 2) = mean(insert_times);
            avg_find(4, 2) = mean(find_times);
         else
            avg_insert(4, 1) = mean(insert_times);
            avg_find(4, 1) = mean(find_times);
         end
     end
    
    if perm_flag
        figure(fig_num)
        title_str = " Consecutive Insertion (Build) Times Histogram for d = " + string(d) + " Over " + string(n) + " Permutations";
        subplot(1, 2, 1)
        histogram(insert_times(:, 1), 20);
        title(title_str);
        xlabel("Time to Build (seconds)")
        ylabel("Number of occurences (out of 100)")        
    else
        figure(fig_num)
        title_str = " Consecutive Insertion (Build) Times Histogram For n = " + string(n) + ", d = " + string(d); 
        subplot(1, 2, 2)
        title_str = " Consecutive Find Times Histogram For n = " + string(n) + ", d = " + string(d); 
        histogram(find_times(:, 1), 20);
        title(title_str);
        xlabel("Time to Build (seconds)")
        ylabel("Number of occurences (out of 100)")
    end
    
    
    
    
  
end
%%
load('quadtree_benchmark')

figure(7)
bar(categorical({'n = 100', 'n = 1000', 'n = 100K', 'n = 1M'}), [avg_insert(:, 2) flip(inserting_time)]), set(gca,'yscale','log')
title('Average Build Times for kd-Tree/Quadtree for Random Permutations')
ylabel('Time (s) (log scale)')
xlabel('Number of Data Points')
legend('kd-tree', 'quadtree', 'Location', 'northwest')

figure(8)
bar(categorical({'n = 100', 'n = 1000', 'n = 100K', 'n = 1M'}), [avg_find(:, 2) flip(finding_time)]),set(gca,'yscale','log')
title('Average Find Times for kd-Tree/Quadtree for Random Permutations')
ylabel('Time (s) (log scale)')
xlabel('Number of Data Points')
legend('kd-tree', 'quadtree', 'Location', 'northwest')


%%

figure(5)
bar(categorical({'n = 100', 'n = 1000', 'n = 100K', 'n = 1M'}), avg_insert)
title('Average Build Times for kd Tree')
ylabel('Time (s)')
xlabel('Number of Data Points')
legend('Random Data', 'Random Permutations', 'Location', 'northwest')

figure(6)
bar(categorical({'n = 100', 'n = 1000', 'n = 100K', 'n = 1M'}), avg_find)
title('Average Find Times for kd Tree')
ylabel('Time (s)')
xlabel('Number of Data Points')
legend('Random Data', 'Random Permutations', 'Location', 'northwest')
