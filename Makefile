SRC_FILES	:= $(wildcard ./src/*.cpp)
INCLUDE_DIR	:= $(wildcard ./include)

FLAGS		:= -I$(INCLUDE_DIR) -g -std=c++17 -fsanitize=address

TARGET		:= funcgen

default:
	g++ $(SRC_FILES) $(FLAGS) -o $(TARGET)