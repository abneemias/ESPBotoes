from pythonosc.osc_server import AsyncIOOSCUDPServer
from pythonosc.dispatcher import Dispatcher
import asyncio
import threading
from tkinter import *
import winsound

import vlc
import time
import socket

media_player = vlc.MediaListPlayer() 
  
player = vlc.Instance() 
  
media_list = player.media_list_new() 
  
media = player.media_new("Amarelo.mp4") 
media2 = player.media_new("Azul.mp4") 
media3 = player.media_new("falhou.mp4")  



  
media_list.add_media(media) 
media_list.add_media(media2)
media_list.add_media(media3)
 

  
media_player.set_media_list(media_list) 
  
new = player.media_player_new() 
  
media_player.set_media_player(new) 


funcionando = True

def _from_rgb(rgb):
    """translates an rgb tuple of int to a tkinter friendly color code
    """
    return "#%02x%02x%02x" % rgb   
class App(threading.Thread):

    def __init__(self):
        threading.Thread.__init__(self)
        self.start()

    def callback(self):
        funcionando = False
        self.root.quit()

    def run(self):
        self.root = Tk()
        self.root.geometry("500x200")
        self.root.protocol("WM_DELETE_WINDOW", self.callback)
        funcionando = True
        self.label = Label(self.root, text=" ",font=('Helvatical bold',100))
        self.label.pack()
        self.vlabel = Label(self.root, text="vermelho=",font=('Helvatical bold',10))
        self.alabel = Label(self.root, text="azul=",font=('Helvatical bold',10))
        self.vlabel.pack()
        self.alabel.pack()
        self.root.mainloop()
    
    def mudar(self,nome):
        self.root.winfo_children()[0].config(text=nome)
    def mudar_cor(self,red):
        self.root.winfo_children()[0].config(fg =_from_rgb((int(red*240), int(red*240), int(red*240))))
    def vmudar(self,nome):
        self.root.winfo_children()[1].config(text=("vermelho="+str(("%.2f" % nome))))       
    def amudar(self,nome):
        self.root.winfo_children()[2].config(text=("azul="+str(("%.2f" % nome))))


app = App()

ip = "0.0.0.0"
port = 1337

def print_push3(address, *args):
    if args[0] > 0 :
        media_player.play_item_at_index(0) 
        time.sleep(4.3)
        media_player.set_pause(1)
        
def print_push4(address, *args):    
    if args[0] > 0 :
        media_player.play_item_at_index(1) 
        time.sleep(4.3)
        media_player.set_pause(1) 
        
def print_push1(address, *args):
    if args[0] > 0 :
        media_player.play_item_at_index(2) 
        time.sleep(7.4)
        media_player.set_pause(1)  


def numero(address, *args):
    if(args[0]>=0):
        app.mudar(args[0])
    else:
        app.mudar("-----")

def vermelho(address, *args):
    if(args[0]>=0):
        app.vmudar(args[0])
    else:
        app.vmudar("-----")

def azul(address, *args):
    if(args[0]>=0):
        app.amudar(args[0])
    else:
        app.amudar("-----")
        
def vvermelho(address, *args):
    if(args[0]>0):
        media_player.play_item_at_index(0) 
        time.sleep(4.3)
        media_player.set_pause(1)
    else:
        pass

def vazul(address, *args):
    if(args[0]==1.0):
        media_player.play_item_at_index(1) 
        time.sleep(4.3)
        media_player.set_pause(1) 
    else:
        pass

def iniciar(address, *args):
    if(args[0]==1):
        winsound.Beep(1000, 100)       

def default_handler(address, *args):
    print("teve um estranho" + str(address)+":" + str(args))

def brilho(address, *args):
    app.mudar_cor(args[0])
    
dispatcher = Dispatcher()
dispatcher.map("/contagem*",numero)
dispatcher.map("/tvermelho*",vermelho);
dispatcher.map("/tazul*",azul);
dispatcher.map("/start*",iniciar)
dispatcher.map("/brilho*",brilho)
dispatcher.map("/azul*",vazul)
dispatcher.map("/vermelho*",vvermelho)

dispatcher.set_default_handler(default_handler)

async def loop():
    """Example main loop that only runs for 10 iterations before finishing"""
    i=0
    while(funcionando):
        print(f"Loop {i}")
        i=i+1
        await asyncio.sleep(1)


async def init_main():
    server = AsyncIOOSCUDPServer((ip, port), dispatcher, asyncio.get_event_loop())
    transport, protocol = await server.create_serve_endpoint()  # Create datagram endpoint and start serving

    await loop()  # Enter main loop of program

    transport.close()  # Clean up serve endpoint


asyncio.run(init_main())