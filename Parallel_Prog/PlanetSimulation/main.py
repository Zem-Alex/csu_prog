import threading
import math
import time

class Planet:
    def __init__(self, name, x0, y0, z0, radius, speed):
        self.name = name
        self.x0 = x0
        self.y0 = y0
        self.z0 = z0
        self.radius = radius
        self.speed = speed
        self.angle = 0

    def move(self):
        while True:
            x = self.x0 + self.radius * math.cos(self.angle)
            y = self.y0 + self.radius * math.sin(self.angle)
            z = self.z0

            self.angle += self.speed

            print("{}: x = {:.2f}, y = {:.2f}, z = {:.2f}".format(self.name, x, y, z))
            time.sleep(0.6)

earth = Planet("Earth", 0, 0, 0, 10, 0.1)
mars = Planet("Mars", 20, 20, 20, 5, 0.2)

threading.Thread(target=earth.move).start()
threading.Thread(target=mars.move).start()