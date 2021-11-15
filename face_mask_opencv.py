##-------------------------------------------------------------------------
import cv2
import os
from tensorflow.keras.preprocessing.image import img_to_array
from tensorflow.keras.models import load_model
from tensorflow.keras.applications.mobilenet_v2 import preprocess_input
import numpy as np
import datetime
import matplotlib.pyplot as plt
# import urllib.request
import paho.mqtt.publish as publish
import base64

## model & path file
cascPath = os.path.dirname(
    cv2.__file__) + "haarcascade_frontalface_alt2.xml"
faceCascade = cv2.CascadeClassifier("haarcascade_frontalface_alt2.xml")
model = load_model("mask_detector.model")

## parameter
user = "6301012610078"
ID_1 = [] 
p = 0
sc = 0
check_detect = 0  
## parameters for esp32
# ID_2 = []
# p_2 = 0
# sc_2 = 0
# check_detect_2 = 0

# url = "http://192.168.1.32/cam-hi.jpg" ## url camera
video_capture = cv2.VideoCapture(0)

while True:
    try:
        ret, frame = video_capture.read()
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        faces = faceCascade.detectMultiScale(gray,scaleFactor=1.1,minNeighbors=5,minSize=(60, 60),flags=cv2.CASCADE_SCALE_IMAGE)
        faces_list=[]
        preds=[]
        
        if check_detect == 0:
            if faces != ():
                check_detect += 1
                p += 1
                sc += 1
                ID_1.append(p)
                print("---------- Found !!!!!! ------------")
            else:
                pass
        if check_detect == 1:
            if faces == ():
                check_detect = check_detect-1
            else :
                pass
## esp32
    #     imgResponse = urllib.request.urlopen(url)
    #     imgnp = np.array(bytearray(imgResponse.read()), dtype = np.uint8)
    #     img = cv2.imdecode(imgnp, -1)
    #     gray_2 = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    #     face_2 = faceCascade.detectMultiScale(gray_2,scaleFactor=1.1,minNeighbors=5,minSize=(60, 60),flags=cv2.CASCADE_SCALE_IMAGE)
    #     faces_list_2=[]
    #     preds_2=[]
    #     if check_detect_2 == 0:
    #         if face_2 != ():
    #             check_detect_2 += 1
    #             p_2 += 1
    #             sc_2 += 1
    #             ID_2.append(p_2)
    #             print("---------- Found toooooooo!!!!!! ------------")
    #         else:
    #             pass
    #     if check_detect_2 == 1:
    #         if face_2 == ():
    #             check_detect_2 = check_detect_2 - 1
    #         else :
    #             pass

        for (x, y, w, h) in faces:  ## วาดเส้นกรอบหน้า
            ## timestamp
            dt = datetime.datetime.now()
            dts = str(dt)
            dtn = dts.replace(':','-')

            face_frame = frame[y:y+h,x:x+w]
            face_frame = cv2.cvtColor(face_frame, cv2.COLOR_BGR2RGB)
            face_frame = cv2.resize(face_frame, (224, 224))
            face_frame = img_to_array(face_frame)
            face_frame = np.expand_dims(face_frame, axis=0)
            face_frame =  preprocess_input(face_frame)
            faces_list.append(face_frame)
            if len(faces_list)>0:
                preds = model.predict(faces_list)

            for pred in preds:
                (mask, withoutMask) = pred
            
            label = "Mask" if mask > withoutMask else "No Mask"            
            color = (0, 255, 0) if label == "Mask" else (0, 0, 255)
            label = "{}: {:.2f}%".format(label, max(mask, withoutMask) * 100)
            cv2.putText(frame, label, (x, y- 10),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.45, color, 2)
            cv2.rectangle(frame, (x, y), (x + w, y + h),color, 2)

            if "No Mask: 100.00%" in label:
                if sc != 0: ## ถ่ายรูป          
                    cv2.imwrite("data/"+str(dtn)+".jpg",frame) 
                    sc = 0
                    image = open(r"C:\Users\asus\Downloads\FACE cv\FACE_DETECT\data/"+str(dtn)+".jpg", 'rb') #ส่งภาพนั้นไปที่ sub ผ่าน mqtt ---> เลือก path files
                    image_read = image.read()
                    image_64_encode = base64.encodebytes(image_read)
                    publish.single(f'{ user }', image_64_encode, qos=1, hostname='test.mosquitto.org')
                    time.sleep(5)         
        ## Display the resulting frame      
        cv2.imshow('Video', frame)


## for esp32
    #     for (x, y, w, h) in face_2:
    #          ## timestamp
    #         dt = datetime.datetime.now()
    #         dts = str(dt)
    #         dtn = dts.replace(':','-')

    #         face_img = img[y:y+h,x:x+w]
    #         face_img = cv2.cvtColor(face_img, cv2.COLOR_BGR2RGB)
    #         face_img = cv2.resize(face_img, (224, 224))
    #         face_img = img_to_array(face_img)
    #         face_img = np.expand_dims(face_img, axis=0)
    #         face_img =  preprocess_input(face_img)
    #         faces_list_2.append(face_img)
    #         if len(faces_list_2)>0:
    #             preds_2 = model.predict(faces_list_2)

    #         for pred_2 in preds_2:
    #             (mask, withoutMask) = pred_2
    #         label_2 = "Mask" if mask > withoutMask else "No Mask"

    #         color_2 = (0, 255, 0) if label_2 == "Mask" else (0, 0, 255)
    #         label_2 = "{}: {:.2f}%".format(label_2, max(mask, withoutMask) * 100)
    #         cv2.putText(img, label_2, (x, y- 10),
    #                     cv2.FONT_HERSHEY_SIMPLEX, 0.45, color_2, 2)

    #         cv2.rectangle(img, (x, y), (x + w, y + h),color_2, 2)
    #         if "No Mask: 100.00%" in label_2:
    #             if sc_2 != 0: ## ถ่ายรูป          
                    # cv2.imwrite("data/"+str(dtn)+".jpg",frame) 
                    # image = open(r"data/"+str(dtn)+".jpg", 'rb') #ส่งภาพนั้นไปที่ sub ผ่าน mqtt ---> เลือก path files
                    # image_read = image.read()
                    # image_64_encode = base64.encodebytes(image_read)
                    # publish.single(f'{user}', image_64_encode, qos=1, hostname='test.mosquitto.org')
    #                 sc_2 = 0
    #         # Display the resulting frame
    #     cv2.imshow('Video', img)            

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    except Exception as ex:
        p -= 1
        ID_1.pop
        pass
        
video_capture.release()        
cv2.destroyAllWindows()   
##--------------------------------------------------------------------------------
