# Get the list of input .txt files
file(TO_CMAKE_PATH "${PAYLOAD_FILES}" PAYLOAD_LIST)
separate_arguments(PAYLOAD_LIST)

file(WRITE "${OUT_FILE}" "#include <stddef.h>\n\n")

set(index 0)
foreach(file_path IN LISTS PAYLOAD_LIST)
    file(READ "${file_path}" CONTENTS)
    string(REPLACE "\\" "\\\\" CONTENTS "${CONTENTS}")
    string(REPLACE "\"" "\\\"" CONTENTS "${CONTENTS}")
    string(REPLACE "\n" "\\n\"\n\"" CONTENTS "${CONTENTS}")
    get_filename_component(NAME "${file_path}" NAME_WE)
    file(APPEND "${OUT_FILE}" "static const char payload_${index}[] = \"${CONTENTS}\";\n")
    math(EXPR index "${index} + 1")
endforeach()

# Declare the array
file(APPEND "${OUT_FILE}" "\nconst char* payloads[] = {\n")
math(EXPR count "${index} - 1")
foreach(i RANGE ${count})
    file(APPEND "${OUT_FILE}" "    payload_${i},\n")
endforeach()
file(APPEND "${OUT_FILE}" "};\n")
file(APPEND "${OUT_FILE}" "const int payload_count = sizeof(payloads) / sizeof(payloads[0]);\n")
