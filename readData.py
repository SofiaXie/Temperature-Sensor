import serial
import time 
import requests

def post_data(temp = 101):
    curr_time = time.localtime()
    day = curr_time.tm_mday
    date_to_post = f"{time.strftime("%A", curr_time)}, {time.strftime("%B", curr_time)} {day}{"st" if day % 10 == 1 else "nd" if day % 10 == 2 else "rd" if day % 10 == 3 else "th"}"
    # time_to_post = f"{curr_time.tm_hour % 12}:{curr_time.tm_min:02} {"PM" if curr_time.tm_hour > 11 else "AM"}"
    time_to_post = f"{curr_time.tm_hour % 12 if curr_time.tm_hour % 12 else 12}:{curr_time.tm_min:02} {"AM" if curr_time.tm_hour < 12 or curr_time.tm_hour == 24 else "PM"}"

    try:
        data = {
            'temp': float(temp),
            'time': time_to_post,
            'date': date_to_post
        }

        # response = requests.post("https://ec2-18-221-189-137.us-east-2.compute.amazonaws.com/api/weather", json=data)
        response = requests.post(" http://localhost:3000/api/weather", json=data)

        if response.status_code == 200:
            print('that worked!')
        else:
            print(f"status code {response.status_code}")
            print('that did not work')
            print(response.text)
        
    except Exception as e:
        print("error", str(e))

ardunio_port = "COM5"
baud_rate = 9600

ser = serial.Serial(ardunio_port, baud_rate)
time.sleep(2); #connection settle time

def avg(alist):
    temp = 0
    for i in alist:
        temp += float(i)
    
    return temp / len(alist)

try:
    alist = []
    while True:
        if ser.in_waiting > 0:
            if len(alist) == 10:
                 post_data(round(avg(alist), 2))
                 alist = []
            else:
                line = ser.readline().decode('utf-8').rstrip()
                alist.append(line)
           
except KeyboardInterrupt:
    print("Exiting program")

temp = line

ser.close()