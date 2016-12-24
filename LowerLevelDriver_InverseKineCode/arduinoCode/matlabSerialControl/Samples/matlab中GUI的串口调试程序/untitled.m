function varargout = untitled(varargin)
% UNTITLED M-file for untitled.fig
%      UNTITLED, by itself, creates a new UNTITLED or raises the existing
%      singleton*.
%
%      H = UNTITLED returns the handle to a new UNTITLED or the handle to
%      the existing singleton*.
%
%      UNTITLED('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in UNTITLED.M with the given input arguments.
%
%      UNTITLED('Property','Value',...) creates a new UNTITLED or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before untitled_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to untitled_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help untitled

% Last Modified by GUIDE v2.5 07-Sep-2013 13:47:05

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @untitled_OpeningFcn, ...
                   'gui_OutputFcn',  @untitled_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before untitled is made visible.
function untitled_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to untitled (see VARARGIN)

% 初始化
set(handles.caiji,'UserData',0);
setappdata(handles.save,'ApplicationData',0);

% Choose default command line output for untitled
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes untitled wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = untitled_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in on.
function on_Callback(hObject, eventdata, handles)
% hObject    handle to on (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

clc;

s1 = instrfind('Type','serial','Port','COM1','Tag','');    % 查看端口是否存在
s2 = instrfind('Type','serial','Port','COM2','Tag','');
s3 = instrfind('Type','serial','Port','COM3','Tag','');    % 查看端口是否存在
s4 = instrfind('Type','serial','Port','COM4','Tag','');
% 获取参数值


if (isempty(s1) && get(handles.port,'Value')==1 )           % 如果端口1存在，存创建端口 
    s = serial('COM1');                   % 创建串口号
    if(get(handles.botelv,'Value')==1)    % 设置串口参数
        s.BaudRate = 1200;                   
    elseif(get(handles.botelv,'Value')==2) 
        s.BaudRate = 2400;   
    elseif(get(handles.botelv,'Value')==3) 
        s.BaudRate = 4800;   
    elseif(get(handles.botelv,'Value')==4) 
        s.BaudRate = 9600;  
    elseif(get(handles.botelv,'Value')==5) 
        s.BaudRate = 19200; 
    elseif(get(handles.botelv,'Value')==6) 
        s.BaudRate = 38400;
    elseif(get(handles.botelv,'Value')==7) 
        s.BaudRate = 76800;
    elseif(get(handles.botelv,'Value')==8) 
        s.BaudRate = 115200;  
    end
    if(get(handles.jiaoyanw,'Value')==1)
        s.Parity = 'none';                      % 无校验位
    elseif(get(handles.jiaoyanw,'Value')==2)
        s.Parity = 'odd';                      % 偶校验
    elseif(get(handles.jiaoyanw,'Value')==3)
        s.Parity = 'even';                      % 奇校验
    end
    if(get(handles.dataw,'Value')==1)           % 数据位
        s.DataBits = 8;
    elseif(get(handles.dataw,'Value')==2)
        s.DataBits = 7;
    elseif(get(handles.dataw,'Value')==3)
        s.DataBits = 6;
    elseif(get(handles.dataw,'Value')==4)
        s.DataBits = 5;
    end
    if(get(handles.stopw,'Value')==1)           % 停止位
        s.StopBits = 1;
    elseif(get(handles.stopw,'Value')==2)
        s.StopBits = 1.5;
    elseif(get(handles.stopw,'Value')==3)
        s.StopBits = 2;  
    end
    s.Timeout = 0.1;
    s.InputBufferSize = 3072;
    s.OutputBufferSize = 3072;
    s.ReadAsyncMode = 'continuous';
    
    handles.sbuff = s;
    guidata(hObject, handles);
    s.BytesAvailableFcnMode = 'byte';
    s.BytesAvailableFcnCount = 10;
    s.BytesAvailableFcn = {@recive_data, handles};
    fopen(s);
    set(handles.caiji,'Enable','On');
    set(handles.off,'Enable','On');
    set(handles.on,'Enable','Off');
    set(handles.edit1,'String','打开成功！');
    set(handles.exit,'Enable','Off');
    set(handles.edit1,'backgroundcolor',[0 1 0]);
    
elseif (isempty(s2) && get(handles.port,'Value')==2 )        % 如果端口2存在，存创建端口 
    s = serial('COM2');                   % 创建串口号
    if(get(handles.botelv,'Value')==1)    % 设置串口参数
        s.BaudRate = 1200;                   
    elseif(get(handles.botelv,'Value')==2) 
        s.BaudRate = 2400;   
    elseif(get(handles.botelv,'Value')==3) 
        s.BaudRate = 4800;   
    elseif(get(handles.botelv,'Value')==4) 
        s.BaudRate = 9600;  
    elseif(get(handles.botelv,'Value')==5) 
        s.BaudRate = 19200; 
    elseif(get(handles.botelv,'Value')==6) 
        s.BaudRate = 38400;
    elseif(get(handles.botelv,'Value')==7) 
        s.BaudRate = 76800;
    elseif(get(handles.botelv,'Value')==8) 
        s.BaudRate = 115200;  
    end
    if(get(handles.jiaoyanw,'Value')==1)
        s.Parity = 'none';                      % 无校验位
    elseif(get(handles.jiaoyanw,'Value')==2)
        s.Parity = 'odd';                      % 偶校验
    elseif(get(handles.jiaoyanw,'Value')==3)
        s.Parity = 'even';                      % 奇校验
    end
    if(get(handles.dataw,'Value')==1)           % 数据位
        s.DataBits = 8;
    elseif(get(handles.dataw,'Value')==2)
        s.DataBits = 7;
    elseif(get(handles.dataw,'Value')==3)
        s.DataBits = 6;
    elseif(get(handles.dataw,'Value')==4)
        s.DataBits = 5;
    end
    if(get(handles.stopw,'Value')==1)           % 停止位
        s.StopBits = 1;
    elseif(get(handles.stopw,'Value')==2)
        s.StopBits = 1.5;
    elseif(get(handles.stopw,'Value')==3)
        s.StopBits = 2;  
    end
    s.Timeout = 0.1;
    s.InputBufferSize = 3072;
    s.OutputBufferSize = 3072;
    s.ReadAsyncMode = 'continuous';
    
    handles.sbuff = s;
    guidata(hObject, handles);
    s.BytesAvailableFcnMode = 'byte';
    s.BytesAvailableFcnCount = 10;
    s.BytesAvailableFcn = {@recive_data, handles};
    fopen(s);
    set(handles.caiji,'Enable','On');
    set(handles.off,'Enable','On');
    set(handles.on,'Enable','Off');
    set(handles.exit,'Enable','Off');
    set(handles.edit1,'String','打开成功！');
    set(handles.edit1,'backgroundcolor',[0 1 0]);
    
elseif (isempty(s3) && get(handles.port,'Value')==3 )        % 如果端口3存在，存创建端口 
    s = serial('COM3');                   % 创建串口号
    if(get(handles.botelv,'Value')==1)    % 设置串口参数
        s.BaudRate = 1200;                   
    elseif(get(handles.botelv,'Value')==2) 
        s.BaudRate = 2400;   
    elseif(get(handles.botelv,'Value')==3) 
        s.BaudRate = 4800;   
    elseif(get(handles.botelv,'Value')==4) 
        s.BaudRate = 9600;  
    elseif(get(handles.botelv,'Value')==5) 
        s.BaudRate = 19200; 
    elseif(get(handles.botelv,'Value')==6) 
        s.BaudRate = 38400;
    elseif(get(handles.botelv,'Value')==7) 
        s.BaudRate = 76800;
    elseif(get(handles.botelv,'Value')==8) 
        s.BaudRate = 115200;  
    end
    if(get(handles.jiaoyanw,'Value')==1)
        s.Parity = 'none';                      % 无校验位
    elseif(get(handles.jiaoyanw,'Value')==2)
        s.Parity = 'odd';                      % 偶校验
    elseif(get(handles.jiaoyanw,'Value')==3)
        s.Parity = 'even';                      % 奇校验
    end
    if(get(handles.dataw,'Value')==1)           % 数据位
        s.DataBits = 8;
    elseif(get(handles.dataw,'Value')==2)
        s.DataBits = 7;
    elseif(get(handles.dataw,'Value')==3)
        s.DataBits = 6;
    elseif(get(handles.dataw,'Value')==4)
        s.DataBits = 5;
    end
    if(get(handles.stopw,'Value')==1)           % 停止位
        s.StopBits = 1;
    elseif(get(handles.stopw,'Value')==2)
        s.StopBits = 1.5;
    elseif(get(handles.stopw,'Value')==3)
        s.StopBits = 2;  
    end
    s.Timeout = 0.1;
    s.InputBufferSize = 3072;
    s.OutputBufferSize = 3072;
    s.ReadAsyncMode = 'continuous';
    
    handles.sbuff = s;
    guidata(hObject, handles);
    s.BytesAvailableFcnMode = 'byte';
    s.BytesAvailableFcnCount = 10;
    s.BytesAvailableFcn = {@recive_data, handles};
    fopen(s);
    set(handles.caiji,'Enable','On');
    set(handles.off,'Enable','On');
    set(handles.on,'Enable','Off');
    set(handles.exit,'Enable','Off');
    set(handles.edit1,'String','打开成功！');
    set(handles.edit1,'backgroundcolor',[0 1 0]);
    
elseif (isempty(s4) && get(handles.port,'Value')==4 )        % 如果端口4存在，存创建端口 
    s = serial('COM4');                   % 创建串口号
    if(get(handles.botelv,'Value')==1)    % 设置串口参数
        s.BaudRate = 1200;                   
    elseif(get(handles.botelv,'Value')==2) 
        s.BaudRate = 2400;   
    elseif(get(handles.botelv,'Value')==3) 
        s.BaudRate = 4800;   
    elseif(get(handles.botelv,'Value')==4) 
        s.BaudRate = 9600;  
    elseif(get(handles.botelv,'Value')==5) 
        s.BaudRate = 19200; 
    elseif(get(handles.botelv,'Value')==6) 
        s.BaudRate = 38400;
    elseif(get(handles.botelv,'Value')==7) 
        s.BaudRate = 76800;
    elseif(get(handles.botelv,'Value')==8) 
        s.BaudRate = 115200;  
    end
    if(get(handles.jiaoyanw,'Value')==1)
        s.Parity = 'none';                      % 无校验位
    elseif(get(handles.jiaoyanw,'Value')==2)
        s.Parity = 'odd';                      % 偶校验
    elseif(get(handles.jiaoyanw,'Value')==3)
        s.Parity = 'even';                      % 奇校验
    end
    if(get(handles.dataw,'Value')==1)           % 数据位
        s.DataBits = 8;
    elseif(get(handles.dataw,'Value')==2)
        s.DataBits = 7;
    elseif(get(handles.dataw,'Value')==3)
        s.DataBits = 6;
    elseif(get(handles.dataw,'Value')==4)
        s.DataBits = 5;
    end
    if(get(handles.stopw,'Value')==1)           % 停止位
        s.StopBits = 1;
    elseif(get(handles.stopw,'Value')==2)
        s.StopBits = 1.5;
    elseif(get(handles.stopw,'Value')==3)
        s.StopBits = 2;  
    end
    s.Timeout = 0.1;
    s.InputBufferSize = 3072;
    s.OutputBufferSize = 3072;
    s.ReadAsyncMode = 'continuous';
    
    handles.sbuff = s;
    guidata(hObject, handles);
    s.BytesAvailableFcnMode = 'byte';
    s.BytesAvailableFcnCount = 10;
    s.BytesAvailableFcn = {@recive_data, handles};
    fopen(s);
    set(handles.caiji,'Enable','On');
    set(handles.off,'Enable','On');
    set(handles.on,'Enable','Off');
    set(handles.exit,'Enable','Off');
    set(handles.edit1,'String','打开成功！');
    set(handles.edit1,'backgroundcolor',[0 1 0]);
else
    msgbox('串口不存在或被占用！');
    set(handles.edit1,'String','打开失败！');
    set(handles.edit1,'backgroundcolor',[1 0/255 0]);
end

   
% 中断处理程序
function recive_data(t,  event, handles)

if(getappdata(handles.caiji,'ApplicationData')~=0)            % 收到单击采集信号的信息
   
    g = handles.sbuff;
    [out,huanchongcout] = fread(g,10);                       % 读取数据
%     plot(handles.axes1,out);  
    % 解析数据
    if(out(1)==128 && bitxor(bitxor(bitxor(bitxor(out(2),out(3)),out(4)),out(5)),out(6)) == out(7))
        data2 = dec2bin(out(2),8);
        data3 = dec2bin(out(3),8);
        data4 = dec2bin(out(4),8);
        data5 = dec2bin(out(5),8);
        data6 = dec2bin(out(6),8);
        cur_data0 = 0;      % 初始化脉冲值
        cur_data1 = dec2bin(cur_data0,32);   % 转成二进制，有效位数为32
        cur_data1(1:4) = data6(5:8);
        cur_data1(5:11) = data5(2:8);
        cur_data1(12:18) = data4(2:8);
        cur_data1(19:25) = data3(2:8);
        cur_data1(26:32) = data2(2:8);
        cur_data2 = cur_data1;
        set(handles.current_data,'String',bin2dec(cur_data2));
    end
    
    
    if(getappdata(handles.save,'ApplicationData') ~=0)        % 开始存储数据
        
        File = get(handles.save_play,'String');
        fid = fopen(File,'a');
        fprintf(fid,'%d\t',bin2dec(cur_data2));
        fprintf(fid,'\n');
        fclose(fid);
        
    end      
end  


% --- Executes on button press in off.
function off_Callback(hObject, eventdata, handles)
% hObject    handle to off (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

    s = handles.sbuff;      % 传递
    fclose(s);              % 关闭串口设备对象
    delete(s);              % 删除内存中的串口设备对象
    clear s;                % 清除工作区间的串口设备对象
    setappdata(handles.axes1,'ApplicationData',0);  % 清空缓存数据
    set(handles.axes1,'UserData',0);                % 将计数器清0
    set(handles.save,'UserData',0);                 % 将数据保存区清0
    set(handles.edit1,'String','串口关闭');
    set(handles.edit1,'backgroundcolor',[0 0/255 1]);
    set(handles.caiji,'Enable','Off');
    set(handles.on,'Enable','On');
    set(handles.save,'Enable','Off');
    set(handles.off,'Enable','Off');
    set(handles.exit,'Enable','On');
% --- Executes on selection change in port.
function port_Callback(hObject, eventdata, handles)
% hObject    handle to port (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns port contents as cell array
%        contents{get(hObject,'Value')} returns selected item from port


% --- Executes during object creation, after setting all properties.
function port_CreateFcn(hObject, eventdata, handles)
% hObject    handle to port (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in botelv.
function botelv_Callback(hObject, eventdata, handles)
% hObject    handle to botelv (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns botelv contents as cell array
%        contents{get(hObject,'Value')} returns selected item from botelv


% --- Executes during object creation, after setting all properties.
function botelv_CreateFcn(hObject, eventdata, handles)
% hObject    handle to botelv (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in dataw.
function dataw_Callback(hObject, eventdata, handles)
% hObject    handle to dataw (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns dataw contents as cell array
%        contents{get(hObject,'Value')} returns selected item from dataw


% --- Executes during object creation, after setting all properties.
function dataw_CreateFcn(hObject, eventdata, handles)
% hObject    handle to dataw (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in jiaoyanw.
function jiaoyanw_Callback(hObject, eventdata, handles)
% hObject    handle to jiaoyanw (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns jiaoyanw contents as cell array
%        contents{get(hObject,'Value')} returns selected item from jiaoyanw


% --- Executes during object creation, after setting all properties.
function jiaoyanw_CreateFcn(hObject, eventdata, handles)
% hObject    handle to jiaoyanw (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in stopw.
function stopw_Callback(hObject, eventdata, handles)
% hObject    handle to stopw (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns stopw contents as cell array
%        contents{get(hObject,'Value')} returns selected item from stopw


% --- Executes during object creation, after setting all properties.
function stopw_CreateFcn(hObject, eventdata, handles)
% hObject    handle to stopw (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes during object creation, after setting all properties.
function axes1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: place code in OpeningFcn to populate axes1

if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in caiji.
function caiji_Callback(hObject, eventdata, handles)
% hObject    handle to caiji (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%  data = handles.data;

% 发送信号，传递给中断，将信号暂存在采集控件中

% t = str2num(get(handles.save_time,'String'));
index = get(handles.save_lujin,'UserData');         % 是否设定存储路径
g = handles.sbuff;
[a,b] = fread(g);
if ( b==0 )
    msgbox('当前无数据输入！');
    set(handles.save,'Enable','Off');
else
    if(get(handles.caiji,'UserData')==0)
        set(handles.caiji,'String','停止采集');
        set(handles.caiji,'BackgroundColor',[1 0 0]);
        setappdata(handles.caiji,'ApplicationData',1);   % 用于传递给中断响应函数，可以接收并显示数据了
        set(handles.caiji,'UserData',1);
        if(  index~=0 )                                       % 设定存储条件
            set(handles.save,'Enable','On');
        else
            set(handles.save,'Enable','Off');
        end
    else
        set(handles.caiji,'String','开始采集');
        setappdata(handles.caiji,'ApplicationData',0); 
        set(handles.caiji,'BackgroundColor',[0.8 0.8 0.8]);
        set(handles.caiji,'UserData',0);
        set(handles.save,'Enable','Off');
        set(handles.save_time,'String',0);
    end
    
end
% --- Executes on button press in save.
function save_Callback(hObject, eventdata, handles)
% hObject    handle to save (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% 发送开始存储信号，并带有时间控制功能

  setappdata(handles.save,'ApplicationData',1);
% g = handles.sbuff;
% [data,b] = fread(g)
  t = str2num(get(handles.save_time,'String'));
  acc_time = t;        % 中间变量     
  set(handles.time_play,'String',num2str(t));
  for i = 1:t         % 时间显示     
      
     pause(0.995);
     set(handles.time_play,'String',num2str(acc_time-1));   
     acc_time = acc_time-1;     
      
  end    
  setappdata(handles.save,'ApplicationData',0);
%   File = get(handles.save_play,'String');                     % 获取存储路径
%   fopen(File);
%   g = handles.sbuff;
%   [data,b] = fread(g)
%   fprintf(File,'%12.8e\t',data);
%  save ( File ,'uint8','data');
% --- Executes on button press in exit.
function exit_Callback(hObject, eventdata, handles)
% hObject    handle to exit (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

close(gcbf);

function save_play_Callback(hObject, eventdata, handles)
% hObject    handle to save_play (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of save_play as text
%        str2double(get(hObject,'String')) returns contents of save_play as a double


% --- Executes during object creation, after setting all properties.
function save_play_CreateFcn(hObject, eventdata, handles)
% hObject    handle to save_play (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in save_lujin.
function save_lujin_Callback(hObject, eventdata, handles)
% hObject    handle to save_lujin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.save,'Enable','On');
[file, pathname, index] = uiputfile({'*.txt';'*.dat';'*.mat'},'文件另存为');
file1 = strcat(pathname,file);
set(handles.save_play,'String',file1);
set(handles.save_lujin,'UserData',index);      % 判断是否设定了保存文件的路径

function save_time_Callback(hObject, eventdata, handles)
% hObject    handle to save_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of save_time as text
%        str2double(get(hObject,'String')) returns contents of save_time as a double



% --- Executes during object creation, after setting all properties.
function save_time_CreateFcn(hObject, eventdata, handles)
% hObject    handle to save_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function time_play_CreateFcn(hObject, eventdata, handles)
% hObject    handle to time_play (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called



function current_data_Callback(hObject, eventdata, handles)
% hObject    handle to current_data (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of current_data as text
%        str2double(get(hObject,'String')) returns contents of current_data as a double


% --- Executes during object creation, after setting all properties.
function current_data_CreateFcn(hObject, eventdata, handles)
% hObject    handle to current_data (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
