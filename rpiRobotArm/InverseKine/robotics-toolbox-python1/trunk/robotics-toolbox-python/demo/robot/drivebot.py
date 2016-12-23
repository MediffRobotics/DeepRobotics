#DRIVEBOT Drive a graphical robot
#
#	DRIVEBOT(ROBOT)
#	DRIVEBOT(ROBOT, Q)
#
# Drive a graphical robot by means of a slider panel.
#
# If no graphical robot exists one is created in a new window.  Otherwise
# all graphical robots are 'driven'.
#
# If Q is specified it is used as the initial joint angle, otherwise
# it is taken from one of the existing graphical robots.
#
# SEE ALSO: ROBOT/PLOT, ROBOT

# MOD HISTORY:
# 	10/01 	fix bug for n<6
# $Log: drivebot.m,v $
# Revision 1.4  2002/04/14 10:12:13  pic
# Changed see also info.
#
# Revision 1.3  2002/04/01 11:47:12  pic
# General cleanup of code: help comments, see also, copyright, remnant dh/dyn
# references, clarification of functions.
#
# $Revision: 1.4 $

# Copyright (C) 2001-2002, by Peter I. Corke

function drivebot(a,b)
	bgcol = [135 206 250]/255;

	if isstr(a)
		% drivebot(name, j), graphical callback function
		name = a; j = b;
		rh = findobj('Tag', name);
		handles = get(gco, 'Userdata');
		scale = handles{3};
		for r=rh',
			rr = get(r, 'UserData');
			q = rr.q;
			if isempty(q),
				q = zeros(1,rr.n);
			end
			if gco == handles{1},
				% get value from slider
				q(j) = get(gco, 'Value') / scale(j);
				set(handles{2}, 'String', num2str(scale(j)*q(j)));
			else
				% get value from text box
				q(j) = str2num(get(gco, 'String')) / scale(j);
				set(handles{1}, 'Value', q(j));
			end
			rr.q = q;
			set(r, 'UserData', rr);
		end
		plot(rr, q)
		t6 = fkine(rr, q);
		h3 = get(findobj('Tag', 'T6'), 'UserData');
		for i=1:3,
			set(h3(i,1), 'String', sprintf('%.3f', t6(i,4)));
			set(h3(i,2), 'String', sprintf('%.3f', t6(i,3)));
		end
	else
		% drivebot(r, q)
		r = a;
		scale = ones(r.n,1);

		n = r.n;
		width = 300;
		height = 40;
		minVal = -pi;
		maxVal = pi;	

		qlim = r.qlim;
		if isempty(qlim),
			qlim = [minVal*ones(r.n,1) maxVal*ones(r.n,1)];
		end

		if nargin < 2,
		    q = zeros(1,n);
		else
			if isstr(b),
				if strncmp(b, 'deg', 3),
					disp('** in degree mode')
					L = r.link;
					for i=1:r.n,
						if L{i}.sigma == 0,
							scale(i) = 180/pi;
						end
					end
				end
			else
				q = b;
			end
		end
		t6 = fkine(r, q);
		fig = figure('Units', 'pixels', ...
		    'Position', [0 -height width height*(n+2)], ...
		    'Color', bgcol);
		set(fig,'MenuBar','none')
		delete( get(fig, 'Children') )

		% first we check to see if there are any graphical robots of
		% this name, if so we use them, otherwise create a robot plot.

		rh = findobj('Tag', r.name);

		% attempt to get current joint config of graphical robot
		if ~isempty(rh),
			rr = get(rh(1), 'UserData');
			if ~isempty(rr.q),
				q = rr.q;
			end
		end


		% now make the sliders
		for i=1:n,
			uicontrol(fig, 'Style', 'text', ...
				'Units', 'pixels', ...
				'BackgroundColor', bgcol, ...
				'Position', [0 height*(n-i) width*0.1 height*0.4], ...
				'String', sprintf('q%d', i));

			h(i) = uicontrol(fig, 'Style', 'slider', ...
				'Units', 'pixels', ...
				'Position', [width*0.1 height*(n-i) width*0.7 height*0.4], ...
				'Min', scale(i)*qlim(i,1), ...
				'Max', scale(i)*qlim(i,2), ...
				'Value', scale(i)*q(i), ...
				'Tag', sprintf('Slider%d', i), ...
				'Callback', ['drivebot(''' r.name ''',' num2str(i) ')']);

			h2(i) = uicontrol(fig, 'Style', 'edit', ...
				'Units', 'pixels', ...
				'Position', [width*0.8 height*(n-i) width*0.2 height*0.4], ...
				'String', num2str(scale(i)*q(i)), ...
				'Tag', sprintf('Edit%d', i), ...
				'Callback', ['drivebot(''' r.name ''',' num2str(i) ')']);

			% hang handles off the slider and edit objects
			handles = {h(i) h2(i) scale};
			set(h(i), 'Userdata', handles);
			set(h2(i), 'Userdata', handles);
		end

		uicontrol(fig, 'Style', 'text', ...
			'Units', 'pixels', ...
			'FontSize', 20, ...
			'HorizontalAlignment', 'left', ...
			'Position', [0 height*(n+1) 0.8*width height], ...
			'BackgroundColor', 'white', ...
			'String', r.name);

		% X
		uicontrol(fig, 'Style', 'text', ...
			'Units', 'pixels', ...
			'BackgroundColor', bgcol, ...
			'Position', [0 height*(n+0.5) 0.06*width height/2], ...
			'BackgroundColor', 'yellow', ...
			'FontSize', 10, ...
			'HorizontalAlignment', 'left', ...
			'String', 'x:');

		h3(1,1) = uicontrol(fig, 'Style', 'edit', ...
			'Units', 'pixels', ...
			'Position', [0.06*width height*(n+0.5) width*0.2 height/2], ...
			'String', sprintf('%.3f', t6(1,4)), ...
			'Tag', 'T6');

		% Y
		uicontrol(fig, 'Style', 'text', ...
			'Units', 'pixels', ...
			'BackgroundColor', bgcol, ...
			'Position', [0.26*width height*(n+0.5) 0.06*width height/2], ...
			'BackgroundColor', 'yellow', ...
			'FontSize', 10, ...
			'HorizontalAlignment', 'left', ...
			'String', 'y:');

		h3(2,1) = uicontrol(fig, 'Style', 'edit', ...
			'Units', 'pixels', ...
			'Position', [0.32*width height*(n+0.5) width*0.2 height/2], ...
			'String', sprintf('%.3f', t6(2,4)));

		% Z
		uicontrol(fig, 'Style', 'text', ...
			'Units', 'pixels', ...
			'BackgroundColor', bgcol, ...
			'Position', [0.52*width height*(n+0.5) 0.06*width height/2], ...
			'BackgroundColor', 'yellow', ...
			'FontSize', 10, ...
			'HorizontalAlignment', 'left', ...
			'String', 'z:');

		h3(3,1) = uicontrol(fig, 'Style', 'edit', ...
			'Units', 'pixels', ...
			'Position', [0.58*width height*(n+0.5) width*0.2 height/2], ...
			'String', sprintf('%.3f', t6(3,4)));

		% AX
		uicontrol(fig, 'Style', 'text', ...
			'Units', 'pixels', ...
			'BackgroundColor', bgcol, ...
			'Position', [0 height*(n) 0.06*width height/2], ...
			'BackgroundColor', 'yellow', ...
			'FontSize', 10, ...
			'HorizontalAlignment', 'left', ...
			'String', 'ax:');

		h3(1,2) = uicontrol(fig, 'Style', 'edit', ...
			'Units', 'pixels', ...
			'Position', [0.06*width height*(n) width*0.2 height/2], ...
			'String', sprintf('%.3f', t6(1,3)));

		% AY
		uicontrol(fig, 'Style', 'text', ...
			'Units', 'pixels', ...
			'BackgroundColor', bgcol, ...
			'Position', [0.26*width height*(n) 0.06*width height/2], ...
			'BackgroundColor', 'yellow', ...
			'FontSize', 10, ...
			'HorizontalAlignment', 'left', ...
			'String', 'ay:');

		h3(2,2) = uicontrol(fig, 'Style', 'edit', ...
			'Units', 'pixels', ...
			'Position', [0.32*width height*(n) width*0.2 height/2], ...
			'String', sprintf('%.3f', t6(2,3)));

		% AZ
		uicontrol(fig, 'Style', 'text', ...
			'Units', 'pixels', ...
			'BackgroundColor', bgcol, ...
			'Position', [0.52*width height*(n) 0.06*width height/2], ...
			'BackgroundColor', 'yellow', ...
			'FontSize', 10, ...
			'HorizontalAlignment', 'left', ...
			'String', 'az:');

		h3(3,2) = uicontrol(fig, 'Style', 'edit', ...
			'Units', 'pixels', ...
			'Position', [0.58*width height*(n) width*0.2 height/2], ...
			'String', sprintf('%.3f', t6(3,3)));


		set(h3(1,1), 'Userdata', h3);
		uicontrol(fig, 'Style', 'pushbutton', ...
			'Units', 'pixels', ...
			'FontSize', 16, ...
			'Position', [0.8*width height*n 0.2*width 2*height], ...
			'CallBack', 'delete(gcf)', ...
			'BackgroundColor', 'red', ...
			'String', 'Quit');


		if isempty(rh),
			figure
			plot(r, q);
		end
	end
