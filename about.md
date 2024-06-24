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

Note:
    You NEED to have Python installed, in order to use a module, you can just import it normally like in the default script.