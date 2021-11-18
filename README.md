


# Face-Mask-Detector
คำอธิบายส่วนของโค้ดโปรแกรมนี้

![image](https://user-images.githubusercontent.com/87509273/142445712-7a0b16db-34cb-4dd5-996f-d88a68f22614.png)


**โปรเจคนี้เกี่ยวกับ**
Project ของกลุ่มเราทำเกี่ยวกับการตรวจจับใบหน้าของคนที่ไม่ใส่แมสก์ ผ่านกล้อง Webcam และ esp32cam โดยใช้ OpenCV ในการวิเคราะห์รูปภาพ และใช้ paho-mqtt ในการส่งรูปภาพในระยะไกลทำให้สามารถนำไปประยุกต์ใช้ได้ใน
สถานที่ต่างๆที่มีคนเดินพลุกพล่าน เช่น ทางเข้าสวนสาธารณะ หรือทางเข้าศูนย์การค้า

**ทำอะไรได้บ้าง**
- ตรวจจับใบหน้าของคนที่ใส่แมสก์ และไม่ใส่แมสก์
- ส่งรูปภาพที่ตรวจจับได้ไปยังคอมพิวเตอร์เครื่องอื่น
- Monitor รูปภาพของคนที่ไม่ใส่แมส(ถ้าใช้ mqtt broker ที่มีความเร็วและการตอบสนองที่ดีกว่านี้)
- บันทึกรูปภาพของคนที่ไม่ใส่แมสก์ลงไปใน History และเรียกดูได้


**Framework ที่ใช้**
- opencv
- Tensorflow-Keras
- Paho MQTT publish
- GTK-3
- Glade

**วิธีการใช้งานโปรแกรม**

Subsciber 
1. สั่งใช้งาน sub.py เเละ sub2.py โดยกำหนด Topic และ Path ที่จะใช้จัดเก็บรูปภาพที่ถูกส่งมาจาก Publish
2. สั่งใช้งาน FMD_GUI.c
3. กดปุ่ม Play บน Gui แล้วสังเกตภาพที่ได้รับผ่านหน้าต่าง GUI หรือไฟล์ที่ตั้งเป็น Path ในการเก็บภาพไว้

Publisher
1. open face_mask_opencv.py
2. เลือก Topicให้ตรงกับทางฝั่ง Subsciber เเละ เลือก Pathสำหรับบันทึกไฟล์รูปภาพ
3. Run face_mask_opencv.py จะเปิดหน้าต่าง Opencv ที่ใช้ตรวจจับกล้องขึ้นมา
4. หากใส่แมสอยู่ให้ถอดแมส แล้วโปรแกรมจะทำการ Publish ภาพหน้าที่ไม่ใส่แมสไปยังจุดที่ Subsciber ไว้



**Credits**

Opencv/Model
- https://github.com/opencv/opencv/tree/master/data/haarcascades
- https://www.youtube.com/watch?v=Ax6P93r32KU

Esp32/Cam
- https://github.com/yoursunny/esp32cam

GUI
- https://classroom.google.com/u/1/c/MzY4ODkyNTcxMDU4
- https://www.youtube.com/watch?v=g-KDOH_uqPk


Link นำเสนอ
https://www.youtube.com/watch?v=s-55-uhtJYw




