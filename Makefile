CC      :=  g++ -g 
SRC     :=  $(wildcard src/*.cpp) 
BDIR    :=  obj
EDIR    :=  Release
OBJ     :=  $(SRC:src/%.c=$(BDIR)/%.o)
CFLAGS  :=  -W -Wall -Werror
NAME    :=  $(EDIR)/MyCrd

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) | $(EDIR)
	$(CC) $^ -o $@

$(BDIR)/%.o: src/%.cpp | $(BDIR) | $(EDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(BDIR):
	@mkdir $@ 

$(EDIR):
	@mkdir $@

clean:
	$(RM) -r $(BDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
