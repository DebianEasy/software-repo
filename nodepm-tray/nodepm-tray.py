#!/usr/bin/env python3
from pystray import MenuItem as item
import pystray
from PIL import Image
import subprocess
import os
import sys
from threading import Thread
import time

version="0.2.4"

def lightup():
    subprocess.run("nodepm backlight up",shell=True)
def lightdown():
    subprocess.run("nodepm backlight down",shell=True)
def displaymode_switch():
    subprocess.run("nodepm timer switch",shell=True)
    subprocess.run("notify-send 'NodePm Timer '`nodepm timer status`",shell=True)
    update()
def powermode():
    p0 = subprocess.run('nodepm battery|grep -i line|grep -i on',stdout=subprocess.PIPE,shell=True)
    #print(p0.returncode)
    if p0.returncode == 0:
        line='Ac'
    else:
        line='Bat'
    p1 = subprocess.run('nodepm battery|tail -1',stdout=subprocess.PIPE,shell=True)
    bat_stat = p1.stdout
    bat_stat = str(bat_stat)
    bat_stat = bat_stat.lstrip("b")
    bat_stat = bat_stat.strip('\'')
    bat_stat = bat_stat.rstrip("\\n")
    bat_stat = bat_stat.split(' ')[len(bat_stat.split(' '))-1]
    line = line+' '+bat_stat+'%'
    return line
def powermode_show():
    strtmp = powermode()
    strtmp = 'notify-send '+strtmp
    subprocess.run(strtmp,shell=True)
    update()
def displaymode():
    p2 = subprocess.run('nodepm timer status',stdout=subprocess.PIPE,shell=True)
    line = p2.stdout
    line = str(line)
    line = line.lstrip("b")
    line = line.lstrip("'")
    line = line.rstrip("'")
    line = line.split("\\t")[len(line.split("\\t"))-1]
    line = line.split("\\")[0]
    #print(line)
    return line
def geticon(icon_name):
    #print(os.path.isfile('/etc/nodepm-tray/icon/'+icon_name))
    if os.path.isfile('/etc/nodepm-tray/icon/'+icon_name):
        image=Image.open('/etc/nodepm-tray/icon/'+icon_name)
    elif os.path.isfile('/var/lib/nodepm-tray/icon/'+icon_name):
        image=Image.open('/var/lib/nodepm-tray/icon/'+icon_name)
    elif os.path.isfile('/usr/local/share/nodepm-tray/icon/'+icon_name):
        image=Image.open('/usr/local/share/nodepm-tray/icon/'+icon_name)
    elif os.path.isfile('/usr/share/nodepm-tray/icon/'+icon_name):
        image=Image.open('/usr/share/nodepm-tray/icon/'+icon_name)
    else:
        image=Image.new("RGB", (32, 32), (255, 255, 255))
    return image
def getimagename(disp_flag,pw_supply,bat_capa):
    if disp_flag != "on" :
        icon_name = "display.png"
    elif pw_supply == "Ac" :
        icon_name = "charging.png"
    elif 90 < bat_capa :
        icon_name = "full.png"
    elif 65 < bat_capa <= 90 :
        icon_name = "high.png"
    elif 30 < bat_capa <=65 :
        icon_name = "half.png"
    elif bat_capa <= 30 :
        icon_name = "low.png"
    return icon_name
def update():
    global notify_line_old
    global battery_capacity_old
    global menu_line_old
    global display_line_old
    global power_supply_old
    global image_name_old
    global display_flag_old
    notify_line = powermode()
    power_supply = notify_line.split(' ')[0]
    battery_capacity = int(notify_line.split(' ')[len(notify_line.split(' '))-1].rstrip('%'))
    menu_line = 'power status: '+power_supply+" "+notify_line.split(' ')[len(notify_line.split(' '))-1]
    display_flag = displaymode()
    display_line = 'timer status: '+display_flag
    image_name=getimagename(display_flag,power_supply,battery_capacity)
    if image_name_old != image_name:
        image = geticon(image_name)
        icon.icon = image
    if notify_line_old != notify_line:
        icon.title = notify_line
    if display_line_old != display_line or menu_line_old != menu_line:
        icon.menu = (item('backlight up', lightup), item('backlight down', lightdown),item(display_line, displaymode_switch),item(menu_line,powermode_show))
    notify_line_old = notify_line
    menu_line_old = menu_line
    display_line_old = display_line
    battery_capacity_old = battery_capacity
    image_name_old = image_name
    power_supply_old = power_supply
    display_flag_old = display_flag
    return 0
def refresh():
    global notify_line_old
    global battery_capacity_old
    global menu_line_old
    global display_line_old
    global power_supply_old
    global image_name_old
    global display_flag_old
    notify_line = powermode()
    power_supply = notify_line.split(' ')[0]
    battery_capacity = int(notify_line.split(' ')[len(notify_line.split(' '))-1].rstrip('%'))
    menu_line = 'power status: '+power_supply+" "+notify_line.split(' ')[len(notify_line.split(' '))-1]
    display_flag = displaymode()
    display_line = 'timer status: '+display_flag
    image_name=getimagename(display_flag,power_supply,battery_capacity)
    image = geticon(image_name)
    notify_line_old = notify_line
    menu_line_old = menu_line
    display_line_old = display_line
    battery_capacity_old = battery_capacity
    image_name_old = image_name
    power_supply_old = power_supply
    icon.icon = image
    icon.title = notify_line
    icon.menu = (item('backlight up', lightup), item('backlight down', lightdown),item(display_line, displaymode_switch),item(menu_line,powermode_show))
    return 0
def icon_run():
    icon.run()

if len(sys.argv) > 1 :
    if sys.argv[1] == '--help':
        print("NodePm Tray Program")
        print('Version: '+version)
        print("Usage:\t"+sys.argv[0])
        print(" --help\t\tto print help page")
        print(" --wait\t\tto wait for nodepm daemon to start instead of stop tray program when nodepm daemon not detected")
        exit(2)
    else:
        if os.path.exists("/run/nodepm")==False:
            print("NodePm daemon not found!")
            exit(1)
else:
    if os.path.exists("/run/nodepm")==False:
        print("NodePm daemon not found!")
        exit(1)
notify_line = powermode()
battery_capacity = int(notify_line.split(' ')[len(notify_line.split(' '))-1].rstrip('%'))
power_supply = notify_line.split(' ')[0]
menu_line = 'power status: '+power_supply+" "+notify_line.split(' ')[len(notify_line.split(' '))-1]
display_flag = displaymode()
display_line = 'timer status: '+display_flag
image_name=getimagename(display_flag,power_supply,battery_capacity)
image = geticon(image_name)
notify_line_old = notify_line
power_supply_old = power_supply
menu_line_old = menu_line
display_line_old = display_line
battery_capacity_old = battery_capacity
image_name_old = image_name
display_flag_old = display_flag
menu = (item('backlight up', lightup), item('backlight down', lightdown),item(display_line, displaymode_switch),item(menu_line,powermode_show))
icon = pystray.Icon("NodePm applet",image,notify_line,menu)
thread_icon = Thread(target=icon_run)
thread_icon.start()
count = 0
while True:
    time.sleep(5)
    Thread(target=update).start()
    #thread_update.join()
    count = count + 1
    if count >= 12 :
        Thread(target=refresh).start()
        #thread_refresh.join()
