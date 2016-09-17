CXX       :=  g++ -g
SRC       :=  $(wildcard src/*.cpp)
BDIR      :=  obj
EDIR      :=  Release
OBJ       :=  $(SRC:src/%.c=$(BDIR)/%.o)
CXXFLAGS  :=  -W -Wall -Werror
NAME      :=  $(EDIR)/MyCrd

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) | $(BDIR) $(EDIR)
	$(CXX) $^ -o $@

$(BDIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BDIR) $(EDIR):
	@mkdir -p $@

clean:
	$(RM) -r $(BDIR)

fclean: clean
	$(RM) -r $(EDIR)

re: fclean all