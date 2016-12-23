import requests

img = 'avatar.jpeg'

url = 'http://cmput466.top/result/'
url += img

r = requests.get(url)
res = r.json()['result']

print(res)
