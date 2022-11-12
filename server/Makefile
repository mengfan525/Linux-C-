SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
 
ALL: server


$(OBJ): $(SRC)
        gcc -c $< -o $@

ALL: $(OBJ)
        gcc $< -o $@
 
 
clean:
        rm -rf $(OBJ) ALL
