#!/usr/bin/python3

from vehicule import Vehicule

class Car(Vehicule):
    person_price = 20 # 20€/person
    
    def __init__(self,capacity):
        super().__init__(capacity)