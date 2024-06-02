#Naïve and simple makefile

help:
	@echo "Help Menu"
	@echo "make help   -- Print this menu."
	@echo "make alfa   -- Compile and execute process alfa."
	@echo "make beta   -- Compile and execute process beta."
	@echo "make inject -- Compile and execute process inject."

alfa:
	gcc ecc.c packet.c error_gen.c 1_proc_alfa.c -o main_alfa.o
	./main_alfa.o

beta:
	gcc ecc.c packet.c error_gen.c 2_proc_beta.c -o main_beta.o
	./main_beta.o

inject:
	gcc ecc.c packet.c error_gen.c 3_inject_error.c -o main_inject.o
	./main_inject.o

clean:
	rm -rf inject_log_file chn* alfa_log_file output_file