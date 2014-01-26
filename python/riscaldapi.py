#!/usr/bin/python3
print ("Starting program")
import serial
import pymysql
#import MAX3100 as COM
import time
# import string
#
count = 1
test=serial.Serial("/dev/ttyACM0",9600,timeout=5)
time.sleep(1)
test.open()
time.sleep(1)

conn = pymysql.connect(host="127.0.0.1", user="riscaldapi", passwd="riscaldapi", db="riscaldapi")
cur = conn.cursor()

#out = open("out.csv","wb")
while True:
	test.write(bytes("t", encoding='ascii'))
	time.sleep(1)
	try:
		myin = test.readline()
	except serial.serialutil.SerialException:
		pass
	temps = str(myin, encoding="ascii").strip().split(",")
	print(temps)
	try:
		cur.execute("INSERT INTO `riscaldapi`.`temphistory` (`inside`, `flowIn`, `flowOut`) VALUES ('"+str(temps[0])+"', '"+str(temps[1])+"', '"+str(temps[2])+"')");
	except IndexError:  #If the answer does not contain three fields (like an ACK)
		pass
#	out.write(myin)
#	out.flush()
	conn.commit()

test.close()
conn.close()
