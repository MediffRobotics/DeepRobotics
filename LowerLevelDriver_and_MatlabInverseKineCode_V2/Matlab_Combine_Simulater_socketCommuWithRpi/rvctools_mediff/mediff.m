classdef mediff
    properties
        L=Link();
        mediffArm=SerialLink();
        T_Origion;
        Speed;
    end
    
    methods 
        function InverseKine(obj)
            a=0;
        end
        function MoveUp(obj,Direction)
            %Direction=0£º Up
            %Direction=1£º Down
            %Direction=2£º Forward
            %Direction=3£º Backward
            UpMat = [0 0 0 0; ...
                    0 0 0 0;...
                    0 0 0 1;...
                    0 0 0 0];
            DownMat = [0 0 0 0; ...
                    0 0 0 0;...
                    0 0 0 -1;...
                    0 0 0 0];
            ForwMat=[0 0 0 1; ...
                    0 0 0 0;...
                    0 0 0 0;...
                    0 0 0 0];
               
            BackMat = [0 0 0 -1; ...
               0 0 0 0;...
               0 0 0 0;...
               0 0 0 0];

           %% inverse kinematics      
            % current state
            T1 = obj.mediffArm.fkine(obj.mediffArm.getpos()); 
            % move up by one
            if(0==Direction)
                obj.T_Origion = T1 +UpMat;
            elseif(1==Direction)
                obj.T_Origion = T1 +DownMat;    
            elseif(2==Direction)        
                obj.T_Origion = T1 +ForwMat;    
            elseif(3==Direction)        
                obj.T_Origion = T1 +BackMat;                    
            end
            % compute a Cartesian path   
            T = ctraj(T1, obj.T_Origion, obj.Speed); 	
            qi = obj.mediffArm.ikine(T);
            
           %% Display the movements 
            obj.mediffArm.plot(qi);    
            obj.mediffArm.getpos();
        end              
        
        function obj = mediff()
           %% Setting robot link                        
            %                theta   d       a   alpha
            obj.L(1) = Link([ 0      6       3   pi/2    0]);            
            obj.L(2) = Link([ 0      0       6   pi      0]);
            obj.L(3) = Link([ 0      0       0   -pi/2   0]);
            obj.L(3).qlim = [-pi pi];
            obj.L(4) = Link([ 0      6       0   pi/2    0]);
            obj.L(5) = Link([ 0      0       0   -pi/2   0]);
            obj.L(6) = Link([ 0      4       0   0       0]);

            obj.mediffArm = SerialLink(obj.L, 'name', 'MEDIFF ARM', ...
                'manufacturer', 'Unimation', 'ikine', 'puma',...
                'comment', 'viscous friction; params of 8/95');
            obj.mediffArm.model3d = 'UNIMATE/MOTOMAN';
            obj.mediffArm.plot([0 0 0 0 0 0] );
            
            % Initial robot position affine matrix
            obj.T_Origion=obj.mediffArm.fkine([0 0 0 0 0 0]);
            obj.Speed=10;
            obj.mediffArm.teach()                      
        end
    end
  
    
end 