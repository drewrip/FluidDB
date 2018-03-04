import msgpackrpc
from flask import Flask, request
from flask_restful import Resource, Api, reqparse
app = Flask(__name__)
api = Api(app)

methods = ["adddata", "removedata", "changedata", "getboat", "makeboat", "removeboat", "getboatbyindex", "getnumberboats", "makeliq", "removeliq"]

def callBack(paramNum, params):
	client = msgpackrpc.Client(msgpackrpc.Address("localhost", 8080))
	if(paramNum >= 0 and paramNum <= 2):
		result = client.call(methods[paramNum], params[0], params[1], params[2]) 
	elif(paramNum >= 3 and paramNum <= 6):
		result = client.call(methods[paramNum], params[0], params[1])
	elif(paramNum >= 7 and paramNum <= 9):
		result = client.call(methods[paramNum], params[0])
	return result

@app.route("/api/", methods=["POST", "GET"])
def AccessDB():
	reqMethod = request.values.get("method")
	reqParams = request.values.get("params")
	return callBack(methods.index(reqMethod),reqParams)