//editted original app.js module to use custom arestNoXBee dependency

// Module
var express = require('express');
var app = express();

// Define port
var port = 3000;

// View engine
app.set('view engine', 'jade');

// Set public folder
app.use(express.static(__dirname + '/public'));

// Serve interface
app.get('/', function(req, res){
  res.render('dashboard');
});

// Rest
var rest = require("arestNoXBee")(app);

rest.addDevice('serial',"COM3",115200);

rest.heartBeat(10000);

// Start server
app.listen(port);
console.log("Listening on port " + port);
