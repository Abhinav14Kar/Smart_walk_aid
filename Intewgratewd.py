
import urllib.parse
import urllib.request
import mysql.connector
import time
from pushbullet import Pushbullet


wifi_ssid = 'Galaxy A3102DE'
wifi_password = 'csli6803'


thingspeak_api_key = 'NJ5UMAVME42KJNEE'
channel_id = '2370857'

pushbullet_api_key = 'o.srpazgEBfF4G2UdV0v956rjLzOoRPbxe'
pb = Pushbullet(pushbullet_api_key)


connection = mysql.connector.connect(
    host="localhost",
    user="root",
    password="123456",
    database="ghost",
    autocommit=True
)
cursor = connection.cursor()

def fetch_thingspeak_data():
    url = f'https://api.thingspeak.com/channels/2370857/feeds/last.json?api_key=NJ5UMAVME42KJNEE'
    response = urllib.request.urlopen(url)
    data = response.read().decode('utf-8')
    return eval(data)

try:
    while True:
        
        thingspeak_data = fetch_thingspeak_data()
        
        
        weight = float(thingspeak_data['field1'])
        ax = float(thingspeak_data['field2'])
        ay = float(thingspeak_data['field3'])
        az = float(thingspeak_data['field4'])

        # Apply calibration (replace with your calibration factors)
        # weight *= 1.0 / 1e32
        # ax *= 1.0 / 1e32
        # ay *= 1.0 / 1e15
        # az *= 1.0 / 1e50

        
        print(f"Weight: {weight} g, Ax: {ax}, Ay: {ay}, Az: {az}")

        
        query = "INSERT INTO mydata (weight, ax, ay, az) VALUES (%s, %s, %s, %s)"
        values = (weight, ax, ay, az)
        cursor.execute(query, values)

        
        if weight <= -2.80 and (abs(ax) > 200 or abs(ay) > 200 or abs(az) > 1040):
             alert_message = f"ALERT: Weight - {weight}g, Ax - {ax}, Ay - {ay}, Az - {az}"
             print(alert_message)

    
             push = pb.push_note("Alert", alert_message)


        
        time.sleep(1)

finally:
    
    cursor.close()
    connection.close()


