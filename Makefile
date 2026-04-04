LIBS= -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: game

main.o: src/main.cpp
		g++ -c "src/main.cpp" -o main.o 


Player.o: src/Player.cpp
		g++ -c "src/Player.cpp" -o Player.o

# enemy.o: enemy.cpp
# 		g++ -c "enemy.cpp" -o enemy.o

# projectile.o: projectile.cpp
# 		g++ -c "projectile.cpp" - o projectile.o

# summon.o: summon.cpp
# 		g++ -c "summon.cpp" -o summon.o


#enemy.o projectile.o summon.o add these as needed
game: main.o Player.o #enemy.o projectile.o summon.o
		@echo "** Building the game"
		g++ -o game main.o Player.o $(LIBS)

run: game
		./game
