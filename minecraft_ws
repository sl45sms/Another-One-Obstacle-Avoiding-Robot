import py_mcws #https://github.com/HRTK92/py-mcws
import urllib.request

server = py_mcws.WebsocketServer()
robotServer = "http://192.168.178.59/"

@server.event
async def on_ready(host, port):
    print("Σύνδεση στον διακομιστή...")
    print(f"γράψε '/connect {host}:{port}' στο τερματικο του minecraft και στη συνέχεια πάτησε Enter.")

@server.event
async def on_connect():
    print("Συνδέθηκε το ρομποτάκι!")
    await server.command("say συνδέθηκε το ρομποτάκι!")   

@server.event
async def on_PlayerMessage(event):
    #print(event)
    #example event
    #{'body': {'message': '[___________] left', 'receiver': '', 'sender': '___________', 'type': 'say'}, 'header': {'eventName': 'PlayerMessage', 'messagePurpose': 'event', 'version': 17039360}}
    # check if message is a command left, right, forward, backward, stop, explore for the robot
    # and send the command to arduino via esp-01 module wifi
    if "left" in event['body']['message']:
        print("left")
        with urllib.request.urlopen(robotServer+'left') as response:
          html = response.read()
          print(html)
        pass
    elif "right" in event['body']['message']:
        print("right")
        with urllib.request.urlopen(robotServer+'right') as response:
          html = response.read()
          print(html)
        pass
    elif "forward" in event['body']['message']:
        print("forward")
        with urllib.request.urlopen(robotServer+'forward') as response:
          html = response.read()
          print(html)
        pass
    elif "backward" in event['body']['message']:
        print("backward")
        with urllib.request.urlopen(robotServer+'backward') as response:
          html = response.read()
          print(html)
        pass
    elif "stop" in event['body']['message']:
        print("stop")
        with urllib.request.urlopen(robotServer+'stop') as response:
          html = response.read()
          print(html)
        pass
    elif "explore" in event['body']['message']:
        print("explore")
        with urllib.request.urlopen(robotServer+'explore') as response:
          html = response.read()
          print(html)
        pass
    else:
        print("Message not recognized as a command")

server.start(host="0.0.0.0", port=19631)
