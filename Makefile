NAME = webserv

FLAGS = -Wall -Werror -Wextra -std=c++98

DIR_PARSER = src/Parser/
DIR_SERVER = src/Server/
DIR_EPOLL = src/epoll/
DIR_UTILS = src/utils/

SRC_PARSER =	$(DIR_PARSER)Parser.cpp
				
SRC_SERVER = 	$(DIR_SERVER)Server.cpp \
				$(DIR_SERVER)Router.cpp \
				$(DIR_SERVER)utils.cpp  \
				$(DIR_SERVER)socket.cpp 

SRC_UTILS =		$(DIR_UTILS)utils.cpp	\
				$(DIR_UTILS)socket.cpp

SRC_EPOLL = $(DIR_EPOLL)epoll.cpp

SRC = 	main.cpp		\
		$(SRC_PARSER)	\
		$(SRC_EPOLL)	\
		$(SRC_UTILS)	\
		$(SRC_SERVER)

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