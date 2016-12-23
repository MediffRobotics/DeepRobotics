from poster.encode import multipart_encode
from poster.streaminghttp import register_openers
import urllib2

register_openers()
img = 'avatar.jpeg'

with open(img, 'r') as f:
    datagen, headers = multipart_encode({"img": f})
    request = urllib2.Request("http://cmput466.top/img_upload", datagen, headers)
    response = urllib2.urlopen(request)
