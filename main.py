import zmq

from SerialHandler import SerialHandler
from SerialHandler import ReadThread
from SerialHandler import FileHandler
import threading
import serial

context = zmq.Context()
zsock_t = context.socket(zmq.PULL)
zsock_t.bind("ipc:///tmp/com")

sh = SerialHandler()
th = ReadThread(threading.Thread, serial.Serial('/dev/ttyACM0',256000,timeout=1), FileHandler('historyFile.txt'), True)
th.start()

#sh.sendEncoderPublisher(False)
sh.activateSensorPublisher(False)
sh.sendPidActivation(False)

print("Start listen")
while True:
	msg = zsock_t.recv()
	floats = msg.decode("utf-8").split(" ")
	speed = float(floats[0])
	angle = float(floats[1])
	print("Speed: {}, Angle: {}".format(speed, angle))
	sh.sendMove(speed, angle, angle)
	if speed == 0.0:
		sh.sendBrake(angle)
th.stop()
