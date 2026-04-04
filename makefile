LIBS= -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: game

main.o: main.cpp
		g++ -c "main.cpp" -o main.o 

# enemy.o: enemy.cpp
# 		g++ -c "enemy.cpp" -o enemy.o

# projectile.o: projectile.cpp
# 		g++ -c "projectile.cpp" - o projectile.o

# summon.o: summon.cpp
# 		g++ -c "summon.cpp" -o summon.o


#enemy.o projectile.o summon.o add these ass needed
game: main.o #enemy.o projectile.o summon.o
		@echo "** Building the game"
		g++ -o game main.o $(LIBS)

run: game.o
		./game
