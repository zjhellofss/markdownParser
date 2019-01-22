cmake_minimum_required(VERSION 3.12)
project(parser C)

set(CMAKE_C_STANDARD 11)

include_directories(markdown_src)
include_directories(markdown_src/markdown_convert)
include_directories(markdown_src/markdown_parser)
include_directories(markdown_src/markdown_token)
link_directories(/usr/local/lib)
LINK_LIBRARIES(curl ssl crypto)
add_executable(parser
        markdown_src/markdown_convert/markdown_tohtml.c
        markdown_src/markdown_convert/markdown_tohtml.h
        markdown_src/markdown_parser/markdown_paragraph.c
        markdown_src/markdown_parser/markdown_paragraph.h
        markdown_src/markdown_parser/markdown_parser.c
        markdown_src/markdown_parser/markdown_parser.h
        markdown_src/markdown_parser/markdown_sentence.c
        markdown_src/markdown_parser/markdown_sentence.h
        markdown_src/markdown_token/markdown_token.c
        markdown_src/markdown_token/markdown_token.h
        markdown_src/main.c
        markdown_src/markdown_translate/cJSON.c
        markdown_src/markdown_translate/cJSON.h
        markdown_src/markdown_config.h markdown_src/markdown_token/markdown_headnodes.c markdown_src/markdown_token/markdown_headnodes.h markdown_src/markdown_convert/markdown_html2pdf.c markdown_src/markdown_convert/markdown_html2pdf.h markdown_src/markdown_convert/markdown_time.c markdown_src/markdown_convert/markdown_time.h markdown_src/markdown_translate/markdown_translate.c markdown_src/markdown_translate/markdown_translate.h)

install(TARGETS parser RUNTIME DESTINATION /usr/local/bin)
