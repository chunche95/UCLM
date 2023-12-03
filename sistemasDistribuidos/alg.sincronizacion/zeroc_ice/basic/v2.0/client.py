#!/bin/python3

import Ice
import sys
import TimeoutError
Ice.loadSlice("Clock.ice")

import Clock

class ClockClient(Ice.Application):
    def run(self, argv):
        # # Creamos un proxy para el servicio de reloj
        # proxy = self.communicator().stringToProxy("ClockService:default -p 10000")
        # # Lo convertimos al tipo correcto
        # clock = Clock.ClockServicePrx.checkedCast(proxy)
        # if not clock:
        #     raise RuntimeError("Invalid proxy")
        # # Obtenemos la hora del reloj remoto
        # remoteTime = clock.getTime()
        # # Obtenemos la hora local
        # localTime = time.time()
        # # Calculamos la diferencia entre las dos horas
        # diff = localTime - remoteTime
        # # Si la diferencia es positiva, avanzamos nuestro reloj
        # if diff > 0:
        #     clock.sync(diff)
        # # Si la diferencia es negativa, atrazamos nuestro reloj
        # elif diff < 0:
        #     clock.sync(-diff)
        # # Imprimimos la hora del reloj remoto
        # print("Remote clock time: " + str(remoteTime))
        # # Imprimimos la hora del reloj local
        # print("Local clock time: " + str(localTime))
        # # Imprimimos la diferencia entre las dos horas
        # print("Diff: " + str(diff))
        # return 0
        proxy = self.communicator().stringToProxy("ClockService:default -p 10000")
        clockService = Clock.ClockServicePrx.checkedCast(proxy)

        if not clockService:
            raise RuntimeError("Invalid proxy")
        
        while True:
            currentTime = clockService.getTime()
            print(f"Local time: {time.ctime()}, server Time: {currentTime}")
            time.sleep(5)
    
    if __name__ == '__main__':
        app = ClockClient()
        sys.exit(app.main(sys.argv))