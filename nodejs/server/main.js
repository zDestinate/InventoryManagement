const express = require('express'),
	app = express(),
	serv = require('http').Server(app);
const session = require('express-session')
const path = require('path');
const bodyParser = require("body-parser");
	
//Server start
console.log("[SERVER] Server started");


app.set('trust proxy', 1) // trust first proxy
app.use(session({
	name: '370',
	secret: ' asjdfhioq23 qkjdwr 723iawfhsfdfsdf hahdk',
	resave: false,
	saveUninitialized: true,
	cookie:
	{ 
		secure: false,
		maxAge: 3600000
	}
}))


//Set server default path
app.use(express.static( __dirname + '/../client'));

app.set("views", path.join(__dirname, '../views'));
app.engine("html", require("dot-emc").init(
    {
        app: app,
        fileExtension:"html"
    }
).__express);
app.set("view engine", "html");

//bodyParser
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

//Get IP address and check if its IPv4 or IPv6
function GetIPAddress(req)
{
	var ip = req.headers['cf-connecting-ip'] || req.headers['x-forwarded-for'] || req.connection.remoteAddress;
	
	if (ip.substr(0, 7) == "::ffff:") {
		ip = ip.substr(7);
	}
	return ip;
}


app.get('/', function(req, res)
{
	var data = {};
	data['test'] = 'something';
	data['test2'] = 'something2';
	
	var prettydata = JSON.stringify(data, null, 2);
	res.type('json').send(prettydata);
});

app.get('/user/login/:username/:password', function(req, res)
{
	//if auth is false or auth doesn't exist
	if(!req.session.auth)
	{
		if(req.params.username == 'abc' && req.params.password == '123')
		{
			req.session.auth = true;
			res.send('you login');
			return;
		}
		
		//if username or password is wrong
		res.send('invalid username password');
		return;
	}
	//if auth is true
	else
	{
		res.send('you already login');
	}
});

app.get('/inventory', function(req, res)
{
	if(req.session.auth)
	{
		var data = {};
		data['test'] = 'something';
		data['test2'] = 'something2';
		
		var prettydata = JSON.stringify(data, null, 2);
		res.type('json').send(prettydata);
		return;
	}
	
	res.send('you are not login');
});

//Set page 404
app.use(function(req, res, next) {
	console.log("[WEB] %s connected to %s", GetIPAddress(req), req.originalUrl);
	res.status(404);
	return;
});

//Server listen port and IP
serv.listen(80, "157.245.0.156");
console.log("[SERVER] Server listening on port 80...");