from django.conf.urls import url
from . import views
from django.conf import settings
from django.conf.urls.static import static

app_name = 'robweb'
urlpatterns = [
    url(r'^$', views.index, name='index'),
    url(r'^img_upload', views.img_upload, name='img_upload'),
    url(r'^gallery', views.gallery, name='gallery'),
    url(r'^img/(?P<img_name>.+)/$', views.detail, name='detail'),
    url(r'^result/(?P<img_name>.+)/$', views.result, name='result'),
] + static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
