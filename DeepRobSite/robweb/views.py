from django.shortcuts import render, get_object_or_404
from django.http import JsonResponse
from .forms import ImageForm
from .models import TfImage
from django.utils import timezone
from django.core.paginator import Paginator, EmptyPage, PageNotAnInteger
from django.views.decorators.csrf import csrf_exempt
from django.core.files.images import ImageFile


def index(request):
    return render(request, 'robweb/index.html')


def detail(request, img_name):
    tf_image = get_object_or_404(TfImage, name=img_name)
    context = {
        'img': tf_image
    }
    return render(request, 'robweb/detail.html', context)


def result(request, img_name):
    tf_image = get_object_or_404(TfImage, name=img_name)
    response = {
        'img_name': img_name,
        'result': tf_image.result
    }
    return JsonResponse(response)


@csrf_exempt
def img_upload(request):
    if request.method == 'POST':
        img_form = ImageForm(request.POST, request.FILES)
        if img_form.is_valid():
            if 'img' in request.FILES:
                TfImage.objects.create(
                    name=request.FILES['img'].name,
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


def gallery(request):
    imgs = TfImage.objects.order_by('-upload_date')
    paginator = Paginator(imgs, 9)  # Show 9 words per page

    page = request.GET.get('page')
    try:
        imgs = paginator.page(page)
    except PageNotAnInteger:
        # If page is not an integer, deliver first page.
        imgs = paginator.page(1)
    except EmptyPage:
        # If page is out of range (e.g. 9999), deliver last page of results.
        imgs = paginator.page(paginator.num_pages)

    return render(request, 'robweb/gallery.html', {'imgs': imgs})
