NAME = webserv

FLAGS = -Wall -Werror -Wextra -std=c++98

SRC = 	main.cpp \
		epoll.cpp \
		ServerSocket.cpp

OBJ = $(SRC:.cpp=.o)

%.o: %.cpp
	c++ $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJ)
		c++ $(FLAGS) $(OBJ) -o $(NAME)

clean :
		$(RM) $(OBJ) $(OBJ)

fclean :
		$(RM) $(OBJ) $(OBJ) $(NAME)

re : fclean all

.PHONY : all clean fclean re