cmake_minimum_required(VERSION 3.12)
project(module C)

set(CMAKE_C_STANDARD 11)

include_directories(markdown_module/markdown_src)
include_directories(markdown_module/markdown_src/markdown_convert)
include_directories(markdown_module/markdown_src/markdown_parser)
include_directories(markdown_module/markdown_src/markdown_token)

add_executable(module
        markdown_module/markdown_src/markdown_convert/markdown_tohtml.c
        markdown_module/markdown_src/markdown_convert/markdown_tohtml.h
        markdown_module/markdown_src/markdown_parser/markdown_paragraph.c
        markdown_module/markdown_src/markdown_parser/markdown_paragraph.h
        markdown_module/markdown_src/markdown_parser/markdown_sentence.c
        markdown_module/markdown_src/markdown_parser/markdown_sentence.h
        markdown_module/markdown_src/markdown_token/markdown_token.c
        markdown_module/markdown_src/markdown_token/markdown_token.h
        markdown_module/markdown_src/main.c
        markdown_module/markdown_src/markdown_config.h
        markdown_module/test_/test.c markdown_module/markdown_src/markdown_convert/markdown_parser.c markdown_module/markdown_src/markdown_convert/markdown_parser.h)
