#!/bin/bash

DATA=../CK_Config.csv
IP=10.0.79.2
ftp -n $IP<<END
quote USER anonymous
quote PASS
put $DATA
quit
END