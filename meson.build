project('opengl-time', 'c')
cc = meson.get_compiler('c')

incl = files()
subdir('src')

deps = []
deps += cc.find_library('m', required : true)
deps += dependency('glfw3')
deps += dependency('opengl')
deps += dependency('glew')


add_global_arguments('-DWall', language : 'c')
add_global_arguments('-DWerror', language : 'c')


executable('opengl-time', sources + incl, dependencies: deps)
