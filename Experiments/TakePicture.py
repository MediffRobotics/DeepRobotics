import cv2
import threading
import time
class CCamera(threading.Thread):

    def __init__(self):
        #Init threading
        threading.Thread.__init__(self)


        # Camera 0 is the integrated web cam on my netbook
        self.camera_port = 1
        #Number of frames to throw away while the camera adjusts to light levels
        self.ramp_frames = 30
        # Now we can initialize the camera capture object with the cv2.VideoCapture class.
        # All it needs is the index to a camera port.
        self.camera = cv2.VideoCapture(self.camera_port)

        print "Init camera system"
        ###Init camera
        # Ramp the camera - these frames will be discarded and are only used to allow v4l2
        # to adjust light levels, if necessary
        for i in xrange(self.ramp_frames):
         temp = self.get_image()

        self.frame=[]

    #Show image thread
    def run(self):
        while True:
            self.get_image()
            self.showImg()
    def showImg(self):
        #print "show img"
        cv2.imshow("left", self.frame)
        cv2.waitKey(1)
        #if cv2.waitKey(1) & 0xFF == ord('q'):
		#    return
        #time.sleep(1)

    # Captures a single image from the camera and returns it in PIL format
    def get_image(self):
        #read is the easiest way to get a full image out of a VideoCapture object.
        retval, tmpframe = self.camera.read()
        w = self.camera.get(cv2.CAP_PROP_FRAME_WIDTH)
    	h = self.camera.get(cv2.CAP_PROP_FRAME_HEIGHT)
        self.frame = tmpframe[0:int(h), 0:int(w/2)]

    def saveImage(self):
        print 'Saving image...'
        file = "test_image.png"
        # A nice feature of the imwrite method is that it will automatically choose the
        # correct format based on the file extension you provide. Convenient!
        cv2.imwrite(file, self.frame)


    def releaseCamera(self):
        # You'll want to release the camera, otherwise you won't be able to create a new
        # capture object until your script exits
        print "Camera resource cleared"
        self.camera.release()
        #cv2.destroyAllWindows()

if __name__=='__main__':
    objCamera=CCamera()
    objCamera.setDaemon(True)
    objCamera.start()

    time.sleep(2)
    '''
    while True:
        cmd=raw_input("Please input cmd:")
        objCamera.saveImage()
        '''
    observation = objCamera.frame
    print 'pass'
    objCamera.releaseCamera()
