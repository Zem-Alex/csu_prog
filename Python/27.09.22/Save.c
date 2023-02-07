
import arcade
from pyglet.math import Vec2

SPRITE_SCALING = 0.5

SCREEN_WIDTH = 1200
SCREEN_HEIGHT = 800
SCREEN_TITLE = "Sprite with Moving Platforms Example"
SPRITE_PIXEL_SIZE = 128
GRID_PIXEL_SIZE = (SPRITE_PIXEL_SIZE * SPRITE_SCALING)

# How many pixels to keep as a minimum margin between the character
# and the edge of the screen.
VIEWPORT_MARGIN = SPRITE_PIXEL_SIZE * SPRITE_SCALING
RIGHT_MARGIN = 4 * SPRITE_PIXEL_SIZE * SPRITE_SCALING

# Physics
MOVEMENT_SPEED = 9 * SPRITE_SCALING
JUMP_SPEED = 26 * SPRITE_SCALING
GRAVITY = 1.4 * SPRITE_SCALING



class MyGame(arcade.Window):

    def __init__(self, width, height, title):

        super().__init__(width, height, title)
        self.background = arcade.load_texture("background.png")

        self.static_wall_list = None
        self.moving_wall_list = None
        self.liquid_list = None

        self.player_list = None
        # Set up the player
        self.player_sprite = None
        self.physics_engine = None
        self.game_over = False

        self.left_down = False
        self.right_down = False

    def setup(self):

        # Sprite lists
        self.static_wall_list = arcade.SpriteList()
        self.moving_wall_list = arcade.SpriteList()
        self.liquid_lava_list = arcade.SpriteList()
        self.liquid_water_list = arcade.SpriteList()
        self.player_list = arcade.SpriteList()

        # Set up the player
        self.player_sprite = arcade.Sprite("girl.png", SPRITE_SCALING)
        self.player_sprite.center_x = 2 * GRID_PIXEL_SIZE
        self.player_sprite.center_y = 3 * GRID_PIXEL_SIZE
        self.player_list.append(self.player_sprite)

        # Create floor
        for i in range(40):
            if i != 14 and i != 15 and i != 16 and i != 17 and i != 19 and i != 20 and i != 21 and i != 22:
                wall = arcade.Sprite("brick.png", SPRITE_SCALING)
                wall.bottom = 50
                wall.center_x = i * GRID_PIXEL_SIZE / 2
                self.static_wall_list.append(wall)
            elif i == 14 or i == 19:
                leftbrick = arcade.Sprite("leftbrick.png", SPRITE_SCALING)
                leftbrick.bottom = 50
                leftbrick.center_x = i * GRID_PIXEL_SIZE / 2
                self.static_wall_list.append(leftbrick)
                if i == 14:
                    lava = arcade.Sprite("lava.png", SPRITE_SCALING)
                    lava.bottom = 50
                    lava.center_x = i * GRID_PIXEL_SIZE / 2 + 45
                    self.liquid_lava_list.append(lava)
                else:
                    water = arcade.Sprite("water.png", SPRITE_SCALING)
                    water.bottom = 50
                    water.center_x = i * GRID_PIXEL_SIZE / 2 + 45
                    self.liquid_water_list.append(water)
            elif i == 17 or i == 22:
                rightbrick = arcade.Sprite("rightbrick.png", SPRITE_SCALING)
                rightbrick.bottom = 50
                rightbrick.center_x = i * GRID_PIXEL_SIZE / 2
                self.static_wall_list.append(rightbrick)
            else:
                bottombrick = arcade.Sprite("bottombrick.png", SPRITE_SCALING)
                bottombrick.bottom = 50
                bottombrick.center_x = i * GRID_PIXEL_SIZE / 2
                self.static_wall_list.append(bottombrick)

        # Create platform side to side
        doorgirl = arcade.Sprite("doorgirl.png", SPRITE_SCALING)
        doorgirl.center_y = 3 * GRID_PIXEL_SIZE
        doorgirl.center_x = 3 * GRID_PIXEL_SIZE
        doorgirl.boundary_left = 2 * GRID_PIXEL_SIZE
        doorgirl.boundary_right = 5 * GRID_PIXEL_SIZE
        doorgirl.change_x = 2 * SPRITE_SCALING
        self.moving_wall_list.append(doorgirl)

        '''leftbrick = arcade.Sprite("leftbrick.png", SPRITE_SCALING)
        leftbrick.bottom = 50
        leftbrick.center_x = 608
        self.static_wall_list.append(leftbrick)

        rightbrick = arcade.Sprite("rightbrick.png", SPRITE_SCALING)
        rightbrick.bottom = 50
        rightbrick.center_x = 706
        self.static_wall_list.append(rightbrick)

        bottombrick = arcade.Sprite("bottombrick.png", SPRITE_SCALING)
        bottombrick.bottom = 50
        bottombrick.center_x = 660
        self.static_wall_list.append(bottombrick)

        lava = arcade.Sprite("lava.png", SPRITE_SCALING)
        lava.bottom = 49
        lava.center_x = 654
        self.liquid_lava_list.append(lava)'''



        # Create our physics engine
        self.physics_engine = \
            arcade.PhysicsEnginePlatformer(self.player_sprite,
                                           [self.static_wall_list, self.moving_wall_list],
                                           gravity_constant=GRAVITY)

        # Set the background color
        arcade.set_background_color(arcade.color.AMAZON)

        self.game_over = False

    def on_draw(self):
        """
        Render the screen.
        """

        # This command has to happen before we start drawing
        self.clear()


        # Draw the sprites.
        arcade.draw_texture_rectangle(600, 400, 1200, 800, self.background)
        self.static_wall_list.draw()
        self.moving_wall_list.draw()
        self.player_list.draw()
        self.liquid_lava_list.draw()
        self.liquid_water_list.draw()

        # Put the text on the screen.
        distance = self.player_sprite.right
        output = f"Distance: {distance}"
        arcade.draw_text(output, 10, 20, arcade.color.WHITE, 14)

    def set_x_speed(self):
        if self.left_down and not self.right_down:
            self.player_sprite.change_x = -MOVEMENT_SPEED
        elif self.right_down and not self.left_down:
            self.player_sprite.change_x = MOVEMENT_SPEED
        else:
            self.player_sprite.change_x = 0

    def on_key_press(self, key, modifiers):
        """ Called whenever the mouse moves. """
        if key == arcade.key.UP:
            if self.physics_engine.can_jump():
                self.player_sprite.change_y = JUMP_SPEED
        elif key == arcade.key.LEFT:
            self.left_down = True
            self.set_x_speed()
        elif key == arcade.key.RIGHT:
            self.right_down = True
            self.set_x_speed()

    def on_key_release(self, key, modifiers):
        """ Called when the user presses a mouse button. """
        if key == arcade.key.LEFT:
            self.left_down = False
            self.set_x_speed()
        elif key == arcade.key.RIGHT:
            self.right_down = False
            self.set_x_speed()

    def on_update(self, delta_time):
        """ Movement and game logic """

        # Call update on all sprites
        lavas_hit_list = arcade.check_for_collision_with_list(self.player_sprite, self.liquid_lava_list)
        for lava in lavas_hit_list:
            self.player_sprite.kill()
        self.physics_engine.update()

def main():
    """ Main function """
    window = MyGame(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)
    window.setup()
    arcade.run()


if __name__ == "__main__":
    main()