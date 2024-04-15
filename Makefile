EXECUTABLE = ./bin/gl
LIB_DIR = ./lib
LIBS = -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32
INCLUDE_DIR = ./include
MAIN_FILE = ./src/main.c
FILES = ./src/glad.c
# RENDER = ./src/engine/render/render.c ./src/engine/render/render_init.c
# FILES += $(RENDER)

build: ./src/main.c
	g++ $(MAIN_FILE) $(FILES) -o $(EXECUTABLE) -I$(INCLUDE_DIR) -L$(LIB_DIR) $(LIBS)
run: build
	$(EXECUTABLE).exe
rebuild:
	python -m compiledb make build run
clean:
	rm $(EXECUTABLE).exe
