#!/usr/bin/python3
from unittest import TestCase
from vehicule import Vehicule
from car import Car

class TestVehicule(TestCase):
    def setUp(self):
        self.vehicule = Vehicule(6)
    def test_default_fare_60(self):
        self.assertEquals(self.vehicule.fare(), 60) # Comparable value for default value

class TestCar(TestCase):
    def setUp(self):
        self.car = Car(6)
    def test_default_fare_120(self):
        self.assertEquals(self.car.fare(), 120) # Comparable value for default value
