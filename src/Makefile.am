AM_CPPFLAGS =  -I../phyml -I../seqgen -I../levmar -I../librna

bin_PROGRAMS = RNAcode

RNAcode_SOURCES = \
    RNAcode.c \
    RNAcode.h \
    rnaz_utils.h \
    rnaz_utils.c \
    utils.h \
    utils.c \
    cmdline.c \
    cmdline.h \
    treeSimulate.c \
    treeSimulate.h \
    treeML.h \
    treeML.c \
    code.c \
    postscript.c \
    code.h \
    extreme_fit.c \
    extreme_fit.h \
    postscript.h \
    score.c \
    score.h \
    misc.c \
    misc.h

LDADD = \
    -L../levmar -llevmar \
    -L../phyml -lPHYML \
    -L../seqgen -lseqgen \
    -L../librna -lRNA \
    -lm
