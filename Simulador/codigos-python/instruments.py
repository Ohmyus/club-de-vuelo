import pygame
import numpy as np

class needle():
    def __init__(self, length, width, center):
        self.length = length
        self.width = width
        self.center = center

    def draw_at(self, surface, angle):
        R = np.array([
            [np.cos(angle), -np.sin(angle)],
            [np.sin(angle), np.cos(angle)]
        ])

        arrow_pts = np.array([
            [-self.width/2, 0],
            [self.width/2, 0],
            [0, -self.length],
        ])

        rotated_pts = (arrow_pts @ R.T) + self.center

        pygame.draw.polygon(surface, "white", [rotated_pts[0,:], rotated_pts[1,:], rotated_pts[2,:]])

class airspeed_indicator():
    def __init__(self):
        self.pos = [540, 500]
        self.radius = 120
        self.long_needle = needle(self.radius-20, 5, self.pos)

        self.maxVal = 500
        self.minVal = 0
        self.maxAng = 300
        self.minAng = 0

    def update(self, data, surface):
        airspeed = data["speed"]
        needle_angle = np.deg2rad(self.minAng + self.maxAng*(airspeed/(self.maxVal - self.minVal)))
        pygame.draw.circle(surface, (0,0,0), self.pos, self.radius)
        self.long_needle.draw_at(surface, needle_angle)

class altimeter():
    def __init__(self):
        self.pos = [750, 200]
        self.radius = 120
        self.needles = [
            needle(self.radius-20, 5, self.pos),
            needle(self.radius-40, 10, self.pos),
            needle(self.radius-60, 15, self.pos)   
        ]
            

        self.maxVals = [0, 0, 0]
        self.minVals = [100, 1000, 10000]
        self.maxAngs = [360, 360, 360]
        self.minAngs = [0,0,0]

    def update(self, data, surface):
        altitude = data["altitude"]
        pygame.draw.circle(surface, (0,0,0), self.pos, self.radius)
        needle_angle = np.zeros(3)
        for i in range(3):
            needle_angle[i] = np.deg2rad(self.minAngs[i] + self.maxAngs[i]*(altitude/(self.maxVals[i] - self.minVals[i])))
            self.needles[i].draw_at(surface, needle_angle[i])

class instruments_display():
    def __init__(self, instruments):
        pygame.init()
        self.screen = pygame.display.set_mode((1080, 720))
        pygame.display.set_caption("Instruments Display")
        self.clock = pygame.time.Clock()
        self.instruments = [instr["instr"] for instr in instruments]
        self.running = True

    def step_frame(self, data_dict):
        if self.running == True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    self.running = False
                    return
            
            self.screen.fill("#454545")
            for instr in self.instruments:
                instr.update(data_dict, self.screen)

            pygame.display.flip()



if __name__ == "__main__":

    instruments = instruments_display([
     {"Type" : "Airspeed Indicator", "instr" : airspeed_indicator()},
     {"Type" : "Altimeter", "instr" : altimeter()},
    ])

    import random
    speed = 100
    altitude = 1000

    running = True
    while running:
        speed += random.randint(-1, 1)  # fake speed changes
        altitude += random.randint(-3, 3)  # fake altitude changes
        data = {"speed": speed, "altitude" : altitude}
        instruments.step_frame(data) 