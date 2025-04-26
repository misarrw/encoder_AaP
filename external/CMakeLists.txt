include(FetchContent)

FetchContent_declare(
    doctest 
    GIT_REPOSITORY https://github.com/doctest/doctest.git)
FetchContent_GetProperties(doctest)
FetchContent_MakeAvailable(doctest)
