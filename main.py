import msgpackrpc
from flask import Flask, request
from flask_restful import Resource, Api, reqparse
app = Flask(__name__)
api = Api(app)

methods = ["makeboat", "changedata", "getboat", "removeboat", "getboatbyindex", "getnumberboats", "makeliq", "removedata", "removeliq", "close"]

def callBack(paramNum, params):
	client = msgpackrpc.Client(msgpackrpc.Address("localhost", 8080))
	if(paramNum == 9):
		result = client.call(methods[paramNum])
	if(paramNum == 0):
		result = client.call(methods[paramNum], params[0], params[1], params[2]) 
	elif(paramNum >= 1 and paramNum <= 4):
		result = client.call(methods[paramNum], params[0], params[1])
	elif(paramNum >= 5 and paramNum <= 8):
		result = client.call(methods[paramNum], params[0])
	return result

@app.route("/api/", methods=["POST", "GET"])
def AccessDB():
	reqMethod = request.values.get("method")
	reqParams = request.values.get("params")
	return callBack(methods.index(reqMethod),reqParams)