#! /usr/bin/bash

cd channels
nrnivmodl Kv4.mod Kir.mod Kvs1.mod Kv7.mod Kv10.mod Cav1.mod Cav2.mod
mv x86_64 ..
