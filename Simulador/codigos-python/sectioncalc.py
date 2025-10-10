import numpy as np
class rubber_band():
    def __init__(self, od, id, length): #declaration must be in mm
        self.od = od
        self.id = id
        self.length = length
    
    def __str__(self):
        return "Goma " + str(self.od) + "-" + str(self.id)

    def calcSection(self): #output is in mm^2
        return np.pi*(self.od**2 - self.id**2)/4
    
mybandlist = [
    rubber_band(6, 3, 1000),
    rubber_band(7, 5, 1000),
    rubber_band(10, 5, 1000),
    ]

for aband in mybandlist:
    print(f"{str(aband)},\tA= {aband.calcSection()}")