include giet.env

compile_reset:
	${AS} -g -mips32 -o reset.o reset.s

compile_giet:
	${AS} -g -mips32 -o giet.o ${GIET_SYS_PATH}/giet.s
	${CC} -Wall -mno-gpopt -ffreestanding -mips32 -I${GIET_SYS_PATH} -I. -c -o drivers.o ${GIET_SYS_PATH}/drivers.c
	${CC} -Wall -mno-gpopt -ffreestanding -mips32 -I${GIET_SYS_PATH} -I. -c -o common.o ${GIET_SYS_PATH}/common.c
	${CC} -Wall -mno-gpopt -ffreestanding -mips32 -I${GIET_SYS_PATH} -I. -c -o ctx_handler.o ${GIET_SYS_PATH}/ctx_handler.c
	${CC} -Wall -mno-gpopt -ffreestanding -mips32 -I${GIET_SYS_PATH} -I. -c -o irq_handler.o ${GIET_SYS_PATH}/irq_handler.c
	${CC} -Wall -mno-gpopt -ffreestanding -mips32 -I${GIET_SYS_PATH} -I. -c -o sys_handler.o ${GIET_SYS_PATH}/sys_handler.c
	${CC} -Wall -mno-gpopt -ffreestanding -mips32 -I${GIET_SYS_PATH} -I. -c -o exc_handler.o ${GIET_SYS_PATH}/exc_handler.c

link_sys: reset.o giet.o
	${LD} -o sys.bin -T sys.ld reset.o giet.o drivers.o common.o ctx_handler.o irq_handler.o sys_handler.o exc_handler.o
	${DU} -D sys.bin > sys.bin.txt

compile_app:
	${CC} -Wall -mno-gpopt -ffreestanding -mips32 -I${GIET_APP_PATH} -I. -c -o stdio.o ${GIET_APP_PATH}/stdio.c
	${CC} -Wall -mno-gpopt -ffreestanding -mips32 -I${GIET_APP_PATH} -I. -c -o main.o main.c

link_app: stdio.o main.o
	${LD} -o app.bin -T app.ld stdio.o main.o
	${DU} -D app.bin > app.bin.txt

all: compile_reset compile_giet link_sys compile_app link_app
