#sub.py
import paho.mqtt.client as mqtt
import base64
import datetime

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
  print("Connected with result code "+str(rc))
  # Subscribing in on_connect() means that if we lose the connection and
  # reconnect then subscriptions will be renewed.
  client.subscribe("camera2")
  
# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
  #f = open('receive.jpg','wb')
  #f.write(msg.payload)
  #f.close()+
  #print("image received")
  dt = datetime.datetime.now()
  dts = str(dt)
  dtn = dts.replace(':','-')
  image_64_decode = base64.decodebytes(msg.payload)
  image_result = open(r"/home/nachanon/Desktop/camera2/" + str(dtn) + ".png", 'wb') #แก้ path ที่ save ด้วย
  image_result.write(image_64_decode)
  print("image2 received")
  
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect("test.mosquitto.org", 1883, 60)

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_forever()