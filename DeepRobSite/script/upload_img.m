command = 'curl -F "img=@/Users/cheng/Desktop/avatar.jpeg" cmput466.top/img_upload';
[status,cmdout] = system(command);
display(status);