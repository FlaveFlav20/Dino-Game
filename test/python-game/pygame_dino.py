import pygame
from pygame.locals import *

class Square(pygame.sprite.Sprite):
    def __init__(self):
        super(Square, self).__init__()
        self.surf = pygame.Surface((10, 10))
         
        # Define the color of the surface using RGB color coding.
        self.surf.fill((0, 200, 255))
        self.rect = self.surf.get_rect()

class Player(pygame.sprite.Sprite):
    def __init__(self):
        self.player = Square()
    def move(self, x, y, screen):
        screen.blit(self.player.surf, (x, y))

class Bird(pygame.sprite.Sprite):
    def __init__(self):
        self.bird = Square()
        self.bird.surf.fill((255, 0, 0))
    def move(self, x, y, screen):
        screen.blit(self.bird.surf, (x, y))

class Bush(pygame.sprite.Sprite):
    def __init__(self):
        self.bush = Square()
        self.bush.surf.fill((0, 255, 0))
    def move(self, x, y, screen):
        screen.blit(self.bush.surf, (x, y))

class Manage_enemy():
    def __init__(self):
        self.birds = []
        self.bushes = []
    
    def add_bird(self, x: int, y: int, screen):
        bird = Bird()
        bird.move(x, y, screen)
        self.birds.append(bird)

    def add_bushes(self, x: int, y: int, screen):
        bush = Bush()
        bush.move(x, y, screen)
        self.bushes.append(bush)
    
    def clear(self):
        for e in self.birds:
            e.bird.kill()
        self.birds = []
        for e in self.bushes:
            e.bush.kill()
        self.bushes = []

def display(buffer, row: int, col: int, screen, manage_enemy: Manage_enemy, player: Player):
    screen.fill((0, 0, 0))
    manage_enemy.clear()
    for j in range(col):
        for i in range(row):
            if buffer[j][i] == '$':
                player.move(i * 10, j * 10, screen)
            if buffer[j][i] == 'v':
                manage_enemy.add_bird(i * 10, j * 10, screen)
            if buffer[j][i] == '%':
                manage_enemy.add_bushes(i * 10, j * 10, screen)