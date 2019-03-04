import flask
from flask import request, jsonify

app = flask.Flask(__name__)
app.config["DEBUG"] == True

#LED Control Variable
global LEDstat
LEDstat = 0

#404 error handler
@app.errorhandler(404)
def siteNotFound(self):
	return jsonify([{"code":404, "API code":404, "message":"site not found"}])

#Home page
@app.route('/', methods=['GET'])
def home():
    return "<h3>IoT Experiment</h3><p>This is the home page!<p>LED status = "+str(LEDstat)

#Main Route
@app.route("/iot", methods=['GET'])
def iot():
	global LEDstat
	reqType = request.args.get('reqtype')
	if reqType == 'update':
		LEDstat = request.args.get('led')
		LEDstat = 1 if int(LEDstat) > 0 else 0 #To resolve false values
		return "updated LED = "+str(LEDstat)
	
	elif reqType == 'fetch':
		Payload = [{"metricID":"Test","Message":"<Any message that you wish to add>","LED":LEDstat}]
		# Payload JSON must be dictionaries within a list
		return jsonify(Payload)
	
	else:
		return jsonify([{"code":200,"API code":404, "message":"Request not resolved!"}])

app.run(host='0.0.0.0', port=8080, debug=True)
