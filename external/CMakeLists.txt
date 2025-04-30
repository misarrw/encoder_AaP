include(FetchContent)

FetchContent_declare(
    doctest 
    GIT_REPOSITORY https://github.com/doctest/doctest.git)
FetchContent_GetProperties(doctest)
FetchContent_MakeAvailable(doctest)


# Загружаем Armadillo через FetchContent
FetchContent_Declare(
    armadillo
    GIT_REPOSITORY https://gitlab.com/conradsnicta/armadillo-code.git
    GIT_TAG 12.6.x  # Укажите нужную версию (например, 12.6.1)
)

FetchContent_GetProperties(armadillo)
FetchContent_MakeAvailable(armadillo)