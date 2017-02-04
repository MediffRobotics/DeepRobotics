import os.path
import numpy as np
from six.moves import urllib
import tensorflow as tf
import re
from tensorflow.python.framework import graph_util
from tensorflow.python.framework import tensor_shape
from tensorflow.python.platform import gfile
from tensorflow.python.util import compat
import cv2


class PreprocessingImgs():
  
  
  def ResizingImgs(self):
    # read imgs
    for filename in self.file_list: 
      
      img=cv2.imread(filename)
      img=cv2.resize(img, (256, 256))
      cv2.imshow('img',img)
      cv2.waitKey(1)
      # resizing imgs 
    
    # writing to a new folder
  
  def ReOrderingimgLists(self):
    print "Reordering list"
  
  def GeneratingImgPathLists(self,img_dir):
    print "generating img path list"
    
  def ReadAllFromDirectory(self,image_dir):
    """Builds a list of training images from the file system.
    """
    if not gfile.Exists(image_dir):
      print("Image directory '" + image_dir + "' not found.")
      return None
    result = {}
    sub_dirs = [x[0] for x in gfile.Walk(image_dir)]
    print "SubDirs:"
    print sub_dirs 
    
    # The root directory comes first, so skip it.
    is_root_dir = True
    for sub_dir in sub_dirs:
      if is_root_dir:
        is_root_dir = False
        continue
        
      extensions = ['jpg', 'jpeg', 'JPG', 'JPEG']
      self.file_list = []
      dir_name = os.path.basename(sub_dir)
      
      print dir_name
      if dir_name == image_dir:
        continue
      print("Looking for images in '" + dir_name + "'")
      for extension in extensions:
        file_glob = os.path.join(image_dir, dir_name, '*.' + extension)
        self.file_list.extend(gfile.Glob(file_glob))
      if not self.file_list:
        print('No files found')
        continue
      label_name = re.sub(r'[^a-z0-9]+', ' ', dir_name.lower())
      training_images = []
      testing_images = []
      validation_images = []
     
      for file_name in self.file_list:
          print file_name
          
    return self.file_list





if __name__ == '__main__':  
  objPreprocessImgs=PreprocessingImgs()
  objPreprocessImgs.ReadAllFromDirectory("TrainImg_imgs")
  objPreprocessImgs.ResizingImgs()      
