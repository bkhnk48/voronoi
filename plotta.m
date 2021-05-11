load('ostacoli.txt')
load('voronoi.txt')
load('percorso.txt')
load('incroci.txt')

axis equal;
%figure('color', [0, 0, 0]);
vrx = voronoi(:, 1);
vry = voronoi(:, 2);
%plot(voronoi(:,1),voronoi(:,2),'r.','MarkerSize',10,'MarkerEdgeColor','g')
plot(vrx, vry,'r.','MarkerSize',10,'MarkerEdgeColor','g')
hold on
plot(ostacoli(:,1),ostacoli(:,2),'r.','MarkerSize',10);
xs = 14;
ys = 54;
xg = 0;
yg = 40;
x = xs; y = ys;
indk = 1;
n = 0;
while (abs(x - xg) > 5)||(abs(y - yg)> 5)
  path(:,indk) = [x y];
  dist = sqrt((vrx - x).^2+(vry - y).^2);
  goal = sqrt((xg - x).^2+(xg - y).^2);
  if(n < 1000000)
    n = n + 1;
  else  
    printf("."); %Find closest vertices of the Voronoi edges
    n = 0;
  end
  [mn ind] = min(dist(:));
  xt = vrx(ind);
  yt = vry(ind);
  goalj = sqrt((xg - xt).^2+(xg - yt).^2);
  if (goalj < goal )
    x = xt;
    y = yt;
    vrx(ind) = 1E6;
    vry(ind) = 1E6;
    indk = indk +1;
  else
    vrx(ind) = 1E6;
    vry(ind) = 1E6;
  end
end
path(:,indk) = [xg yg];
plot(path(1,:),path(2,:),'-r');
%plot(percorso(:,1),percorso(:,2),'MarkerEdgeColor','y','LineWidth',3)
%plot(percorso(:,1),percorso(:,2),'r.','MarkerSize',15,'MarkerEdgeColor','y')
%plot(incroci(:,1),incroci(:,2),'r.','MarkerSize',15,'MarkerEdgeColor','r')
hold off
%axis off;
%set(gcf,'InvertHardCopy','off');
%text = sprintf("SoDo1.png");
%saveas(gca, text);