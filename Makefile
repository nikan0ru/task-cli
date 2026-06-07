CPP=c++

CPPFLAGS= -Wall -Wextra -g

SRC= main.cpp tasks.cpp utils.cpp

OBJ= $(SRC:.cpp=.o)

NAME=task-cli

all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $(CPPFLAGS)  -o $@ $^

%.o: %.cpp task-cli.h
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re: fclean all
