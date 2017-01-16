import cv2

camera = cv2.VideoCapture(1)
#fourcc = cv2.VideoWriter_fourcc(*'XVID')
#out = cv2.VideoWriter('output.avi', fourcc, 20.0, (640,480))

while True:
	success, frame = camera.read()
#print "width: %d pixels" % (frame.shape[1])
#print "height: %d pixels" % (frame.shape[0])
#print "channels: %d" % (frame.shape[2])
	#out.write(frame)
	w = camera.get(cv2.CAP_PROP_FRAME_WIDTH)
	h = camera.get(cv2.CAP_PROP_FRAME_HEIGHT)
	left_eye = frame[0:int(h), 0:int(w/2)]
	cv2.imshow("left", left_eye)
	if cv2.waitKey(1) & 0xFF == ord('q'):
		break

camera.release()
#out.release()
cv2.destroyAllWindows()
