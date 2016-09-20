NAME      :=  MyCrd
BDIR      :=  Release
ODIR      :=  obj
SRC       :=  $(wildcard src/*.cpp)
OBJ       :=  $(SRC:src/%.cpp=$(ODIR)/%.o)
CXXFLAGS  :=  -W -Wall -Werror

.PHONY: all debug clean fclean re

all: $(NAME)

debug: CXXFLAGS += -DDEBUG -g
debug: all

$(NAME): $(OBJ) | $(BDIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BDIR)/$@

$(ODIR)/%.o: src/%.cpp | $(ODIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(ODIR) $(BDIR):
	@mkdir -p $@

clean:
	$(RM) -r $(ODIR)

fclean: clean
	$(RM) -r $(BDIR)

re: fclean all