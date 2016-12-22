from django import forms
from .models import TfImage


class ImageForm(forms.ModelForm):

    class Meta:
        model = TfImage
        fields = ('img',)
