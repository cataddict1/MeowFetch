build:
	g++ src/main.cpp -o meowfetch

install:
	cp meowfetch /bin/

all:
	g++ src/main.cpp -o meowfetch
	cp meowfetch /bin/

clean:
	rm -f meowfetch