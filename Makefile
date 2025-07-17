NAME = webserv

FLAGS = -Wall -Werror -Wextra -std=c++98

OBJ_DIR = .obj/

DIR_MAIN = src/main/
DIR_PARSER = src/Parser/
DIR_SERVER = src/Server/
DIR_UTILS = src/utils/
DIR_SENDER = src/Sender/

SRC_MAIN =		$(DIR_MAIN)main.cpp

SRC_PARSER =	$(DIR_PARSER)Parser.cpp	\
				$(DIR_PARSER)Run.cpp
				
SRC_SERVER = 	$(DIR_SERVER)Server.cpp	\
				$(DIR_SERVER)Router.cpp	\
				$(DIR_SERVER)utils.cpp	\
				$(DIR_SERVER)socket.cpp	\

SRC_UTILS =		$(DIR_UTILS)utils.cpp	\
				$(DIR_UTILS)socket.cpp	\
				$(DIR_UTILS)epoll.cpp	\
				$(DIR_UTILS)Tools.cpp

SRC_SENDER	=	$(DIR_SENDER)Response.cpp	\
				$(DIR_SENDER)Sender.cpp		\
				$(DIR_SENDER)Post.cpp

SRC =	$(SRC_MAIN)		\
		$(SRC_PARSER)	\
		$(SRC_UTILS)	\
		$(SRC_SERVER)	\
		$(SRC_SENDER)

OBJ = $(SRC:%.cpp=$(OBJ_DIR)%.o)

$(OBJ_DIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	c++ $(FLAGS) -c $< -o $@ -I ./lib

all: $(NAME)

$(NAME) : $(OBJ)
	c++ $(FLAGS) $(OBJ) -o $(NAME) -I ./lib

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME) upload/*

re : fclean all

.PHONY : all clean fclean re