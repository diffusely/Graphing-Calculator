NAME	= graph

GLAD	= lib/glad/

LIB		= -L$(GLAD) -lglad

SDIR	= src/
ODIR	= obj/

SRC		= $(SDIR)main.cpp $(SDIR)Triangle.cpp \
		  $(SDIR)Shader.cpp $(SDIR)Line.cpp \
		  $(SDIR)Graph.cpp $(SDIR)ExpTree.cpp \
		  $(SDIR)Camera.cpp $(SDIR)CameraController.cpp \
		  $(SDIR)Grid.cpp

OBJ		= $(patsubst $(SDIR)%.cpp,$(ODIR)%.o,$(SRC))

INC		= -Iincludes -I$(GLAD)/include
GLFLAG	= -lglfw -lGL -ldl
GPP		= g++ -std=c++17 $(INC)

RM		= rm -rf

all			:	$(NAME)

$(ODIR)		:
				mkdir -p $(ODIR)


$(ODIR)%.o	: 	$(SDIR)%.cpp | $(ODIR)
				$(GPP) -c $< -o $@

$(NAME)		:	$(OBJ)
				make -C $(GLAD)
				$(GPP) $(OBJ) $(LIB) $(GLFLAG) -o $(NAME) 

re			:	fclean all

clean		:
				make -C $(GLAD) clean
				$(RM) $(OBJ) $(ODIR)

fclean		:	clean
				make -C $(GLAD) fclean
				$(RM) $(NAME)

.PHONY: all clena fclean re