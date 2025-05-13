NAME	= graph

GLAD	= lib/glad/

LIB		= -L$(GLAD) -lglad

SDIR	= src/
SRC		= $(SDIR)main.cpp $(SDIR)Triangle.cpp $(SDIR)Shader.cpp $(SDIR)Line.cpp $(SDIR)Graph.cpp
OBJ		= $(SRC:%.cpp=%.o)

INC		= -Iincludes -I$(GLAD)/include
GLFLAG	= -lglfw -lGL -ldl
GPP		= g++ -std=c++17 $(INC)

RM		= rm -rf

all			:	$(NAME)

%.o			:	%.cpp
				$(GPP) -c $< -o $@

$(NAME)		:	$(OBJ)
				make -C $(GLAD)
				$(GPP) $(OBJ) $(LIB) $(GLFLAG) -o $(NAME) 

re			:	fclean all

clean		:
				make -C $(GLAD) clean
				$(RM) $(OBJ)

fclean		:	clean
				make -C $(GLAD) fclean
				$(RM) $(NAME)

.PHONY: all clena fclean re