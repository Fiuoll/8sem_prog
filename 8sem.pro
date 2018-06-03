TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    prints.c \
    norms.c \
    setka.c \
    functions.c \
    laspack/eigenval.c \
    laspack/errhandl.c \
    laspack/factor.c \
    laspack/itersolv.c \
    laspack/matrix.c \
    laspack/mlsolv.c \
    laspack/operats.c \
    laspack/precond.c \
    laspack/qmatrix.c \
    laspack/rtc.c \
    laspack/vector.c \
    shema.c \
    solver.c \
    gnuplot.c

HEADERS += \
    head.h \
    structs.h \
    laspack/copyrght.h \
    laspack/eigenval.h \
    laspack/elcmp.h \
    laspack/errhandl.h \
    laspack/factor.h \
    laspack/itersolv.h \
    laspack/lastypes.h \
    laspack/matrix.h \
    laspack/mlsolv.h \
    laspack/operats.h \
    laspack/precond.h \
    laspack/qmatrix.h \
    laspack/rtc.h \
    laspack/vector.h \
    laspack/version.h
