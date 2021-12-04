const bcrypt = require('bcrypt');
const config = require('../config.json');


//Mongo inc++ seq
function getNextSequenceValue(db, strCounter, callback){
	var sequenceDocument = db.collection('counters').findOneAndUpdate(
		{_id: strCounter},
		{$inc:{seq:1}},
		{new:true},
		callback
	);
}

//Get IP address and check if its IPv4 or IPv6
function GetIPAddress(req)
{
	var ip = req.headers['cf-connecting-ip'] || req.headers['x-forwarded-for'] || req.connection.remoteAddress;
	
	if (ip.substr(0, 7) == "::ffff:") {
		ip = ip.substr(7);
	}
	return ip;
}

function findUser(userName, db,passcode, callback){
	db.collection('users').find({username: userName}).toArray(function(err, result){
		//console.log(result);
		//console.log(result[1].price);

		//Database result length
		if(result.length <= 0)
		{
			if (callback && typeof(callback) === 'function')
			{
				//No result found
				callback(err, false);
			}
		}
		else
		{
			bcrypt.compare(passcode, result[0].password, function(berr, bresult)
		
				{
				
					if (callback && typeof(callback) === 'function')
					{
						if(bresult)
						callback(berr,true);
						else
						callback(berr, false);
					}
				}); 
		
		}

		//console.log(result[i].username);
				//return result[i].username;

				//Check if callback exist and its a function
				
				

			/* 	bcrypt.compare("22344", result[i].password, function(berr, bresult)
				{
					console.log(bresult);
				}); */
			
		
	});
}

module.exports = function (app, express, db)
{
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
			findUser(req.params.username, db,req.params.password, function(err, result)
			{


				if(err || !result)
				{
					console.log("[LOGIN] %s failed to login username %s", GetIPAddress(req), req.params.username);
					
					

					var data = {};
					data['message'] = 'Login failed';
					data['code'] = '0';
					
					var prettydata = JSON.stringify(data, null, 2);
					res.type('json').send(prettydata);
					return;
				}
				else
				{
					
					req.session.auth=true;
					console.log("[LOGIN] %s successfully login username %s", GetIPAddress(req), req.params.username);
					
					
					var data = {};
					data['message'] = 'Login success';
					data['code'] = '10';
					
					var prettydata = JSON.stringify(data, null, 2);
					res.type('json').send(prettydata);
					return;
				}


			/* 	if(req.params.password == '123')
				{
					req.session.auth = true;
					res.send('you login');
					return;
				}
				else
				{
					//if username or password is wrong
					res.send('invalid username password');
					return;
				} */
			})	
		}
		//if auth is true
		else
		{
			var data = {};
					data['message'] = 'Already Logged in';
					data['code'] = '111';
					
					var prettydata = JSON.stringify(data, null, 2);
					res.type('json').send(prettydata);
		}
	});
	
	app.get('/user/create/:username/:password', function(req, res)
	{
		//if auth is true or auth doesn't exist
		if(req.session.auth)
		{

			var strUsername = req.params.username;
			var strPassword = req.params.password;
			
			if((strUsername != undefined) && (strPassword != undefined))
			{
				db.collection('users').find({"username":strUsername}).toArray(function(err, result){
					result = result[0];
					if(result == undefined)
					{
						getNextSequenceValue(db, 'userid', function(serr, sres)
						{
							db.collection("users").insertOne(
								{_id: sres.value.seq,
									username: strUsername, 
									password: String(bcrypt.hashSync(strPassword, config.Hash.saltround)),
									perm: "0,0,0,0,0"
								}, function(werr, wres){
								
								//if error creating user
								if(werr)
								{
									//console.log("[WEB][CREATE_USER] %s failed to create a new user %s", GetIPAddress(req), strUsername);
									//console.log(werr);
									
									var data = {};
									data['message'] = 'Failed to create a user';
									data['code'] = '104';
									
									var prettydata = JSON.stringify(data, null, 2);
									res.type('json').send(prettydata);
									return;
								}
								else
								{
									//console.log("[WEB][CREATE_USER] %s successfully created a new user %s", GetIPAddress(req), strUsername);
									
									var data = {};
									data['message'] = 'Successfully created a user';
									data['code'] = '001';
									
									var prettydata = JSON.stringify(data, null, 2);
									res.type('json').send(prettydata);
									return;
								}
							});
						});
					}
					else
					{
						var data = {};
						data['message'] = 'Username already exist';
						data['code'] = '101';
						
						var prettydata = JSON.stringify(data, null, 2);
						res.type('json').send(prettydata);
						return;
					}
				});
			}
			else
			{
				//Invalid	
				var data = {};
				data['message'] = 'Invalid username or password';
				data['code'] = '102';
				
				var prettydata = JSON.stringify(data, null, 2);
				res.type('json').send(prettydata);
				return;
			}
			
		}
		//Not login
		else
		{
			var data = {};
			data['message'] = 'Unauthorized';
			data['code'] = '900';
			
			var prettydata = JSON.stringify(data, null, 2);
			res.type('json').send(prettydata);
			return;
		}
	});


	app.get('/user/create/:name/:email/:phone', function(req, res)
	{
		//if auth is false or auth doesn't exist
		console.log(req.params);
		console.log("NAME: %s", req.params.name);
		console.log("EMAIL: %s", req.params.email);

		res.send("CREATE IS WORKING");
	});


	app.get('/inventory', function (req, res) 
	{
		//if(req.session.auth)
	//	{

		/*
		const inventory= Inventory.find({});
		console.log(inventory);
		res.render(inventory);
		*/

		db.collection('inventory').find({}).toArray(function(err, result){
			//console.log(result);
			//console.log(result[1].price);
			for(var i = 0; i < result.length; i++)
			{
				if(result[i].price == 35)
				{
					console.log(result[i]);
				}
			}
		});

		res.send("working");
	//	}
		
		//res.send('you are not login');
	});

	app.post('/inventory', function (req,res) {
		const newInventory = new inventory(res.body);
		 newInventory.save();
		console.log(newInventory);
		res.send("new invetory item added");
	})
	
	
	app.get('/inventory/new', function(req, res)
	{
		//if(req.session.auth)
		//{
		res.render('inventory/new');
		//}
		
		//res.send('you are not login');
	});

	app.get('/seed', function (req, res) 
	{
		//if(req.session.auth)
	//	{
		db.listCollections({name: 'inventory'}).next(function(err, collinfo){
			if(collinfo == null)
			{
				console.log("Unable to find collection name inventory");
				db.createCollection("inventory", function(cerr, res)
				{
					if(cerr)
					{
						console.log("Failed to create collection name inventory");
						throw cerr;
					}
					else
					{					
						getNextSequenceValue(db, 'inventoryid', function(nerr, nres)
						{
							var hashpass = bcrypt.hashSync("123QWEasd", config.Hash.saltround);
							db.collection("inventory").insertOne({_id: nres.value.seq, username: "admin", password: String(hashpass), rank: 0}, function(uerr, ures) {
								if(uerr)
								{
									console.log("Failed to create an admin. Please make sure your database is clean");
									throw uerr;
								}
								else
								{
									console.log("Created a admin with username admin and password adminCIRC");
								}
							});
						});
					}
				});
			}
		});

	//	}
		
		//res.send('you are not login');
	});

	//Set page 404
	app.use(function(req, res, next) {
		console.log("[WEB] %s connected to %s", GetIPAddress(req), req.originalUrl);
		res.status(404);
		return;
	});
	
}
