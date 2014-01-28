#!/usr/bin/python3
print ("Starting program")
import serial
import pymysql
import time
import rrdtool
import datetime

count = 1
test=serial.Serial("/dev/ttyACM0",9600,timeout=5)
time.sleep(1)
test.open()
time.sleep(1)

conn = pymysql.connect(host="127.0.0.1", user="riscaldapi", passwd="riscaldapi", db="riscaldapi")
cur = conn.cursor()

flowOutHistory=[40,40,40,40]
counter = 0
setGoalTemp=20
setDiffTemp=0.15
now = datetime.datetime.now()
seconds = ((now.weekday()*24*3600) + (now.hour*3600) + (now.minute*60)+ now.second)

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

		#Change desired temp according to database
		if (float(setGoalTemp) != float(temps[3])):
			try:
				command = "u"+str(setGoalTemp)
				test.write(bytes(command, encoding='ascii'))
				time.sleep(1)
				myin = test.readline()
			except serial.serialutil.SerialException:
				time.sleep(2)
				command = "u"+str(setGoalTemp)
				test.write(bytes(command, encoding='ascii'))
				time.sleep(1)
				myin = test.readline()

		if (float(setDiffTemp) != float(temps[4])):
			try:
				command = "i"+str(setDiffTemp)
				test.write(bytes(command, encoding='ascii'))
				time.sleep(1)
				myin = test.readline()
			except serial.serialutil.SerialException:
				time.sleep(2)
				command = "i"+str(setDiffTemp)
				test.write(bytes(command, encoding='ascii'))
				time.sleep(1)
				myin = test.readline()

		#Guess whether fire is on or not
		flowOut = float(temps[2])
		if (flowOut > (sum(flowOutHistory) / len(flowOutHistory) )):
			fire = 1
		else:
			fire = 0

		#Keep the last 4 values for average
		flowOutHistory.append(float(temps[2]))
		del flowOutHistory[0]

		print(temps, fire, seconds)
		try:
			cur.execute("INSERT INTO `riscaldapi`.`temphistory` (`inside`, `flowIn`, `flowOut`, `goalTemp`, `diffTemp`, `rel1`, `fire`) VALUES (%s, %s, %s, %s, %s, %s, %s)" %(temps[0],temps[1],temps[2],temps[3],temps[4],temps[5],temps[6]));
		except:
			pass

		try:
			ret = rrdtool.update('riscaldapi.rrd', 'N:%s:%s:%s' %(temps[0], temps[1], temps[2]))

		except:
			pass

	time.sleep(4)

	counter = counter + 1
	if (counter >= 5):
		counter = 0
		now = datetime.datetime.now()
		seconds = ((now.weekday()*24*3600) + (now.hour*3600) + (now.minute*60)+ now.second) #Seconds from monday midnight
		cur.execute("SELECT * FROM `schedule` WHERE `seconds` < %i ORDER BY `seconds` DESC LIMIT 1" %(seconds))
		result = cur.fetchall()
		setGoalTemp = float(result[0][1])
		setDiffTemp = float(result[0][2])

		conn.commit()

test.close()
conn.close()
