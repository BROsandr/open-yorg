system_include = [r'C:\Code\c++\SFML-2.5.1-windows-vc15-64-bit\SFML-2.5.1\include', r'C:\programs\lemon-debug\include']
include = ['C:/Code/c++/open-yorg/include/']
libpath=[r'C:\programs\lemon-debug\lib/', r'C:\Code\c++\SFML-2.5.1-windows-vc15-64-bit\SFML-2.5.1\lib'] 
libs = ['sfml-graphics-d', 'sfml-system-d', 'sfml-window-d', 'lemon']
cppflags_ms = ['/std:c++17', '/MDd', '/EHs', '/Zi', '/Ob0', '/Od']
cppflags_gnu = ['-Wno-everything']
cppflags = cppflags_ms + cppflags_gnu
# cppflags = ['/std:c++17', '/MDd', '/EHs', '/Zi', '/Ob0', '/Od', '/FS']
linkflags =[  '/DEBUG:FULL']
env = Environment(CPPPATH=system_include + include, LIBPATH = libpath, LIBS=libs, LINK = 'lld-link', CXX = 'clang-cl', CXXCOMSTR = "Compiling $SOURCE", LINKCOMSTR = "Linking $TARGET" )
# env = Environment(CPPPATH=system_include + include, LIBPATH = libpath, LIBS=libs, CXXCOMSTR = "Compiling $SOURCE", LINKCOMSTR = "Linking $TARGET" )
env.Decider('MD5-timestamp')
env.Tool('compilation_db')
env.CompilationDatabase()
sources = Glob('*/*.cpp') + Glob('*.cpp')
env.Program('open-yorg', sources, LINKFLAGS = linkflags, CPPFLAGS = cppflags)