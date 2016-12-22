from django.shortcuts import render
from django.http import HttpResponse
from .forms import ImageForm
from .models import TfImage
from django.utils import timezone


def index(request):
    return render(request, 'robweb/index.html')


def img_upload(request):
    if request.method == 'POST':
        img_form = ImageForm(request.POST, request.FILES)
        if img_form.is_valid():
            if 'img' in request.FILES:
                TfImage.objects.create(
                    img=request.FILES['img'],
                    upload_date=timezone.datetime.now()
                )
        else:
            print(img_form.errors)

    else:
        img_form = ImageForm()
        context = {
            'img_form': img_form,
        }
        return render(request, 'robweb/img_upload.html', context)

    return render(request, 'robweb/img_res.html')
