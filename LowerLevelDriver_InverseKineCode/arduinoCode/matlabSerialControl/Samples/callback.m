function callback(s, BytesAvailable)  
      
    global t;  
    global x;  
    global m;  
    global ii;  
  
    out = fscanf(s);  
    data = str2num(out)  
      
    t = [t ii];  
    m = [m data];  
    set(p, 'XData',t,'YData',m(1,:));  
      
    drawnow  
    x = x + 1;  
    axis([x-200 x+200 -90 90]);  
    ii=ii+1;  
end  

