#! /usr/bin/bash
rm -r /x86_64
cd channels
nrnivmodl Kv3.mod Kv4.mod Kir.mod Kvs1.mod Kv7.mod Kv10.mod Cav1.mod Cav2.mod Cav3.mod
mv x86_64/ ..
