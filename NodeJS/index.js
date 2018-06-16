const http = require("http");
const functions = require("firebase-functions");

var mqtt = require("mqtt");
var client = mqtt.connect("mqtt://broker.mqtt-dashboard.com");

exports.dialogflowFirebaseFulfillment = functions.https.onRequest(
  (req, res) => {
    let intent = req.body.queryResult.intent.displayName;
    let arg = "";
    let resp = "";
    let flag = true;
    if (intent == "ChangeColor") {
      let color = req.body.queryResult.parameters["color"];
      arg = color;
      resp = "Sure, changing the color to " + color + "!";
    } else if (intent == "LightsOff") {
      arg = "ff";
      resp = "Sure, turning off the light!";
    } else if (intent == "LightsOn") {
      arg = "on";
      resp = "Sure, turning on the light!";
    } else if (intent == "Other") {
      resp = "Suno, bhaago yahan se!";
      flag = false;
    }

    if (flag) {
      callSmartHome(arg, resp)
        .then(output => {
          res.json({ fulfillmentText: output });
          return true; // Return the results of the weather API to Dialogflow
        })
        .catch(error => {
          res.json({
            fulfillmentText: `I don't know the status of light! ` + error
          });
          return false;
        });
    } else {
      res.json({ fulfillmentText: resp });
    }
  }
);

function callSmartHome(arg, resp) {
  return new Promise((resolve, reject) => {
    client.publish("airteldemo", arg);

    resolve(resp);
  });
}
