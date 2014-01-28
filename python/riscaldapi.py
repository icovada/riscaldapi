#!/usr/bin/python3
print ("Starting program")
import serial
import pymysql
import time
import rrdtool

count = 1
test=serial.Serial("/dev/ttyACM0",9600,timeout=5)
time.sleep(1)
test.open()
time.sleep(1)

conn = pymysql.connect(host="127.0.0.1", user="riscaldapi", passwd="riscaldapi", db="riscaldapi")
cur = conn.cursor()

flowOutHistory=[40,40,40,40]

#out = open("out.csv","wb")
while True:
	try:
		test.write(bytes("t", encoding='ascii'))
		time.sleep(1)
		myin = test.readline()
	except serial.serialutil.SerialException:
		pass

	temps = str(myin, encoding="ascii").strip().split(",")

	if (len(temps) == 7):
		#Guess whether fire is on or not
		flowOut = float(temps[2])
		if (flowOut > (sum(flowOutHistory) / len(flowOutHistory) )):
			fire = 1
		else:
			fire = 0

		#Keep the last 4 values for average
		flowOutHistory.append(float(temps[2]))
		del flowOutHistory[0]

		print(temps, fire)
		try:
			cur.execute("INSERT INTO `riscaldapi`.`temphistory` (`inside`, `flowIn`, `flowOut`, `goalTemp`, `diffTemp`, `rel1`, `fire`) VALUES ('"+str(temps[0])+"', '"+str(temps[1])+"', '"+str(temps[2])+"', '"+str(temps[3])+"', '"+str(temps[4])+"', '"+str(temps[5])+"', '"+str(fire)+"')");
		except:
			time.sleep(3)

		try:
			ret = rrdtool.update('riscaldapi.rrd', 'N:%f:%f:%f' %(float(temps[0]), float(temps[1]), float(temps[2])))
		except:  #If the answer does not contain three fields (like an ACK)
			pass

	time.sleep(4)
	conn.commit()

test.close()
conn.close()
