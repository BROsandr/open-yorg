system_include = ['C:/Code/c++/SFML-2.5.1-windows-vc15-64-bit/SFML-2.5.1/include', 'C:/programs/lemon-debug/include']
include = ['C:/Code/c++/open-yorg/include/']
libpath=[r'C:\programs\lemon-debug\lib/', r'C:\Code\c++\SFML-2.5.1-windows-vc15-64-bit\SFML-2.5.1\lib'] 
libs = ['sfml-graphics-d', 'sfml-system-d', 'sfml-window-d', 'lemon']
cppflags_ms = ['/std:c++17', '/MDd', '/EHs', '/Zi', '/Ob0', '/Od'] + [f'/external:I{system_include[0]}', f'/external:I{system_include[1]}']
cppflags_gnu = ['-Wreturn-type']
cppflags_gnu_error_handling = ['-Wall' ,'-Wextra' ,'-pedantic' ,'-std=c++11' ,'-O2' ,'-Wshadow' ,'-Wformat=2' ,'-Wfloat-equal' ,'-Wconversion' ,'-Wlogical-op' ,'-Wshift-overflow=2' ,'-Wduplicated-cond' ,'-Wcast-qual' ,'-Wcast-align' ,'-D_GLIBCXX_DEBUG' ,'-D_GLIBCXX_DEBUG_PEDANTIC' ,'-D_FORTIFY_SOURCE=2' ,'-fsanitize=address' ,'-fsanitize=undefined' ,'-fno-sanitize-recover' ,'-fstack-protector']
cppflags = cppflags_ms + cppflags_gnu + cppflags_gnu_error_handling
# cppflags = ['/std:c++17', '/MDd', '/EHs', '/Zi', '/Ob0', '/Od', '/FS']
linkflags =[  '/DEBUG:FULL']
env = Environment(CPPPATH=include, LIBPATH = libpath, LIBS=libs, LINK = 'lld-link', CXX = 'clang-cl', CXXCOMSTR = "Compiling $SOURCE", LINKCOMSTR = "Linking $TARGET", CCFLAGS = cppflags)
# env = Environment(CPPPATH=include, LIBPATH = libpath, LIBS=libs, LINK = 'lld-link', CXX = 'clang-cl')
# env = Environment(CPPPATH=system_include + include, LIBPATH = libpath, LIBS=libs, CXXCOMSTR = "Compiling $SOURCE", LINKCOMSTR = "Linking $TARGET" )
env.Decider('MD5-timestamp')
env.Tool('compilation_db')
env.CompilationDatabase()
sources = Glob('*/*.cpp') + Glob('*.cpp')
env.Program('open-yorg', sources, LINKFLAGS = linkflags, CPPFLAGS = cppflags)