from django.conf.urls import url
from . import views

app_name = 'robweb'
urlpatterns = [
    url(r'^$', views.index, name='index'),
    url(r'^img_upload', views.img_upload, name='img_upload'),
]