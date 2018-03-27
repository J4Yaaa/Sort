a.out:StackQueue.c sort.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -f a.out

