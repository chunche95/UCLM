#!/bin/python3

import sys
import Ice

class ClockService(Ice.Object):
    def __init__(self): # Constructor
        self.time = None
    def getTime(self, current): # current is a Ice.Current object	
        self.time = current
    def sync(self, other):
        # Obtener la hora del reloj del otro servidor
        otherTime = self.getTime()
        # Calculamos la diferencia entre las dos horas
        diff = self.time - otherTime
        # Si la diferencia es positiva, avanzamos nuestro reloj
        if diff > 0:
            self.time += diff
        # Si la diferencia es negativa, atrazamos nuestro reloj
        elif diff < 0:
            self.time -= diff
    def __str__(self): # To string method
        return str(self.time)
if __name__ == 'main':
    # Creamos un servidor Ice
    ic = Ice.initialize()
    adaptador = ic.createObjectAdapter("ClockService")
    object = ClockService()
    adaptador.add(object, ic.stringToIdentity("ClockService"))
    adaptador.activate()
    # Esperamos a que el cliente se conecte
    ic.waitForShutdown()