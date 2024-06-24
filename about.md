# PyDeath

- This mod allows you to run Python code whenever you die (in game)

# How to add a script?
- If you don't have a script added. the default code that will run is:
```python
import random
list = ["You are dead!", "You have DIED...", "the PlayerObject::playerDestroyed function has been called"]

value = random.choice(list)
print(value) # uses stdout.
```
To add a script, follow the steps:
1. Create a script with your code in it.
2. Open geometry dash and go to the mods menu
3. Go to PyDeath's settings menu, you will see a select file button, which then will prompt you to select the file.
4. Select the file you created.
5. You're done!!!

# Using python modules
- PyDeath requires python to be installed and it uses it as the interpreter.
- Which means that you can just use `pip` to install modules and import them like normal.

# PyDeath-specific enhancements:
- PyDeath introduces special placeholders that get replaced with in-game values:
  - `{PLAYER_X}`: Player's X Position
  - `{PLAYER_Y}`: Player's Y positon

## Example:
```python
print("Died at X {PLAYER_X} and Y {PLAYER_Y}")
# saying that the X position of the player is 50
# and the Y position of the player is 0.
# PyDeath will automatically change the code above to:
print("Died at X 50 and Y 0")
