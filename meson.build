project(
    'chess-bot',
    'cpp',
    default_options: [
        'cpp_std=c++17',
        'warning_level=3',
        'buildtype=release',
        'b_ndebug=true',
    ],
)

# Compiler and Linker Flags
add_global_link_arguments('-flto', language: 'cpp')

# Include directory
inc = include_directories('inc')

# Sources
sources = [
  './main.cpp',
  'src/serial_port.cpp',
  'src/chess_bot.cpp'
]

executable(
    'chess_bot',
    sources: sources,
    include_directories: inc,
    install: true,
)
