from __future__ import unicode_literals
from django.db import models
from django.utils.encoding import python_2_unicode_compatible


@python_2_unicode_compatible
class TfImage(models.Model):
    img = models.ImageField(upload_to='tf_images', blank=False, null=True)
    name = models.CharField(max_length=200, blank=True, default='')
    result = models.TextField(default='', blank=True, null=True)
    upload_date = models.DateTimeField(blank=True, null=False)

    def __str__(self):
        return self.img.name
