#!/bin/python3

import Ice
import sys

class ClockClient:
    def __init__(self):
        self.ic = Ice.initialize()
        self.proxy = self.ic.stringToProxy("ClockService:tcp -h localhost -p 10000")
        self.clock = self.proxy.ice_checkedCasr("::ClockService")

    def getTime(self):
        return self.clock.getTime()
    
    def sync(self):
        self.clock.sync(self.clock)

if __name__ == "__main__":
    client = ClockClient()
    print(client.getTime())
    client.sync()
    print(client.getTime())