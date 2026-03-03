COMP=gcc
FLAGS=-fno-stack-protector -z execstack -mpreferred-stack-boundary=2 -m32 -Wno-incompatible-pointer-types

all : vuln safe

vuln:
	$(COMP) vuln.c -o vuln  $(FLAGS)

safe:
	$(COMP) -o safer safer.c $(FLAGS)
run:
	./vuln

clean:
	rm vuln safer *.txt