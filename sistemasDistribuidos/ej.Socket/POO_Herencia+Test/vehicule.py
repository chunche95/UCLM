#!/usr/bin/python3

class Vehicule:
    person_price = 10 # price per person
    # constructor de la clase
    def __init__(self, capacity ):
        self.capacity = capacity # nº person on site
    def fare(self):
        return self.capacity * self.person_price    
# Main program 
if __name__ == "__main__":    
    # Object creation
    vehicule = Vehicule(6)
    # Obtaining the price of the vehicule
    vehicule.person_price = 20 # No modification
    Vehicule.person_price = 20 # change price
    print("Vehicule capacity:", vehicule.capacity)
    print("Vehicule fare: " , vehicule.fare)

