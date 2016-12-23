"""
SerialLink object.

@author: Peter Corke
@copyright: Peter Corke
"""

from numpy import *
from utility import *
from transform import *
import copy
from Link import *
from robot import *
from plot import * 

class SerialLink(object):
    """SerialLink object.
    Instances of this class represent a robot manipulator
    within the toolbox.
    """
        
    def __init__(self, arg=None, gravity=None, base=None, tool=None, name='', comment='', manuf=''):
        """
        SerialLink object constructor.  Create a robot from a sequence of Link objects.
        
        Several basic forms exist:
            - SerialLink()        create a null SerialLink
            - SerialLink(SerialLink)   create a clone of the SerialLink object
            - SerialLink(links)   create a SerialLink based on the passed links
            
        Various options can be set using named arguments:
        
            - gravity; gravitational acceleration (default=[0,0,9.81])
            - base; base transform (default 0)
            - tool; tool transform (default 0)
            - name
            - comment
            - manuf
        """

        if isinstance(arg, SerialLink):
            for k,v in arg.__dict__.items():
                if k == "links":
                    self.__dict__[k] = copy.copy(v);           
                else:
                    self.__dict__[k] = v;           
        elif len(arg) > 1 and isinstance(arg[0], Link):
            self.links = arg;
        else:
            raise AttributeError;

        # fill in default base and gravity direction
        if gravity != None:
            self.gravity = gravity;
        else:
            self.gravity = [0, 0, 9.81];
        
        if base != None:
            self.base = base;
        else:
            self.base = mat(eye(4,4));
        
        if tool != None:
            self.tool = tool;
        else:
            self.tool = mat(eye(4,4));

        if manuf:
            self.manuf = manuf
        if comment:
            self.comment = comment
        if name:
            self.name = name

        #self.handle = [];
        #self.q = [];
        #self.plotopt = {};
        #self.lineopt = {'Color', 'black', 'Linewidth', 4};
        #self.shadowopt = {'Color', 'black', 'Linewidth', 1};

        return None;

    def __str__(self):
        s = 'ROBOT(%s, %s)' % (self.name, self.config());
        return s;
        
    def __repr__(self):
        s = '';
        if self.name:
            s += 'name: %s\n' % (self.name)
        if self.manuf:
            s += 'manufacturer: %s\n' % (self.manuf)
        else:
            s += 'manufacturer: '
        
        if self.comment:
            s += 'commment: %s\n' % (self.comment)
        else:
            s += 'commment: '
            
        for link in self.links:
            s += str(link) + '\n';
        return s;   

    def __mul__(self, r2):
        r = SerialLink(self);        # clone the robot
        print r
        r.links += r2.links;
        return r;

    def copy(self):
        """
        Return a copy of the SerialLink object
        """
        return copy.copy(self);
               
    def ismdh(self):
        return self.mdh;
        
    def config(self):
        """
        Return a configuration string, one character per joint, which is
        either R for a revolute joint or P for a prismatic joint.
        For the Puma560 the string is 'RRRRRR', for the Stanford arm it is 'RRPRRR'.
        """
        s = '';
        
        for link in self.links:
            if link.sigma == 0:
                s += 'R';
            else:
                s += 'P';
        return s;

    def nofriction(self, all=False):
        """
        Return a Robot object where all friction parameters are zero.
        Useful to speed up the performance of forward dynamics calculations.
        
        @type all: boolean
        @param all: if True then also zero viscous friction
        @see: L{Link.nofriction}
        """
        r = SerialLink(self);
        r.name += "-nf";
        newlinks = [];
        for oldlink in self.links:
            newlinks.append( oldlink.nofriction(all) );
        r.links = newlinks;
        return r;
        
    def showlinks(self):
        """
        Shows details of all link parameters for this robot object, including
        inertial parameters.
        """

        count = 1;
        if self.name:
            print 'name: %s'%(self.name)
        if self.manuf:
            print 'manufacturer: %s'%(self.manuf)
        if self.comment:
            print 'commment: %s'%(self.comment)
        for l in self.links:
            print 'Link %d------------------------' % count;
            l.display()
            count += 1;
##-----------------------------------------------------------------------------------------------
##External Functions
    #From dynamics
    def accel(self, *args):
        return accel(self, *args)
    def coriolis(self, q, qd):
        return coriolis(self, q, qd)
    def inertia(self, value):
        return inertia(self,value)
    def cinertia(self, q):
        return cinertia(self, q)
    def gravload(self, q, gravity=None):
        return gravload(self, q, gravity=None)
    def rne(self, *args, **options):
        return rne(self, *args, **options)

    #from Jacobain
    def jacob0(self, q):
        return jacob0(self,q)
    def jacobn(self, q):
        return jacobn(self, q)

    #form Kinematics
    def fkine(self, q):
        return fkine(self, q)
    def iknie(self, tr, q=None, m=None):
        return iknie(self, tr, q=None, m=None)
    def ikine560(robot, T, configuration=''):
        return ikine560(robot, T, configuration='')
    
    #From robot
    def fdyn(self, t0, t1, torqfun, q0, qd0, varargin):
        return fdyn(self, t0, t1, torqfun, q0, qd0, varargin)
    def itorque(self, q,qdd):
        return itorque(self, q, qdd)
    def manipulability(self, q, witch = 'yoshikawa'):
        return manipulability(self, q, witch = 'yoshikawa')
    def ospace(self, q, qd):
        return ospace(self, q, qd)

    def plot(self, tg, varargin):
        return plot(self, tg, varargin)
    
    
##------------------------------------------------------------------------------------------------
    def __setattr__(self, name, value):
        """
        Set attributes of the robot object
        
            - SerialLink.name = string (name of this robot)
            - SerialLink.comment = string (user comment)
            - SerialLink.manuf = string (who built it)
            - SerialLink.tool = 4x4 homogeneous tranform
            - SerialLink.base = 4x4 homogeneous tranform
            - SerialLink.gravity = 3-vector  (gx,gy,gz)
        """
        
        if name in ["manuf", "name", "comment"]:
            if not isinstance(value, str):
                raise ValueError, 'must be a string'
            self.__dict__[name] = value;
            
        elif name == "links":
            if not isinstance(value[0], Link):
                raise ValueError, 'not a Link object';
            self.__dict__[name] = value;
            self.__dict__['n'] = len(value);
            # set the robot object mdh status flag
            for link in self.links:
                if link.convention != self.links[0].convention:
                    raise 'robot has mixed D&H link conventions'
            self.__dict__['mdh'] = self.links[0].convention == Link.LINK_MDH;
            
        elif name == "tool":
            if not ishomog(value):
                raise ValueError, 'tool must be a homogeneous transform';
            self.__dict__[name] = value;

        elif name == "gravity":
            v = arg2array(value);
            if len(v) != 3:
                raise ValueError, 'gravity must be a 3-vector';
            self.__dict__[name] = mat(v).T
            
        elif name == "base":
            if not ishomog(value):
                raise ValueError, 'base must be a homogeneous transform';
            self.__dict__[name] = value;
            
        else:
            raise AttributeError;

