#!/bin/python3

import Ice 
import time

class ClockServiceI(Clock.ClockService):
    def getTime(self, current=None):
        return time.time()
with Ice.Initialize(sys.argv) as communicator:
    adapter = communicator.createObjectAdapterWithEndpoints("ClockServiceAdapter", "default -p 10000")
    object = ClockServiceI()
    adapter.add(object, communicator.stringToIdentity("ClockService"))
    adapter.active()
    communicator.waitForShutdown()
