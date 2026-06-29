LDFLAGS  = -lm
CFLAGS   = -std=c99 -Wall -Wextra -g -O2 -pedantic -fwrapv -DDBCC_VERSION="\"v1.2.5\""
CXXFLAGS = -std=c++17 -Wall -Wextra -g -O2 -pedantic
RM      := rm
OUTDIR  := out
TEST_C_DIR := ${OUTDIR}/test_c
TEST_ROS_DIR := ${OUTDIR}/test_ros
TEST_SDODPS_DIR := ${OUTDIR}/test_sdodps
SOURCES := ${wildcard *.c}
MDS     := ${wildcard *.md}
HTMLS   := ${MDS:%.md=%.html}
PDFS    := ${MDS:%.md=%.pdf}
MANS    := ${MDS:%.md=%.1}
DBCS    := ${wildcard *.dbc}
OBJECTS := ${SOURCES:%.c=%.o}
LIBOBJS := $(filter-out main.o, $(OBJECTS))
DEPS    := ${SOURCES:%.c=%.d}
XMLS    := ${DBCS:%.dbc=${OUTDIR}/%.xml}
XHTMLS  := ${XMLS:%.xml=%.xhtml}
CODECS  := ${DBCS:%.dbc=${OUTDIR}/%.c}
CFLAGS  += -MMD
TARGET  := dbcc

.PHONY: doc all run clean test test_c test_c_codegen test_c_compile test_c_run test_ros test_sdodps

all: ${TARGET}

%.o: %.c makefile
	${CC} ${CFLAGS} ${INCLUDES} $< -c -o $@

%.1: %.md makefile
	pandoc --standalone --to man -o$@ $<

%.html: %.md makefile
	pandoc -o $@ $<

%.pdf: %.md makefile
	pandoc -o $@ $<

lib${TARGET}.a: ${OBJECTS}
	ar rcs $@ ${OBJECTS}
	ranlib $@

${TARGET}: ${OBJECTS}
	${CC} ${CFLAGS} $^ ${LDFLAGS} -o $@

${OUTDIR}/%.c: %.dbc ${TARGET}
	./${TARGET} ${DBCCFLAGS} -o ${OUTDIR} $<

${OUTDIR}/%.xml: %.dbc ${TARGET}
	./${TARGET} ${DBCCFLAGS} -x -o ${OUTDIR} $<
	xmllint --noout --schema dbcc.xsd $@

${OUTDIR}/%.csv: %.dbc ${TARGET}
	./${TARGET} ${DBCCFLAGS} -C -o ${OUTDIR} $<

${OUTDIR}/%.json: %.dbc ${TARGET}
	./${TARGET} ${DBCCFLAGS} -j -o ${OUTDIR} $<

%.xhtml: %.xml dbcc.xslt
	xsltproc --output $@ dbcc.xslt $<


run: ${XMLS} ${CODECS} ${XHTMLS}

${TEST_C_DIR}/%.c: %.dbc ${TARGET}
	@mkdir -p ${TEST_C_DIR}
	./${TARGET} ${DBCCFLAGS} -f mMso -o ${TEST_C_DIR} $<

TEST_C_FILES=${TEST_C_DIR}/ex1.c \
            ${TEST_C_DIR}/ex2.c \
            ${TEST_C_DIR}/codec_matrix.c \
            ${TEST_C_DIR}/double_signal.c \
            ${TEST_C_DIR}/float_signal.c \
            ${TEST_C_DIR}/enum.c \
            ${TEST_C_DIR}/mul_val.c \
            ${TEST_C_DIR}/single_enum.c \
            ${TEST_C_DIR}/sdodps.c \
            ${TEST_C_DIR}/bitfield_edge.c

TEST_C_FILES_MAIN=${TEST_C_DIR}/ex1.c \
                  ${TEST_C_DIR}/ex2.c \
                  ${TEST_C_DIR}/codec_matrix.c \
                  ${TEST_C_DIR}/double_signal.c \
                  ${TEST_C_DIR}/float_signal.c \
                  ${TEST_C_DIR}/enum.c \
                  ${TEST_C_DIR}/mul_val.c \
                  ${TEST_C_DIR}/sdodps.c \
                  ${TEST_C_DIR}/bitfield_edge.c

TEST_2C_SRCS=tests/test_2c_main.c \
             tests/test_2c_bitfield_edge.c \
             tests/test_2c_codec_matrix.c \
             tests/test_2c_double_signal.c \
             tests/test_2c_enum.c \
             tests/test_2c_ex1.c \
             tests/test_2c_ex2.c \
             tests/test_2c_float_signal.c \
             tests/test_2c_mul_val.c

TEST_2C_SINGLE_ENUM_SRCS=tests/test_2c_single_enum.c \
                         tests/test_2c_single_enum_main.c

TEST_2C_BIN=${TEST_C_DIR}/test_2c
TEST_2C_SINGLE_ENUM_BIN=${TEST_C_DIR}/test_2c_single_enum

TEST_ROS_FILES=${TEST_ROS_DIR}/bitfield_edge/bitfield_edge/package.xml \
               ${TEST_ROS_DIR}/double_signal/double_signal/package.xml \
               ${TEST_ROS_DIR}/enum/enum/package.xml \
               ${TEST_ROS_DIR}/ex1/ex1/package.xml \
               ${TEST_ROS_DIR}/ex2/ex2/package.xml \
               ${TEST_ROS_DIR}/float_signal/float_signal/package.xml \
               ${TEST_ROS_DIR}/mul_val/mul_val/package.xml \
               ${TEST_ROS_DIR}/single_enum/single_enum/package.xml

${TEST_ROS_DIR}/COLCON_IGNORE:
	@mkdir -p ${TEST_ROS_DIR}
	@touch $@

${TEST_ROS_DIR}/double_signal/double_signal/package.xml: double_signal.dbc ${TARGET}
	@mkdir -p ${TEST_ROS_DIR}
	./${TARGET} ${DBCCFLAGS} -r -o ${TEST_ROS_DIR} $<

${TEST_ROS_DIR}/bitfield_edge/bitfield_edge/package.xml: bitfield_edge.dbc ${TARGET}
	@mkdir -p ${TEST_ROS_DIR}
	./${TARGET} ${DBCCFLAGS} -r -W ECU_A -o ${TEST_ROS_DIR} $<

${TEST_ROS_DIR}/enum/enum/package.xml: enum.dbc ${TARGET}
	@mkdir -p ${TEST_ROS_DIR}
	./${TARGET} ${DBCCFLAGS} -r -W Destination -o ${TEST_ROS_DIR} $<

${TEST_ROS_DIR}/single_enum/single_enum/package.xml: single_enum.dbc ${TARGET}
	@mkdir -p ${TEST_ROS_DIR}
	./${TARGET} ${DBCCFLAGS} -r -W Destination -o ${TEST_ROS_DIR} $<

${TEST_ROS_DIR}/ex1/ex1/package.xml: ex1.dbc ${TARGET}
	@mkdir -p ${TEST_ROS_DIR}
	./${TARGET} ${DBCCFLAGS} -r -o ${TEST_ROS_DIR} $<

${TEST_ROS_DIR}/ex2/ex2/package.xml: ex2.dbc ${TARGET}
	@mkdir -p ${TEST_ROS_DIR}
	./${TARGET} ${DBCCFLAGS} -r -W WS200 -o ${TEST_ROS_DIR} $<

${TEST_ROS_DIR}/float_signal/float_signal/package.xml: float_signal.dbc ${TARGET}
	@mkdir -p ${TEST_ROS_DIR}
	./${TARGET} ${DBCCFLAGS} -r -o ${TEST_ROS_DIR} $<

${TEST_ROS_DIR}/mul_val/mul_val/package.xml: mul_val.dbc ${TARGET}
	@mkdir -p ${TEST_ROS_DIR}
	./${TARGET} ${DBCCFLAGS} -r -o ${TEST_ROS_DIR} $<

test_c_codegen: ${TEST_C_FILES}

test_c_compile: test_c_codegen
	${CC} -Wall -Wextra -std=c99 -O0 -pedantic -fwrapv -c ${TEST_C_FILES}

${TEST_2C_BIN}: test_c_codegen ${TEST_C_FILES_MAIN} ${TEST_2C_SRCS}
	${CC} -Wall -Wextra -std=c99 -O0 -pedantic -fwrapv ${TEST_C_FILES_MAIN} ${TEST_2C_SRCS} ${LDFLAGS} -o $@

${TEST_2C_SINGLE_ENUM_BIN}: test_c_codegen ${TEST_C_DIR}/single_enum.c ${TEST_2C_SINGLE_ENUM_SRCS}
	${CC} -Wall -Wextra -std=c99 -O0 -pedantic -fwrapv ${TEST_C_DIR}/single_enum.c ${TEST_2C_SINGLE_ENUM_SRCS} ${LDFLAGS} -o $@

test_c_run: ${TEST_2C_BIN} ${TEST_2C_SINGLE_ENUM_BIN}
	./${TEST_2C_BIN}
	./${TEST_2C_SINGLE_ENUM_BIN}

test_c: test_c_compile test_c_run

test_ros: ${TEST_ROS_FILES} ${TEST_ROS_DIR}/COLCON_IGNORE

test_sdodps: ${TARGET}
	@mkdir -p ${TEST_SDODPS_DIR}
	./${TARGET} ${DBCCFLAGS} -d -o ${TEST_SDODPS_DIR} sdodps.dbc
	${CXX} ${CXXFLAGS} -I${TEST_SDODPS_DIR}/sdodps \
		${TEST_SDODPS_DIR}/sdodps/sdodps_master.cpp \
		${TEST_SDODPS_DIR}/sdodps/sdodps_slave_pcu.cpp \
		${TEST_SDODPS_DIR}/sdodps/sdodps_slave_mcu.cpp \
		tests/test_sdodps_generated.cpp \
		-o ${TEST_SDODPS_DIR}/test_sdodps_generated
	./${TEST_SDODPS_DIR}/test_sdodps_generated

test:
	@set -e; \
	t0=$$(date +%s%3N); \
	t1=$$(date +%s%3N); $(MAKE) --no-print-directory test_c_codegen; t2=$$(date +%s%3N); \
	printf '[time] codegen_c: %d ms\n' "$$((t2-t1))"; \
	t1=$$(date +%s%3N); $(MAKE) --no-print-directory test_ros; t2=$$(date +%s%3N); \
	printf '[time] codegen_ros: %d ms\n' "$$((t2-t1))"; \
	t1=$$(date +%s%3N); $(MAKE) --no-print-directory test_c_compile; t2=$$(date +%s%3N); \
	printf '[time] compile_generated_c: %d ms\n' "$$((t2-t1))"; \
	t1=$$(date +%s%3N); $(MAKE) --no-print-directory test_c_run; t2=$$(date +%s%3N); \
	printf '[time] run_generated_c: %d ms\n' "$$((t2-t1))"; \
	t1=$$(date +%s%3N); $(MAKE) --no-print-directory test_sdodps; t2=$$(date +%s%3N); \
	printf '[time] test_sdodps: %d ms\n' "$$((t2-t1))"; \
	tf=$$(date +%s%3N); \
	printf '[time] total_test: %d ms\n' "$$((tf-t0))"

doc: ${HTMLS} ${MANS} ${PDFS}

-include ${DEPS}

clean:
	${RM} -f *.o *.d *.out ${TARGET} *.htm vgcore.* core
	${RM} -rf ${TEST_C_DIR} ${TEST_ROS_DIR} ${TEST_SDODPS_DIR}
