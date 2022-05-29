# macros
gxx = g++ -std=c++17
flags = -Wall -Wextra -pedantic -pedantic-errors
# sfml = -lsfml-window -lsfml-graphics -lsfml-system

# files
exec = ConnectFourText.exe
# src = sourcefiles
obj = obj

# pattern
$(obj)/%.o : %.cpp
	mkdir -p $(obj)
	$(gxx) $(flags) $^ -c -o $@ 

$(exec) : $(obj)/mainText.o $(obj)/textApp.o $(obj)/agent.o
	$(gxx) $(flags) $^ -o $@ 

# $(obj)/mainText.o : $(obj)/textApp.o

# $(obj)/textApp.o : $(obj)/agent.o

test: $(exec)
	./$(exec)

clean:
	rm -rf $(obj)
	rm $(exec)
