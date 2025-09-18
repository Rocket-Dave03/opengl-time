proc = find_program('shader.py')
gen = generator(proc,
  output: '@PLAINNAME@.h',
  arguments: ['@INPUT@', '@OUTPUT@'])

shaders = files(
  'tri.frag',
  'tri.vert',
)

incl += gen.process(shaders)
