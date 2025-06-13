########### Code Magic Mirror ############

#Importieren der benötigten Bibliotheken
from tkinter import *
from PIL import Image
from PIL import ImageTk
import requests
import json
from datetime import *
from time import *
import random
#from grovepi import *
import locale
locale.setlocale(locale.LC_ALL, 'de_DE.utf8')
#locale.setlocale(locale.LC_ALL, "de_DE")

############# FUNKTIONEN ###############

# Funktion zur Fenstergröße und mittig platzieren
def center_window(width, height):
    # get screen width & Hight
    screen_width = root.winfo_screenwidth()
    screen_height = root.winfo_screenheight()
    
    #calculate position x and y coordinates
    x = (screen_width/2) - (width/2)
    y = (screen_height/2) - (height/2)
    root.geometry("%dx%d+%d+%d" % (width, height, x, y))

# Funktion, um Bildgröße zu verändern
def img_resize(image, x, y):
    img = Image.open(image)
    img_temp = img.resize((x,y))
    img_klein = ImageTk.PhotoImage(img_temp)
    return img_klein

# Funktion, die Api URL aufruft und in ein JSON Format konvertiert
def call_url(url):
    response = requests.get(url)
    return json.loads(response.content)

# Funktion, die die Zeilen nach z Wörten teilt
#def line_split(text, z):
#    word_list = text.split()
#    first_line = word_list[:z]
#   second_line = word_list[z:z*2]
#    third_line = word_list[z*2:]
#    A = " ".join(first_line)
#    B = " ".join(second_line)
#    C = " ".join(third_line)
#    lines = str(A) + "\n" + str(B) + "\n" + str(C)
#    return lines

# Funktion, die die Headline alle 5 Sekunden aktualisiert
x=0
def update_news():
    global x
    headline = headlines[x%len(headlines)]['title']
    x+=1
    #headline_lines = line_split(headline, 10)
    #mirrorLabel4.config(text = "Das gibt's Neues:\n" + headline_lines)
    mirrorLabel4.config(text = "Das gibt's Neues:\n" + headline)
    mirrorLabel4.after(500, update_news)

# Funktion, die die Zeit nach 1 Sek aktualisiert
def my_time():
    time_string = strftime('%H:%M')# time format
    mirrorLabel8.config(text= time_string)
    mirrorLabel8.after(1000,my_time) # time delay of 1000 milliseconds
       
# Funktionen, die die Farben & Bild je nach Temperatur ändern lässt
def temp_farbe(temp):
    if temp < 10:
        mirrorLabel5.config(fg = "deep sky blue")
        mirrorLabel11.config(image = cold_img)
    elif 10 <= temp < 25:
        mirrorLabel5.config(fg = "spring green")
        mirrorLabel11.config(image = medium_img)
    elif temp >= 25:
        mirrorLabel5.config(fg = "sienna1")
        mirrorLabel11.config(image = hot_img)
def temp_min_farbe(temp):
    if temp < 10:
        mirrorLabel6.config(fg = "deep sky blue")
    elif 10 <= temp < 25:
        mirrorLabel6.config(fg = "spring green")
    elif temp >= 25:
        mirrorLabel6.config(fg = "sienna1")
def temp_max_farbe(temp):
    if temp < 10:
        mirrorLabel7.config(fg = "deep sky blue")
    elif 10 <= temp < 25:
        mirrorLabel7.config(fg = "spring green")
    elif temp >= 25:
        mirrorLabel7.config(fg = "sienna1")

# Funtkion, um je nach Wetter anderes Icon anzuzeigen
def wetter_icon(code):
    if code == 0:
        mirrorLabel9.config(image = bright_img)
    elif 0 < code < 3:
        mirrorLabel9.config(image = mainlyClear_img)
    elif code == 3:
        mirrorLabel9.config(image = cloudy_img)
    elif 45 <= code <= 48:
        mirrorLabel9.config(image = foggy_img)
    elif 51 <= code <= 67 or 80 <= code <= 86:
        mirrorLabel9.config(image = rainy_img)
    elif 71 <= code <= 77:
        mirrorLabel9.config(image = snowy_img)
    elif 95 <= code <= 99:
        mirrorLabel9.config(image = storm_img)

# Raumtemperatur
def raum_temp():
    dht_sensor_port = 4
    dht_sensor_type = 0
    [temp, hum] = dht(dht_sensor_port, dht_sensor_type)
    raum_temp = temp
    raum_humid = hum
    mirrorLabel13.config(text = "Raumtemperatur: " + str(raum_temp) + "°C" + "\n" + "Luftfeuchtigkeit: " + str(raum_humid) + "%",
                         justify = LEFT)     
    mirrorLabel13.after(1000, raum_temp)
    
# Funktion, um von BVG aktuelle Abfahrten abzubilden
def update_bvg():
    api_bvg = call_url('https://v6.bvg.transport.rest/stops/900023101/departures?duration=60&results=5&linesOfStops=false&remarks=true&language=de')
    bvg_list = []
    bvg_list_when=[]
    y = 0
    while y <= 4: #weil nur max 5 angezeigt werden, kann in URL geändert werden bei results = 5
        bvg_type = api_bvg['departures'][y]['line']['name']
        bvg_dir = api_bvg['departures'][y]['direction']
        bvg_when = api_bvg['departures'][y]['when'][11:16]
        bvg_list_when.append("Abfahrt: " + str(bvg_when))
        bvg_list.append(str(bvg_type) + ": " + str(bvg_dir))
        y+=1
    mirrorLabel12.config(text = 
                        str(bvg_list[0]) + "\n"+ str(bvg_list_when[0]) + "\n\n"+ 
                        str(bvg_list[1]) + "\n"+ str(bvg_list_when[1]) + "\n\n"+ 
                        str(bvg_list[2]) + "\n"+ str(bvg_list_when[2]) + "\n\n"+ 
                        str(bvg_list[3]) + "\n"+ str(bvg_list_when[3]) + "\n\n"+ 
                        str(bvg_list[4]) + "\n"+ str(bvg_list_when[4]) + "\n\n",
                         justify = RIGHT)
    mirrorLabel12.after(1000, update_bvg)
        
# Funktion, um alles sichtbar zu machen
def make_visible():
    #Guten Morgen und Advice
    mirrorLabel1.place(anchor = N, relx = 0.5, rely = 0.02) # Guten Morgen
    mirrorLabel10.place(anchor = N, relx = 0.5, rely = 0.09) # Advice
    
    #Wetter
    #mirrorLabel2.place(anchor = NW, relx = 0, rely = 2) # Wetter Text
    mirrorLabel51.place(anchor = SW, relx = 0.02, rely = 0.6) # Dein Wetter
    mirrorLabel5.place(anchor = SW, relx = 0.02, rely = 0.64) # aktuelle Temperatur
    mirrorLabel6.place(anchor = SW, relx = 0.02, rely = 0.67) # min Temp
    mirrorLabel7.place(anchor = SW, relx = 0.02, rely = 0.7) # max Temp
    mirrorLabel13.place(anchor = SW, relx = 0.02, rely = 0.8) #Raumtemp und Luftfeucht
    mirrorLabel11.place(anchor = SW, relx = 0.23, rely = 0.7) # Temp Icon
    mirrorLabel9.place(anchor = SW, relx = 0.16, rely = 0.7) # Niederschlag Icon
    
    #Uhr und Datum  
    mirrorLabel8.place(anchor = S, relx = 0.5, rely = 0.82) # Uhrzeit update
    mirrorLabel3.place(anchor = S, relx = 0.5, rely = 0.71) # Datum
    
    #BVG
    bfg_rely=0.87
    mirrorLabel12.place(anchor = S, relx = 0.85, rely = bfg_rely)# BVG Abfahrten
    mirrorLabel121.place(anchor = S, relx=0.861, rely=bfg_rely-0.4)#BVG Abfahren Überschrift
    
    #News
    mirrorLabel4.place(anchor = S, relx = 0.5, rely = 0.95) # News Feed

#Funktion, um alles unsichtbar zu machen
def make_invisible():
    mirrorLabel1.place_forget()
    #mirrorLabel2.place_forget()
    mirrorLabel3.place_forget()
    mirrorLabel4.place_forget()
    mirrorLabel51.place_forget()
    mirrorLabel5.place_forget()
    mirrorLabel6.place_forget()
    mirrorLabel7.place_forget()
    mirrorLabel8.place_forget()
    mirrorLabel9.place_forget()
    mirrorLabel10.place_forget()
    mirrorLabel11.place_forget()
    mirrorLabel12.place_forget()
    mirrorLabel121.place_forget()
    mirrorLabel13.place_forget()
    

# Enscheidung, ob Label angezeugt werden oder nicht
# Werden angezeigt, wenn jemand davorsteht
# Verschwinden, wenn 3 Sekunden niemand davor steht
ultrasonic_ranger = 7
oft=0
def visible():
    global oft
    distance = ultrasonicRead(ultrasonic_ranger)
    if distance <=20:
        make_visible()
        oft=0
    if distance > 20:
        oft+=1
        if oft==6:
            make_invisible()
    mirrorLabel1.after(500,visible)

########## MAIN #########
    
#Set-Up für unser Fenster
user = "Hannah"
root = Tk()
root.title("Dein Magic Morning")
root.configure(background= "black")    

# Nachrichten
api_news = call_url('https://newsapi.org/v2/top-headlines?'
       'country=de&category=general&'
       'apiKey=f9614aa623054695ab72986a7f2e3b92')
# Liste mit Headlines aus Api request erstellen
headlines = api_news['articles']

# Zeit
raw_TS = datetime.now()
date_mirror = raw_TS.strftime("%d.%m.%Y")
date_now = raw_TS.strftime("%Y-%m-%d")
time_now = raw_TS.strftime("%H:00")
datetime_now = date_now + "T" + time_now

## Wetter
api_wetter = call_url('https://api.open-meteo.com/v1/forecast?latitude=52.52&longitude=13.41&hourly=temperature_2m,precipitation,weathercode&daily=temperature_2m_max,temperature_2m_min,precipitation_sum&timezone=Europe%2FBerlin')

wetter_datum = api_wetter['hourly']['time']
wetter_minmax_datum = api_wetter['daily']['time']

datetime_index = wetter_datum.index(datetime_now)
date_index = wetter_minmax_datum.index(date_now)

# Wetterdaten
aktuelle_temp = api_wetter['hourly']['temperature_2m'][int(datetime_index)]
daily_temp_max = api_wetter['daily']['temperature_2m_max'][int(date_index)]
daily_temp_min = api_wetter['daily']['temperature_2m_min'][int(date_index)]
daily_niederschlag = api_wetter['hourly']['weathercode'][int(datetime_index)]

#Bilder anpassen
bright_img = img_resize("bright.png", 50, 50)
cloudy_img = img_resize("cloudy.png", 50, 50)
mainlyClear_img = img_resize("cloudy-day.png", 50, 50)
rainy_img = img_resize("rain.png", 50, 50)
foggy_img = img_resize("mist.png", 50, 50)
snowy_img = img_resize("snowy.png", 50, 50)
storm_img = img_resize("storm.png", 50, 50)
cold_img = img_resize("cold.png", 45, 45)
medium_img = img_resize("medium.png", 45, 45)
hot_img = img_resize("hot.png", 45, 45)


# Advice 2
sprueche = open("Kalendersprueche.txt", 'r', encoding='utf-16')
line=random.randint(0,37)
advice=sprueche.readlines()[line]


# Font Settings
my_font_clock =('Microsoft JhengHei UI Light', 70, 'bold') # display size and style
my_font_date =('Microsoft JhengHei UI Light ',18) # display size and style
my_font_news = ('Microsoft JhengHei UI Light',18)
my_font_weather = ('Microsoft JhengHei UI Light ',15)
my_font_title_weather = ('Microsoft JhengHei UI Light ',15, 'bold')
my_font_title = ('Microsoft JhengHei UI Light',40,'bold')
my_font_advice = ('URW Chancery L',18)
my_font_title_bvg = ('Microsoft JhengHei UI Light', 15, 'bold')
my_font_bvg = ('Microsoft JhengHei UI Light', 15)

# Background
my_bg = "black"

# Schriftfarbe:
my_fg = "snow"

# creating Widgets
mirrorLabel1 = Label(root, text = "Hallo " + user + ":)", font = my_font_title, bg = my_bg, fg = my_fg)
#mirrorLabel2 = Label(root, text = "Heutiges Wetter:", font = my_font_weather, bg = my_bg, fg = my_fg)
mirrorLabel51 = Label(root, text = "Deine Wettervorhersage: \n", font=my_font_title_bvg, bg=my_bg, fg=my_fg)
mirrorLabel5 = Label(root, text = "aktuell: " + str(aktuelle_temp)+ " °C", font = my_font_bvg, bg = my_bg, fg = my_fg)
mirrorLabel6 = Label(root, text = "min: " + str(daily_temp_min) + " °C", font = my_font_bvg, bg = my_bg, fg = my_fg) # mindesttemp
mirrorLabel7 = Label(root, text = "max: " + str(daily_temp_max) + " °C", font = my_font_bvg, bg = my_bg, fg = my_fg) # maxtemp
mirrorLabel8 = Label(root, font = my_font_clock, bg = my_bg, fg =my_fg)
mirrorLabel3 = Label(root, text = datetime.now().strftime('%A') + ', der ' + date_mirror, font = my_font_date, bg = my_bg, fg = my_fg)
mirrorLabel9 = Label(root, text = daily_niederschlag, font = my_font_weather, bg = my_bg, fg =my_fg)
mirrorLabel10 = Label(root, text = "Dein Motivationsspruch für heute: \n" + str(advice), font = my_font_advice, bg = my_bg, fg =my_fg, wraplength = 700)
mirrorLabel11 = Label(root, bg = my_bg, fg =my_fg) # Temp Icons
mirrorLabel121 = Label(root, text = "Deine nächsten Abfahrten: \n", font=my_font_title_bvg, bg=my_bg, fg=my_fg)
mirrorLabel12 = Label(root, font=my_font_bvg, bg = my_bg, fg =my_fg) # BVG Abfahrten
mirrorLabel13 = Label(root, font = my_font_bvg, bg = my_bg, fg =my_fg)
mirrorLabel4 = Label(root, font = my_font_news, background = my_bg, fg = my_fg, wraplength = 700) # News 


visible()
#make_visible() # statt visible() wenn kein Grovepi angeschlossen
update_bvg()
my_time()
update_news()
raum_temp()

center_window(840,900)
#center_window(1100,675)
temp_farbe(aktuelle_temp)
temp_max_farbe(daily_temp_max)
temp_min_farbe(daily_temp_min)
wetter_icon(daily_niederschlag)

# Dauerschleife
root.mainloop()