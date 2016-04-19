#!/bin/bash

mkdir -p tfy13ask
mkdir -p tfy13ask/src
mkdir -p tfy13ask/bin

cp -r clientserver/*.cc clientserver/*.h clientserver/Makefile clientserver/README tfy13ask/src/

tar -cvzf tfy13ask.tar.gz tfy13ask

