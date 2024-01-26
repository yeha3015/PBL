import cv2
import numpy as np
from PIL import Image
import os
IS_FALL_DOWN = 20000


# 画像を読み込む
cd = os.getcwd()
image = cv2.imread(cd+"/image_detect/person4.jpg")
h, _, _ = image.shape
res = 600 / h
image = cv2.resize(image, None, None, res, res)
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

#画像を600*400にする


# Haar Cascadeを使用して人物検出を行う
cascade = cv2.CascadeClassifier(cd+'/image_detect/haarcascade_fullbody.xml')
rects = cascade.detectMultiScale(gray, scaleFactor=1.005, minNeighbors=3)

# 結果を描画する
for (x, y, w, h) in rects:
    if w * h > IS_FALL_DOWN:
        cv2.rectangle(image, (x, y), (x + w, y + h), (0, 0, 255), 2)


# 結果を表示する
cv2.imshow('image', image)
cv2.waitKey(0)
cv2.destroyAllWindows()


