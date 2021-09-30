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
port = 1337

  
class App(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.start()

    def callback(self):
        self.funcionando = False
        self.root.quit()

    def run(self):
        self.funcionando = True
        self.root = Tk()
        self.root.title("Output")
        self.root.geometry('1280x720')
        self.root.configure(background='#00ff00')
        self.root.protocol("WM_DELETE_WINDOW", self.callback)
        self.frame = Frame(self.root,width=1280, height=720)
        self.croma = Frame(self.root,width=1280, height=720, background='#00ff00')
        Canvas(self.croma,bg='#00ff00',width=1280, height=720).pack()
        self.croma.pack()
        self.media_player = vlc.MediaListPlayer()
        self.iniciar_vlc()
        self.root.mainloop()
    
    def iniciar_vlc(self):
        self.player = vlc.Instance()
        self.media_list = self.player.media_list_new()
        
        self.media_list.add_media(self.player.media_new("Azul.mp4")) 
        self.media_list.add_media(self.player.media_new("Amarelo.mp4"))        
        self.media_list.add_media(self.player.media_new("certa.mp4"))
        self.media_list.add_media(self.player.media_new("errada.mp4"))
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
    
    def statuss(self):
        return self.funcionando
    
app = App()
Funcionando = True
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect(('8.8.8.8', 1))
ip = s.getsockname()[0]
print("IP= "+ip+":"+str(8089))

ip = "0.0.0.0"

def vermelho(address, *args):
    if(args[0]==1.0):
        app.tocar_video(1,4.3) 
    else:
        pass

def azul(address, *args):
    if(args[0]==1.0):
        app.tocar_video(0,4.3) 
    else:
        pass
        
def certa(address, *args):
    if(args[0]==1.0):
        app.tocar_video(2,7.4) 
    else:
        pass

def errada (address, *args):
    if(args[0]==1.0):
        app.tocar_video(3,7.4) 
    else:
        pass
      
def default_handler(address, *args):
    print("teve um estranho" + str(address)+":" + str(args))
    
dispatcher = Dispatcher()
dispatcher.map("/vermelho", vermelho)
dispatcher.map("/azul", azul)
dispatcher.map("/certa", certa)
dispatcher.map("/errada", errada)

dispatcher.set_default_handler(default_handler)

async def loop():
    while(app.statuss()):
        print("...")
        await asyncio.sleep(1)


async def init_main():
    server = AsyncIOOSCUDPServer((ip, port), dispatcher, asyncio.get_event_loop())
    transport, protocol = await server.create_serve_endpoint()  # Create datagram endpoint and start serving

    await loop()  # Enter main loop of program

    transport.close()  # Clean up serve endpoint


asyncio.run(init_main())