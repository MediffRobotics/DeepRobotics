function varargout = main(varargin)
% MAIN MATLAB code for main.fig
%      MAIN, by itself, creates a new MAIN or raises the existing
%      singleton*.
%      H = MAIN returns the handle to a new MAIN or the handle to
%      the existing singleton*.
%
%      MAIN('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in MAIN.M with the given input arguments.
%
%      MAIN('Property','Value',...) creates a new MAIN or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before main_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to main_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help main

% Last Modified by GUIDE v2.5 14-Jan-2017 03:38:06

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @main_OpeningFcn, ...
                   'gui_OutputFcn',  @main_OutputFcn, ...
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


% --- Executes just before main is made visible.
function main_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to main (see VARARGIN)

%% Initialization
startup_main()
global mediffSimulator;
mediffSimulator=mediff();

global SockClient;
SockClient=client();
%%
global counter1;
counter1=0;
% Choose default command line output for main
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes main wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = main_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;




% --- Executes on button press in BUTTON_OpenSocket.
function BUTTON_OpenSocket_Callback(hObject, eventdata, handles)
% hObject    handle to BUTTON_OpenSocket (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global SockClient;
SockClient.OpenSocket();


% --- Executes on key press with focus on BUTTON_DetectingMoveKeys and none of its controls.
function BUTTON_DetectingMoveKeys_KeyPressFcn(hObject, eventdata, handles)
% hObject    handle to BUTTON_DetectingMoveKeys (see GCBO)
% eventdata  structure with the following fields (see UICONTROL)
%	Key: name of the key that was pressed, in lower case
%	Character: character interpretation of the key(s) that was pressed
%	Modifier: name(s) of the modifier key(s) (i.e., control, shift) pressed
% handles    structure with handles and user data (see GUIDATA)
ReceivedCharacter=eventdata.Character;
global mediffSimulator;
global SockClient;
MoveDistance=1; 


global counter1;
%% Move Up
if isequal('q',ReceivedCharacter)
   %mediffSimulator.MoveUp(0);   
   counter1=counter1+1;
   SockClient.MoveArm(counter1); %Deg
   
   counter1
end
%% Move down
if isequal('a',ReceivedCharacter)
   %mediffSimulator.MoveUp(1); 
   counter1=counter1-1;
   SockClient.MoveArm(counter1);
   
end

%% Move forward
if isequal('w',ReceivedCharacter)
   mediffSimulator.MoveUp(2);        
end
%% Move backward
if isequal('s',ReceivedCharacter)
   mediffSimulator.MoveUp(3);        


end

% --- Executes on button press in BUTTON_DetectingMoveKeys.
function BUTTON_DetectingMoveKeys_Callback(hObject, eventdata, handles)
% hObject    handle to BUTTON_DetectingMoveKeys (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in BUTTON_CloseSocket.
function BUTTON_CloseSocket_Callback(hObject, eventdata, handles)
% hObject    handle to BUTTON_CloseSocket (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global SockClient;
SockClient.CloseSocket();