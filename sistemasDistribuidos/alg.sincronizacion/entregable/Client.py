#!/bin/python3

import Ice 
import sys
import time

Ice.loadSlice('sincronizacion.ice')
import ssdd

class CristianClient(Ice.Application):
    def run(self, argv):
        # Cristian:tcp -h 192.168.8.224 -p 4080
        proxy = self.communicator().stringToProxy('Cristian:tcp -h 192.168.8.224 -p 4080')
        Cristian = ssdd.CristianPrx.checkedCast(proxy)
        print(Cristian)
        
        SyncProxy = self.communicator().stringToProxy("SyncReport:tcp -h 192.168.8.224 -p 4080")
        SyncReport = ssdd.SyncReportPrx.checkedCast(SyncProxy)
        print(SyncReport)
        if not Cristian:
            raise RuntimeError("Invalid proxy")
        dni = '09146352B'
        #Cristian.write(dni)
        #SyncReport.write(dni)
        tc1 = time.time()
        print(tc1)
        serverTime = Cristian.getServerTime(dni, tc1)
        tc2 = time.time()
        print(tc2)
        error = (tc2-tc1) / 2.0
        print(error)
        SyncReport.notifyTime(dni,'Paulino Bermudez Rodriguez', tc2, serverTime, error)


client = CristianClient()
sys.exit(client.main(sys.argv))
    

