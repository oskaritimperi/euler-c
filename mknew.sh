#!/bin/sh

PROBNUM="$1"
PROBDIR="p${PROBNUM}"

if [ -z "$PROBNUM" ]; then
    echo "usage: $0 problemnum"
    exit 1
fi

cp -rv template "${PROBDIR}"

cd "${PROBDIR}"

sed -i "s/PROBNUM/$PROBNUM/g" CMakeLists.txt

cmake -G "Unix Makefiles"
