import os
import shutil

prefix ='C:/Code/c++/SFML-2.5.1-windows-vc15-64-bit/SFML-2.5.1/bin/'; 
libs = ['sfml-graphics-d-2.dll', 'sfml-system-d-2.dll', 'sfml-window-d-2.dll']
libs = [prefix + el for el in libs]
compile_commands = os.path.abspath('./build/compile_commands.json')
compile_commands_top = os.path.abspath('./compile_commands.json')
ret = os.system('scons')
if ret == 1:
    exit()
if os.path.exists(compile_commands_top):
    os.remove(compile_commands_top)
shutil.copy(compile_commands, './')
if not os.path.exists(os.path.abspath('./build/sfml-graphics-d-2.dll')):
    for file in libs: shutil.copy(file, './build/')
if not os.path.exists(os.path.abspath('./build/resources')):
    print(2)
    shutil.copytree('./resources/', './build/resources/')
os.system('build\open-yorg.exe')