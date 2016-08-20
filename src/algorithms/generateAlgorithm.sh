#!/bin/sh

if [ "$#" -ne 1 ]; then
    echo "ERROR: Invalid parameter !"
    echo "Usage:"
    echo "      generateAlgorithm.sh [AlgorithmName]"
else
    if [ -f $@Algorithm.hpp ]; then
        echo "ERROR: Could NOT generate $@Algorithm.hpp. File already exist!"
    else
        echo ""                                                 >  $@Algorithm.hpp
        echo "////////////////////////////////////////////////" >> $@Algorithm.hpp
        echo "/// File generataed by generateAlgorithms.sh ///" >> $@Algorithm.hpp
        echo "////////////////////////////////////////////////" >> $@Algorithm.hpp
        echo ""                                                 >> $@Algorithm.hpp
        echo ""                                                 >> $@Algorithm.hpp
        cat TemplateAlgorithm.hpp           >> $@Algorithm.hpp
        sed -i "s/Template/$@/g" $@Algorithm.hpp
        sed -i "s/TEMPLATE/$@/g" $@Algorithm.hpp
        echo "$@Algorithm.hpp generated"
    fi
    
    if [ -f $@Algorithm.cpp ]; then
        echo "ERROR: Could NOT generate $@Algorithm.cpp. File already exist!"
    else
        echo ""                                                 >  $@Algorithm.cpp
        echo "////////////////////////////////////////////////" >> $@Algorithm.cpp
        echo "/// File generataed by generateAlgorithms.sh ///" >> $@Algorithm.cpp
        echo "////////////////////////////////////////////////" >> $@Algorithm.cpp
        echo ""                                                 >> $@Algorithm.cpp
        echo ""                                                 >> $@Algorithm.cpp
        cat TemplateAlgorithm.cpp           >> $@Algorithm.cpp
        sed -i "s/Template/$@/g" $@Algorithm.cpp
        sed -i "s/TEMPLATE/$@/g" $@Algorithm.cpp   
        echo "$@Algorithm.cpp generated"
    fi
fi