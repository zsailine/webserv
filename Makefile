NAME = webserv
COMPILER = c++
FLAGS = -Wall -Werror -Wextra -std=c++98

SRC =	main.cpp 	\
		Socket.cpp

OBJ =	$(SRC:.cpp=.o)

%.o : %.cpp
	$(COMPILER) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	$(COMPILER) $(FLAGS) $(OBJ) -o $(NAME)

all : $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : clean all

.PHONY : all clean fclean re
