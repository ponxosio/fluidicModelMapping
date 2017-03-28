COPY %1\FluidicModelMapping.dll X:\fluidicModelMapping\dll_%2\bin\FluidicModelMapping.dll
COPY %1\FluidicModelMapping.lib X:\fluidicModelMapping\dll_%2\bin\FluidicModelMapping.lib

DEL /S X:\fluidicModelMapping\dll_%2\include\*.h
XCOPY /S /Y X:\fluidicModelMapping\fluidicModelMapping\*.h X:\fluidicModelMapping\dll_%2\include