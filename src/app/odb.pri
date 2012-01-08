
odb.name = odb ${QMAKE_FILE_IN}
odb.input = ODBSOURCES
odb.output = ${QMAKE_FILE_BASE}-odb.cxx
odb.commands = odb -I $$QMAKE_INCDIR_QT -d sqlite --profile qt --generate-query --generate-schema ${QMAKE_FILE_IN}
odb.variable_out = SOURCES
odb.CONFIG += target_predeps

QMAKE_EXTRA_COMPILERS += odb
