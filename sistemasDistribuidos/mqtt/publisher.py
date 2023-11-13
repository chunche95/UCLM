#!/usr/bin/env python3

import json, time, paho.mqtt.client as mqtt # import the required libraries

from videogames import deals # import the videogames list of dictionaries

def build_event(vg_data):
    return { # paho.mqtt.client.publish() requires a JSON object
        'name': vg_data['name'],  # name of the game
        'discount': vg_data['discount'], # discount percentage
    }

publisher = mqtt.Client() # create a new instance of the client
publisher.connect('localhost', 1883) # connect to broker (localhost)

print ('Publisher started... videogame deals')

for vg_data in deals: # iterate over the videogames list of dictionaries
    publisher.publish( # publish the event to the broker (localhost)
        f'videogames/deals/{vg_data["type"].lower()}/{vg_data["developer"].lower()}', # topic name (videogames/deals/{type}/{developer}) 
        json.dumps(build_event(vg_data)) # payload (JSON object) 
    )

    print('.', end='', flush=True) # print a dot to the console
    time.sleep(1) # wait 1 second

publisher.disconnect() # disconnect from broker (localhost)