import threading
import time

class MyThread(threading.Thread):
    
    def __init__(self):
        
        global mutex        
        global num
        
        threading.Thread.__init__(self)                
        mutex=threading.Lock()
        
        num=0
      
    def run(self):
        global num            
        time.sleep(1)
        
        if mutex.acquire(1):
            num=num+1
            msg=self.name+'set num to '+str(num)
            print msg
            mutex.release()
            


def test():
    num=0
    
    for i in range(5):
        t=MyThread()        
        t.start()    
                
        
if __name__=='__main__':
    print 'main thread'
    test()



'''
import threading
import time
import random

class MyThread(threading.Thread):
    def run(self):
        wait_time=random.randrange(1,10)
        print "%s will wait %d seconds" %(self.name,wait_time)
        
        time.sleep(wait_time)
        print "I'm " + self.name
            
def test():
    for i in range(5):
        t=MyThread()
        #t.setDaemon(True)
        t.start()    
                
        
if __name__=='__main__':
    print 'main thread'
    test()
'''
