import vlc
import serial
import paho.mqtt.client as mqtt
import time
ser = serial.Serial('/dev/ttyACM0', 9600)

def ConectMQTT(client, userdata, flags, rc):
    print("Connecting to server - " + str(rc))



def SendingMQTT(client, obj, mid):
    print("Message: " + str(mid))



def LogMQTT(client, obj, level, string):
    print(f"Log: {string}")


while True:
    move = ser.read()
    
    MyMQTT = mqtt.Client()
    MyMQTT.on_connect = ConectMQTT
    MyMQTT.on_publish = SendingMQTT
    MyMQTT.on_log = LogMQTT

    MyMQTT.connect("192.168.219.4", 1883)
    
    print(move)
    if (move==b'1'): #condition depending on the reading move
        #Path of the media for the first move
        player= vlc.MediaPlayer('/home/pi/Desktop/media/model4/ink4.mp4')
        player.play()
        player.set_fullscreen(True)
        MyMQTT.publish("dance/lights", "on") #message on sended to the topic dance/lights
        time.sleep(2)
        MyMQTT.publish("dance/lights", "off")
        while player.get_state() != vlc.State.Ended:
            
            time.sleep(1)  # Just to avoid unnecessary CPU use
            playerstate = str(player.get_state())
            # printing the state of the video
            print("State : " + str(playerstate))
            if (playerstate=="State.Ended"):
                player.stop()
                break
    if(move==b'2'):#condition depending on the reading move
        #Path of the media for the second move
        player= vlc.MediaPlayer('/home/pi/Desktop/media/Model1/magic.mp4')
        player.play()
        player.set_fullscreen(True)
        MyMQTT.publish("dance/lights", "on2")#message on2 sended to the topic dance/lights
        time.sleep(2)
        MyMQTT.publish("dance/lights", "off")
        while player.get_state() != vlc.State.Ended:
            
            time.sleep(1)  #  Just to avoid unnecessary CPU use
            playerstate = str(player.get_state())
            # printing the state of the video
            print("State : " + str(playerstate))
            if (playerstate=="State.Ended"):
                player.stop()
                break
    if(move==b'3'):#condition depending on the reading move
        #Path of the media for the thrird move
        player= vlc.MediaPlayer('/home/pi/Desktop/media/model4/ink1.mp4')
        player.play()
        player.set_fullscreen(True)
        MyMQTT.publish("dance/lights", "on3")#message on3 sended to the topic dance/lights
        time.sleep(2)
        MyMQTT.publish("dance/lights", "off")
        while player.get_state() != vlc.State.Ended:
            
            time.sleep(1)  # Just to avoid unnecessary CPU use
            playerstate = str(player.get_state())
            #  printing the state of the video
            print("State : " + str(playerstate))
            if (playerstate=="State.Ended"):
                player.stop()
                break