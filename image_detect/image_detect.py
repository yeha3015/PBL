import cv2
IS_FALL_DOWN = 20000

# 画像を読み込む
image = cv2.imread('person4.jpg')
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Haar Cascadeを使用して人物検出を行う
cascade = cv2.CascadeClassifier('haarcascade_fullbody.xml')
rects = cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

# 結果を描画する
for (x, y, w, h) in rects:
    if w * h > IS_FALL_DOWN:
        cv2.rectangle(image, (x, y), (x + w, y + h), (0, 0, 255), 2)


resize = cv2.resize(image, (600, 400))
# 結果を表示する
cv2.imshow('image', resize)
cv2.waitKey(0)
cv2.destroyAllWindows()