#!/usr/bin/python
#-*-coding=utf-8-*-

from Tkinter import *
import sys
import paho.mqtt.client as mqtt
pencere=Tk()

def on_connect(client, userdata, rc):
    print(str(rc))
    client.subscribe(str(topice1.get()))

def on_message(client, userdata, msg):
    sub.insert(END, str(msg.payload)+"\n")
    print(msg.topic+" "+str(msg.payload))

def stopfunc():
    client.loop_stop()
    client.disconnect()

def subfunc():
    client.loop_stop()
    client.disconnect()
    client.connect(str(wbs1.get()), 1883, 60)
    client.loop_start()

def pubfunc():
    client.loop_stop()
    client.disconnect()
    client.connect(str(wbs1.get()), 1883, 60)
    client.publish(str(topice2.get()), str(messag1.get()))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

wbservice1 = Label(text="Web Servis")
wbservice1.grid(row=0, column=0)
wbs1 = Entry()
wbs1.insert(0,"iot.eclipse.org")
wbs1.grid(row=0, column=1)
topicl = Label(text="Topic")
topicl.grid(row=1, column=0)
topice1 = Entry()
topice1.insert(0, "Topic")
topice1.grid(row=1, column=1)
baglan = Button(text="Bağlan", command = subfunc)
baglan.grid(row=2, column=0)
durdur = Button(text="Durdur", command = stopfunc)
durdur.grid(row=2, column=1)
topic2 = Label(text="Topic")
topic2.grid(row=4, column=0)
topice2 = Entry()
topice2.insert(0,"Topic")
topice2.grid(row=4, column=1)
messag = Label(text="Komut")
messag.grid(row=5, column=0)
messag1 = Entry()
messag1.grid(row=5, column=1)
pub = Button(text="Komut Gönder", command=pubfunc)
pub.grid(row=6, column=0)
sub=Text(pencere, wrap=WORD, height=10, width=25)
sub.grid(row=7, columnspan=2)

#client.publish("/ersin", "c")
#client.loop_stop()
#client.disconnect()

mainloop()

