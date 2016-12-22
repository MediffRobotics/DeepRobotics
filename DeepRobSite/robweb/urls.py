from django.conf.urls import url
from . import views
from django.conf import settings
from django.conf.urls.static import static

app_name = 'robweb'
urlpatterns = [
    url(r'^$', views.index, name='index'),
    url(r'^img_upload', views.img_upload, name='img_upload'),
] + static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)