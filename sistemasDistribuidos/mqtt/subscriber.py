#!/usr/bin/env python3

import json, time, argparse, paho.mqtt.client as mqtt # import the required libraries

def print_hot_deal(deal):
    print(f'[!] Hot Deal \n'
          + f'\t{deal["name"]} by {deal["developer"]} ({deal["type"]})\n'
          + f'\tOn sale with a {deal["discount"]}% discount\n\n')
    
def print_deal(deal):
    print(f'[ ] New deal \n'
        +f'\t{deal["name"]} by {deal["developer"]} ({deal["type"]})\n'
        +f'\tOn sale with a {deal["discount"]}% discount\n\n')
    
def on_message(client, userdata, msg):
    topics = msg.topic.split('/')

    deal = json.loads(msg.payload)
    deal['developer'] = topics[3]
    deal['type'] = topics[2]

    
    if deal['discount'] >= 50:
        print_hot_deal(deal)
    else:
        print_deal(deal)

parser = argparse.ArgumentParser(description='Videogame deals subscriber')

parser.add_argument(
    '-d', '--developer',
    nargs='+',
    default=['+'], # default value is a wildcard (alld developers)
    help='Specify developer(s) of subscribed videogame deals',
    required=False
)

parser.add_argument(
    '-t', '--type',
    nargs='+',
    default=['+'], # default value is a wildcard (all types of games)
    help='Specify type(s) of subscribed videogame deals',
    required=False
)

args = parser.parse_args()

subscriber = mqtt.Client() # create a new instance of the client
subscriber.on_message = on_message # attach the on_message callback function
subscriber.connect('localhost', 1883) # connect to broker (localhost)

for vg_type in args.type:
    for developer in args.developer:
        subscriber.subscribe(
            f'videogames/deals/{vg_type}/{developer}'
        ) # subscribe to the topic (videogames/deals/{type}/{developer})

print ('Waiting for videogame deals...')

try:
    subscriber.loop_forever() # start the loop
except KeyboardInterrupt:
    subscriber.disconnect()
    print('Exit')