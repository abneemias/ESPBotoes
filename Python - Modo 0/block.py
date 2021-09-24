from pythonosc.dispatcher import Dispatcher
from pythonosc.osc_server import BlockingOSCUDPServer
import vlc
import time
import socket

#caso nao use o PureData mudar porta para 8089
port = 1337

media_player = vlc.MediaListPlayer() 
  
player = vlc.Instance() 
  
media_list = player.media_list_new() 
  
media = player.media_new("Amarelo.mp4") 
media2 = player.media_new("Azul.mp4") 
media3 = player.media_new("certa.mp4") 
media4 = player.media_new("errada.mp4") 



  
media_list.add_media(media) 
media_list.add_media(media2)
media_list.add_media(media3) 
media_list.add_media(media4)
 

  
media_player.set_media_list(media_list) 
  
new = player.media_player_new() 
  
media_player.set_media_player(new) 
 
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
        
def print_push2(address, *args):    
    if args[0] > 0 :
        media_player.play_item_at_index(3) 
        time.sleep(7.4)
        media_player.set_pause(1)
        
        
        
        
dispatcher = Dispatcher()
dispatcher.map("/vermelho", print_push3)
dispatcher.map("/azul", print_push4)
dispatcher.map("/certa", print_push1)
dispatcher.map("/errada", print_push2)



s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect(('8.8.8.8', 1))
ip = s.getsockname()[0]
print("IP= "+ip+":"+str(8089))

server = BlockingOSCUDPServer(('127.0.0.1', port), dispatcher)
server.serve_forever()  # Blocks forever