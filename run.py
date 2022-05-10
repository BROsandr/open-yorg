import os
import shutil

# prefix ='C:/Code/c++/SFML-2.5.1-windows-vc15-64-bit/SFML-2.5.1/bin/'; 
# libs = ['sfml-graphics-d-2.dll', 'sfml-system-d-2.dll', 'sfml-window-d-2.dll']
# libs = [prefix + el for el in libs]
ret = os.system('scons -j 8')
if ret != 0:
    exit()
# if not os.path.exists(os.path.abspath('./build/sfml-graphics-d-2.dll')):
#     for file in libs: shutil.copy(file, './build/')
if not os.path.exists(os.path.abspath('./build/resources')):
    shutil.copytree('./resources/', './build/resources/')
os.system('build\open-yorg.exe')