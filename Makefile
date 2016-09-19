NAME      :=  MyCrd
EDIR      :=  Release
ODIR      :=  obj
SRC       :=  $(wildcard src/*.cpp)
OBJ       :=  $(SRC:src/%.cpp=$(ODIR)/%.o)
CXXFLAGS  :=  -W -Wall -Werror

.PHONY: all debug clean fclean re

all: $(NAME)

debug: CXXFLAGS += -DDEBUG -g
debug: all

$(NAME): $(OBJ) | $(EDIR)
	$(CXX) $(CXXFLAGS) $^ -o $(EDIR)/$@

$(ODIR)/%.o: src/%.cpp | $(ODIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(ODIR) $(EDIR):
	@mkdir -p $@

clean:
	$(RM) -r $(ODIR)

fclean: clean
	$(RM) -r $(EDIR)

re: fclean all