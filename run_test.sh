#!/bin/bash

function main
{
    readonly SCRIPT_DIR=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)
    mkdir ${SCRIPT_DIR}/build
    cd ${SCRIPT_DIR}/build
    cmake ../test/.
    make -j4
    cd bin
    ./ScopedMeasurementTest
}

main