# Server

# Structure

- **Makefile**: to build project/lib
- **main.c**: for testing
- **src**: project source
    - **src/Includes**: All headers
        - **src/Includes/Display.h**: To send screen/result to a FILE*
        - **src/Includes/Entities.h**: There is just an enum with all game entities
        - **src/Includes/Server.h**: All server comonent
        - **src/Includes/Utils.h**: It deals with all game comonents
    - **src/*.c**: save behavious as **Includes/*.h**