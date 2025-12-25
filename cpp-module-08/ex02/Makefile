NAME = Mutantstack

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror 

SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
DEPS = Mutantstack.hpp

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean al