
function varargout = seriesComm(varargin)
% SERIESCOMM M-file for seriesComm.fig
%      SERIESCOMM, by itself, creates a new SERIESCOMM or raises the existing
%      singleton*.
%
%      H = SERIESCOMM returns the handle to a new SERIESCOMM or the handle to
%      the existing singleton*.
%
%      SERIESCOMM('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SERIESCOMM.M with the given input arguments.
%
%      SERIESCOMM('Property','Value',...) creates a new SERIESCOMM or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before seriesComm_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to seriesComm_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help seriesComm

% Last Modified by GUIDE v2.5 04-Jun-2016 09:49:45

% Begin initialization code - DO NOT EDIT

%%Author: spirit3772,THUEE,NIP LAB,lks04@mails.tsinghua.edu.cn
%%Date: 2005/11/16,23:00
%% Author:tangzhiqiang  email: tzq16@mails.tsinghua.edu.cn
%% Date: 2016/04/24

%% Recording movements


global movementsRecording;


gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @seriesComm_OpeningFcn, ...
                   'gui_OutputFcn',  @seriesComm_OutputFcn, ...
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


% --- Executes just before seriesComm is made visible.
function seriesComm_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to seriesComm (see VARARGIN)


% Choose default command line output for seriesComm
handles.output = hObject;

%设置初始化参数
set(handles.text3,'string','');
set(handles.text4,'string','');
set(handles.pushbutton4,'enable','off');
set(handles.pushbutton5,'enable','off');
set(handles.pushbutton6,'enable','off');
set(handles.pushbutton1,'String','Open Serial Port','foreGroundColor',[1,0,0.5]);
set(handles.checkbox1,'Value',0);
set(handles.checkbox2,'Value',0);
%设置handles中的一些变量，便于全局共享
handles.displayT = 0;
handles.displayR = 1;
handles.baud_rate =  9600;
%handles.baud_rate =  1200;
handles.com = 'COM1';
handles.verifiedBits = 'NONE';
handles.dataBits = 8;
handles.stopBit = 1;
handles.flowControl = 'NONE';
handles.receiveString = '';
% Update handles structure
guidata(hObject, handles);

% UIWAIT makes seriesComm wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = seriesComm_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.edit1,'string','');


function edit2_Callback(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit2 as text




% --- Executes during object creation, after setting all properties.
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.edit2,'string','');
handles.recieveString = '';
guidata(hObject,handles);

% --- Executes on selection change in popupmenu1.
function popupmenu1_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popupmenu1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu1
com = get(hObject,'string');
handles.com = com{get(hObject,'Value')};
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function popupmenu1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu2.
function popupmenu2_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popupmenu2 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from




%        popupmenu26+
baud_rate = get(hObject,'string');
handles.baud_rate = str2num(baud_rate{get(hObject,'Value')});
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function popupmenu2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu3.
function popupmenu3_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popupmenu3 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu3
verifiedBits = get(hObject,'string');
handles.verifiedBits = verifiedBits{get(hObject,'Value')};
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function popupmenu3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu4.
function popupmenu4_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popupmenu4 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu4
dataBits = get(hObject,'string');
handles.dataBits = str2num(dataBits{get(hObject,'Value')});
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function popupmenu4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu5.
function popupmenu5_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popupmenu5 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu5
stopBit = get(hObject,'string');
handles.stopBit = str2num(stopBit{get(hObject,'Value')});
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function popupmenu5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%打开串口按钮的回调程序
%首先检验是打开串口操作还是关闭操作

%打开操作
if(strcmp(get(hObject,'string') , 'Open Serial Port'))
    %建立一个serial object，并设置其参数（接收的终止符号为\n）
     try
        handles.serial =  serial(handles.com,'BaudRate',handles.baud_rate,'DataBits',handles.dataBits,...
                                'Parity',handles.verifiedBits,'StopBits',handles.stopBit,'FlowControl',...
                                handles.flowControl,'terminator',char(13));
                            
       
                            
        set(handles.serial,'OutputBufferSize',512000);
        set(handles.serial,'InputBufferSize',512000);
        handles.serial.BytesAvailableFcnMode = 'terminator';
        handles.serial.BytesAvailableFcn = {@callback_Serial,handles}; 
        %当接受到数据后如果碰到结束符\n就读入，调用receiveData函数
        %handles.serial.BytesAvailableFcn={'receiveData',handles};
        guidata(hObject,handles);
        %打开串口

        fopen(handles.serial);
    
        
        set(hObject,'String','Close Serial Port','foreGroundColor',[67/255,64/255,119/255]);
        str = ['Serial Port ', handles.com , ' opened sucessfully!'];
        set(handles.text3,'String',str,'fontweight','bold');
        set(handles.pushbutton4,'enable','on');
        set(handles.pushbutton5,'enable','on');
        set(handles.pushbutton6,'enable','on');
     catch
        %进行出错处理
        errmsg = lasterr;
        errordlg([errmsg,char(10),'   Can''t Open Serial Port : ',handles.com, char(10),'   Please choose another Port!'],'Serial Port Open Error');
        rethrow(lasterror);
    end
%关闭串口操作
else
   
    fclose(handles.serial);
    set(hObject,'String','Open Serial Port','foreGroundColor',[1,0,0.5]);
    str = ['Serial Port ', handles.com , ' closed sucessfully!'];
    set(handles.text3,'String',str,'fontweight','bold');
    set(handles.pushbutton4,'enable','off');
    set(handles.pushbutton5,'enable','off');
    set(handles.pushbutton6,'enable','off');
end
    
% --- Executes on selection change in popupmenu6.
function popupmenu6_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popupmenu6 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu6
 
flowControl = get(hObject,'string');
handles.flowControl = flowControl{get(hObject,'Value')};
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function popupmenu6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end




% --- Executes on button press in pushbutton4.
function pushbutton4_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%发送数据按钮回调程序
str = get(handles.edit1,'string');
%检测端口状态
if(strcmp(handles.serial.status,'closed'))
    str1 = ['Serial Port ', handles.com , ' is closed ,Please open it!'];
    set(handles.text3,'String',str1,'fontweight','bold');
else
    %打开时进行串口写出
    if(handles.displayT == 0)
        fprintf(handles.serial,'%s',str);
       
        str2 = ['Data has sent in ASCI format sucessfully!'];
        set(handles.text3,'String',str2,'fontweight','bold');
    else
        fprintf(handles.serial,'%x',str);
        str3 = ['Data has sent in HEX format sucessfully!'];
        set(handles.text3,'String',str3,'fontweight','bold');
    end
end




% --- Executes on button press in checkbox1.
function checkbox1_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox1
handles.displayT = get(hObject,'Value');
guidata(hObject,handles);

% --- Executes on button press in checkbox2.
function checkbox2_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox2
handles.displayR = get(hObject,'Value');
guidata(hObject,handles);




% --- Executes when user attempts to close figure1.
function figure1_CloseRequestFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: delete(hObject) closes the figure

%推出界面时 检查是否关闭串口
%button = questdlg('Do you really want to quit? ','Quit?','Yes','No','No');
button='Yes';
if(strcmp(button, 'Yes'))
        if(strcmp(get(handles.pushbutton1,'string'),'Close Serial Port'))
            fclose(handles.serial);
        end
    delete(hObject);
else
    return;
end




% --- Executes on button press in pushbutton5.
function pushbutton5_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


%发送文件前选择文件
[filename, pathname] = uigetfile( ...
{'*.txt;*.c;*.cpp;*.m','TEXT Files (*.txt,*.c,*.cpp,*.m)';
   '*.txt',  'TEXT-files (*.txt)'; ...
   '*.c','C-Files (*.c)'; ...
   '*.cpp','C++-Files (*.cpp)'; ...
   '*.m','M-Files (*.m)'; ...
   '*.*',  'All Files (*.*)'}, ...
   'Pick a file');
if isequal([filename,pathname],[0,0])
    return
% Otherwise construct the fullfilename and Check and load the file
else
    handles.filePath = fullfile(pathname,filename);
end
guidata(hObject,handles);

% --- Executes on button press in pushbutton6.
function pushbutton6_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%发送文件 文件不能太大
fid = fopen(handles.filePath, 'r');
tempstr = ['File ',handles.filePath, ' has opened sucessfully!'];
set(handles.text4,'string',tempstr,'fontweight','bold');
str = fread(fid,'*char');
str = str';
set(handles.edit1,'string',str);

if(strcmp(handles.serial.status,'closed'))
    str1 = ['Serial Port ', handles.com , ' is closed ,Please open it!'];
    set(handles.text3,'String',str1,'fontweight','bold');
else
    if(handles.displayT == 0)
        fprintf(handles.serial,'%s',str);
        str2 = ['Data has sent in ASCI format sucessfully!'];
        set(handles.text3,'String',str2,'fontweight','bold');
    else
        fprintf(handles.serial,'%x',str);
        str3 = ['Data has sent in HEX format sucessfully!'];
        set(handles.text3,'String',str3,'fontweight','bold');
    end
end







% --- Executes on slider movement.
function slider3_Callback(hObject, eventdata, handles)
% hObject    handle to slider3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider4_Callback(hObject, eventdata, handles)
% hObject    handle to slider4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end



% --- Executes during object creation, after setting all properties.
function slider5_CreateFcn(hObject, eventdata, handles)
    % hObject    handle to slider5 (see GCBO)
    % eventdata  reserved - to be defined in a future version of MATLAB
    % handles    empty - handles not created until after all CreateFcns called

    % Hint: slider controls usually have a light gray background.
    if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
        set(hObject,'BackgroundColor',[.9 .9 .9]);
    end

%%  forward direction button
% --- Executes on button press in BASE.
function BASE_Callback(hObject, eventdata, handles)
    % hObject    handle to BASE (see GCBO)
    % eventdata  reserved - to be defined in a future version of MATLAB
    % handles    structure with handles and user data (see GUIDATA)
% SLIDER_NumSteps_value=handles.slider8.get('value')
% SLIDER_NumSteps_value=handles.SLIDER_NumSteps.get('value')
   MotorFlag='a';
   sign=1;    
   
    % data processing
    str_stepsVal =MovementRecording(get(handles.slider_Base_Servos,'value'),MotorFlag,sign);
    
     fprintf(handles.serial,'%s',str_stepsVal);       
     str2 = ['Data has sent sucessfully!'];
    set(handles.text3,'String',str2,'fontweight','bold');

% --- Executes on button press in UPPERARM.
function UPPERARM_Callback(hObject, eventdata, handles)
% hObject    handle to UPPERARM (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%SLIDER_NumSteps
%handles.SLIDER_NumSteps.get
    MotorFlag='f';
    sign=1;    
    % data processing
    str_stepsVal =MovementRecording(get(handles.SLIDER_NumSteps,'value'),MotorFlag,sign);
    
     fprintf(handles.serial,'%s',str_stepsVal);       
     str2 = ['Data has sent sucessfully!'];
    set(handles.text3,'String',str2,'fontweight','bold');

% --- Executes on button press in ELBOW.
function ELBOW_Callback(hObject, eventdata, handles)
% hObject    handle to ELBOW (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    MotorFlag='g';
    sign=1;    
    % data processing
    str_stepsVal =MovementRecording(get(handles.SLIDER_NumSteps,'value'),MotorFlag,sign);

fprintf(handles.serial,'%s',str_stepsVal);       
 str2 = ['Data has sent sucessfully!'];
set(handles.text3,'String',str2,'fontweight','bold');


% --- Executes on button press in AXIS.
function AXIS_Callback(hObject, eventdata, handles)
% hObject    handle to AXIS (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    MotorFlag='h';
    sign=1;    
    % data processing
    str_stepsVal =MovementRecording(get(handles.SLIDER_NumSteps,'value'),MotorFlag,sign);
    
 fprintf(handles.serial,'%s',str_stepsVal);       
 str2 = ['Data has sent sucessfully!'];
set(handles.text3,'String',str2,'fontweight','bold');






% --- Executes on button press in BACK_BASE.
function BACK_BASE_Callback(hObject, eventdata, handles)
% hObject    handle to BACK_BASE (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in BACK_UPARM.
function BACK_UPARM_Callback(hObject, eventdata, handles)
% hObject    handle to BACK_UPARM (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    MotorFlag='f';
    sign=-1;    
    % data processing
    str_stepsVal =MovementRecording(get(handles.SLIDER_NumSteps,'value'),MotorFlag,sign);
    
    %send it
    fprintf(handles.serial,'%s',str_stepsVal);       
    str2 = ['Data has sent sucessfully!'];
    set(handles.text3,'String',str2,'fontweight','bold');



% --- Executes on button press in BACK_AXIS.
function BACK_AXIS_Callback(hObject, eventdata, handles)
% hObject    handle to BACK_AXIS (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    MotorFlag='h';
    sign=-1;    
    % data processing
    str_stepsVal =MovementRecording(get(handles.SLIDER_NumSteps,'value'),MotorFlag,sign);
    
     fprintf(handles.serial,'%s',str_stepsVal);       
     str2 = ['Data has sent sucessfully!'];
    set(handles.text3,'String',str2,'fontweight','bold');



% --- Executes on button press in BACK_ELBOW.
function BACK_ELBOW_Callback(hObject, eventdata, handles)
% hObject    handle to BACK_ELBOW (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    MotorFlag='g';
    sign=-1;    
    % data processing
    str_stepsVal =MovementRecording(get(handles.SLIDER_NumSteps,'value'),MotorFlag,sign);
    
     fprintf(handles.serial,'%s',str_stepsVal);       
     str2 = ['Data has sent sucessfully!'];
    set(handles.text3,'String',str2,'fontweight','bold');



% --- Executes on button press in BACK_WRIST.
function BACK_WRIST_Callback(hObject, eventdata, handles)
% hObject    handle to BACK_WRIST (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in BACK_HAND.
function BACK_HAND_Callback(hObject, eventdata, handles)
% hObject    handle to BACK_HAND (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in BACK_GRIPPER.
function BACK_GRIPPER_Callback(hObject, eventdata, handles)
% hObject    handle to BACK_GRIPPER (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on slider movement.
function slider6_Callback(hObject, eventdata, handles)
% hObject    handle to slider6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end








% --- Executes during object creation, after setting all properties.
function ELBOW_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ELBOW (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called


% --- Executes on slider movement.
function SLIDER_NumSteps_Callback(hObject, eventdata, handles)
% hObject    handle to SLIDER_NumSteps (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
int64(get(handles.SLIDER_NumSteps,'value'))
get(hObject,'Max');
% --- Executes during object creation, after setting all properties.
function SLIDER_NumSteps_CreateFcn(hObject, eventdata, handles)
% hObject    handle to SLIDER_NumSteps (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider8_Callback(hObject, eventdata, handles)
% hObject    handle to slider8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider8_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end





% --- Executes on button press in SAVE_DATA.
function SAVE_DATA_Callback(hObject, eventdata, handles)
% hObject    handle to SAVE_DATA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global movementsRecording;
MovementFileName=inputdlg('Input file name:');
% 
% global rawDataFromSerial;
% global ReceivedTimesFromSerial;
% global AllMovements;
% global MaxIndex_AllMovements;

save(MovementFileName{1},'movementsRecording');

%% Clear all movement data after saving 
movementsRecording{'a'}=[];
movementsRecording{'b'}=[];
movementsRecording{'c'}=[];
movementsRecording{'d'}=[];
movementsRecording{'f'}=[];
movementsRecording{'g'}=[];
movementsRecording{'h'}=[];

% --- Executes on button press in LOAD_DATA.
function LOAD_DATA_Callback(hObject, eventdata, handles)
% hObject    handle to LOAD_DATA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global AllMovements;
global MaxIndex_AllMovements;
MaxIndex_AllMovements=1;
AllMovements={};

[fileName,filePath]=uigetfile('*.mat','Choose a .mat data');
load(fileName);
AllMovements{MaxIndex_AllMovements}=movementsRecording;

% --- Executes on button press in Play_Forward.
function Play_Forward_Callback(hObject, eventdata, handles)
% hObject    handle to Play_Forward (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global ReceivedTimesFromSerial;
global AllMovements;
ReceivedTimesFromSerial=0;%Init reciving flag
MotorTagBase='a'-1;

CurrentMovements=AllMovements{1};    
% getting the Number of moves
[~,size_f]=size(CurrentMovements{'f'-MotorTagBase}); 

    for MoveNumIndex=1:size_f   % For each movement frame
        % Loading movement data
      
        MovementsForJoint_e=CurrentMovements{'e'-MotorTagBase}(MoveNumIndex);
        SendingToSerial( MovementsForJoint_e,'e',handles );   
        %pause(0.01);     

        MovementsForJoint_f=CurrentMovements{'f'-MotorTagBase}(MoveNumIndex);
        SendingToSerial( MovementsForJoint_f,'f',handles );            
        %pause(0.01);
        
        MovementsForJoint_g=CurrentMovements{'g'-MotorTagBase}(MoveNumIndex);
        SendingToSerial( MovementsForJoint_g,'g',handles);
       % pause(0.01);
        
        MovementsForJoint_h=CurrentMovements{'h'-MotorTagBase}(MoveNumIndex);
        SendingToSerial( MovementsForJoint_h,'h',handles);                     
       % pause(0.01);
  
        %Wait untile finished all movements
        while (ReceivedTimesFromSerial<4)                       
            pause(0.01);                  
        end
        ReceivedTimesFromSerial=0;   
        pause(1);
    end    
ReturnArmToOrigion( handles );


% --- Executes on slider movement.
function slider_Base_Servos_Callback(hObject, eventdata, handles)
% hObject    handle to slider_Base_Servos (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
  MotorFlag='a';
   sign=1;    
   
    % data processing
    str_stepsVal =MovementRecording(get(handles.slider_Base_Servos,'value'),MotorFlag,sign);
    
     fprintf(handles.serial,'%s',str_stepsVal);       
     str2 = ['Data has sent sucessfully!'];
    set(handles.text3,'String',str2,'fontweight','bold');



% --- Executes during object creation, after setting all properties.
function slider_Base_Servos_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_Base_Servos (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end





% --- Executes on key press with focus on slider_Base_Servos and none of its controls.
function slider_Base_Servos_KeyPressFcn(hObject, eventdata, handles)
% hObject    handle to slider_Base_Servos (see GCBO)
% eventdata  structure with the following fields (see UICONTROL)
%	Key: name of the key that was pressed, in lower case
%	Character: character interpretation of the key(s) that was pressed
%	Modifier: name(s) of the modifier key(s) (i.e., control, shift) pressed
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on slider movement.
function slider5_Callback(hObject, eventdata, handles)
% hObject    handle to slider5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes on slider movement.
function slider_WristServo_Callback(hObject, eventdata, handles)
% hObject    handle to slider_WristServo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
 MotorFlag='b';
   sign=1;    
   
    % data processing
    str_stepsVal =MovementRecording(get(handles.slider_WristServo,'value'),MotorFlag,sign);
    
     fprintf(handles.serial,'%s',str_stepsVal);       
     str2 = ['Data has sent sucessfully!'];
    set(handles.text3,'String',str2,'fontweight','bold');


% --- Executes during object creation, after setting all properties.
function slider_WristServo_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_WristServo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider_HandServo_Callback(hObject, eventdata, handles)
% hObject    handle to slider_HandServo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
 MotorFlag='c';
   sign=1;    
   
    % data processing
    str_stepsVal =MovementRecording(get(handles.slider_HandServo,'value'),MotorFlag,sign);
    
     fprintf(handles.serial,'%s',str_stepsVal);       
     str2 = ['Data has sent sucessfully!'];
    set(handles.text3,'String',str2,'fontweight','bold');

% --- Executes during object creation, after setting all properties.
function slider_HandServo_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_HandServo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider_GriperServo_Callback(hObject, eventdata, handles)
% hObject    handle to slider_GriperServo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
 MotorFlag='d';
   sign=1;    
   
    % data processing
    str_stepsVal =MovementRecording(get(handles.slider_GriperServo,'value'),MotorFlag,sign);
    
     fprintf(handles.serial,'%s',str_stepsVal);       
     str2 = ['Data has sent sucessfully!'];
    set(handles.text3,'String',str2,'fontweight','bold');

% --- Executes during object creation, after setting all properties.
function slider_GriperServo_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_GriperServo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on key press with focus on figure1 or any of its controls.
function figure1_WindowKeyPressFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  structure with the following fields (see FIGURE)
%	Key: name of the key that was pressed, in lower case
%	Character: character interpretation of the key(s) that was pressed
%	Modifier: name(s) of the modifier key(s) (i.e., control, shift) pressed
% handles    structure with handles and user data (see GUIDATA)

%for recording how many steps to let motor move
global NumStepsEachTime;
if(isempty(NumStepsEachTime))
    NumStepsEachTime=1;
end

%For recording move index
global MoveIndex;
if(isempty(MoveIndex))
    MoveIndex=1;
end

ReceivedCharacter=eventdata.Character;


%% Deciding num of steps
if (ReceivedCharacter-'0')>=0 &&(ReceivedCharacter-'0')<=9
    NumStepsEachTime=int32((ReceivedCharacter-'0')^5.5);
end

%% controlling steppers
if isequal('q',ReceivedCharacter)
    str_stepsVal =MovementRecording(NumStepsEachTime,'a',1,MoveIndex);    
    %str_stepsVal=1;
    fprintf(handles.serial,'%s',str_stepsVal);      
end

if isequal('a',ReceivedCharacter)
    str_stepsVal =MovementRecording(NumStepsEachTime,'a',-1,MoveIndex);    
     fprintf(handles.serial,'%s',str_stepsVal);      
end
%% 

if isequal('w',ReceivedCharacter)
    str_stepsVal =MovementRecording(NumStepsEachTime,'b',1,MoveIndex);    
     fprintf(handles.serial,'%s',str_stepsVal);      
end

if isequal('s',ReceivedCharacter)
    str_stepsVal =MovementRecording(NumStepsEachTime,'b',-1,MoveIndex);   
     fprintf(handles.serial,'%s',str_stepsVal);      
end

%% 

if isequal('e',ReceivedCharacter)
    str_stepsVal =MovementRecording(NumStepsEachTime,'c',1,MoveIndex);    
     fprintf(handles.serial,'%s',str_stepsVal);      
end

if isequal('d',ReceivedCharacter)
    str_stepsVal =MovementRecording(NumStepsEachTime,'c',-1,MoveIndex);    
     fprintf(handles.serial,'%s',str_stepsVal);      
end

%% 

if isequal('r',ReceivedCharacter)
    str_stepsVal =MovementRecording(NumStepsEachTime,'e',1,MoveIndex);   
     fprintf(handles.serial,'%s',str_stepsVal);      
end

if isequal('f',ReceivedCharacter)
    str_stepsVal =MovementRecording(NumStepsEachTime,'e',-1,MoveIndex);   
     fprintf(handles.serial,'%s',str_stepsVal);      
end

%% 

if isequal('t',ReceivedCharacter)
    str_stepsVal =MovementRecording(NumStepsEachTime,'f',1,MoveIndex);    
     fprintf(handles.serial,'%s',str_stepsVal);      
end

if isequal('g',ReceivedCharacter)
    str_stepsVal =MovementRecording(NumStepsEachTime,'f',-1,MoveIndex);    
     fprintf(handles.serial,'%s',str_stepsVal);      
end


%% 

if isequal('y',ReceivedCharacter)
    str_stepsVal =MovementRecording(NumStepsEachTime,'g',1,MoveIndex);    
     fprintf(handles.serial,'%s',str_stepsVal);      
end

if isequal('h',ReceivedCharacter)
    str_stepsVal =MovementRecording(NumStepsEachTime,'g',-1,MoveIndex);    
     fprintf(handles.serial,'%s',str_stepsVal);      
end


%% 

if isequal('u',ReceivedCharacter)
    str_stepsVal =MovementRecording(NumStepsEachTime,'h',1,MoveIndex);    
     fprintf(handles.serial,'%s',str_stepsVal);      
end

if isequal('j',ReceivedCharacter)
    str_stepsVal =MovementRecording(NumStepsEachTime,'h',-1,MoveIndex);    
     fprintf(handles.serial,'%s',str_stepsVal);      
end

%% Sending to serial
 
 str2 = ['Data has sent sucessfully!'];
 set(handles.text3,'String',str2,'fontweight','bold');


% --- Executes on button press in InsertingMoveButton.
function InsertingMoveButton_Callback(hObject, eventdata, handles)
global MoveIndex;



if(isempty(MoveIndex))
    MoveIndex=0;
end
MoveIndex=MoveIndex+1;

% hObject    handle to InsertingMoveButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in PLAY_BACK.
function PLAY_BACK_Callback(hObject, eventdata, handles)
% hObject    handle to PLAY_BACK (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global ReceivedTimesFromSerial;
ReceivedTimesFromSerial=0;%Init reciving flag
ReturnArmToOrigion( handles );
