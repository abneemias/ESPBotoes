from pythonosc.osc_server import AsyncIOOSCUDPServer
from pythonosc.dispatcher import Dispatcher
import asyncio
import threading
from tkinter import *
import winsound

import vlc
import time
import socket

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
        self.root.title("Output")
        self.root.attributes('-fullscreen', True)
        self.root.geometry('1280x720')
        self.root.configure(background='black')
        self.root.protocol("WM_DELETE_WINDOW", self.callback)
        self.frame = Frame(self.root,width=1280, height=720)
        self.croma = Frame(self.root,width=1280, height=720, background='black')
        self.label = Label(self.croma, text=" ",font=('Helvatical bold',400), fg='#ffffff',background='black')
        self.label.pack()
        self.vlabel = Label(self.croma,  fg='#ffffff', text="vermelho=",font=('Helvatical bold',30),background='black')
        self.alabel = Label(self.croma,  fg='#ffffff', text="azul=",font=('Helvatical bold',30),background='black')
        self.vlabel.pack()
        self.alabel.pack()
        self.croma.pack()
        self.media_player = vlc.MediaListPlayer()
        self.iniciar_vlc()
        self.root.mainloop()
    
    def iniciar_vlc(self):
        self.player = vlc.Instance()
        self.media_list = self.player.media_list_new()
        
        self.media_list.add_media(self.player.media_new("Azul.mp4")) 
        self.media_list.add_media(self.player.media_new("Amarelo.mp4"))        
        
        self.media_player.set_media_list(self.media_list)
        
        self.new = self.player.media_player_new()
        self.new.set_hwnd(self.frame.winfo_id())
        
        self.media_player.set_media_player(self.new) 
     
    def tocar_video(self,posicao,tempo):
        self.croma.pack_forget()
        self.frame.pack()
        self.media_player.play_item_at_index(posicao)
        time.sleep(tempo)
        self.media_player.set_pause(1)
        self.frame.pack_forget()
        self.croma.pack()
        
    def mudar(self,nome):
        self.croma.winfo_children()[0].config(text=nome)
    def mudar_cor(self,red):
        self.croma.winfo_children()[0].config(fg =_from_rgb((int((1-red)*255),int((1-red)*255),int((1-red)*255))))
    def vmudar(self,nome):
        self.croma.winfo_children()[1].config(text=("vermelho="+str(("%.2f" % nome))))       
    def amudar(self,nome):
        self.croma.winfo_children()[2].config(text=("azul="+str(("%.2f" % nome))))
    
    def statuss(self):
        return self.funcionando
    


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
        app.tocar_video(1,4.3)
    else:
        pass

def vazul(address, *args):
    if(args[0]==1.0):
        app.tocar_video(0,4.3) 
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
    while(app.statuss()):
        print(".")
        await asyncio.sleep(1)

async def init_main():
    server = AsyncIOOSCUDPServer((ip, port), dispatcher, asyncio.get_event_loop())
    transport, protocol = await server.create_serve_endpoint()  # Create datagram endpoint and start serving

    await loop()  # Enter main loop of program

    transport.close()  # Clean up serve endpoint


asyncio.run(init_main())