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
//finds user in db if exists 
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

	
		
	});
}
function findUsers(db, callback)
	{
		db.collection('users').find({}).toArray(function(err, result)
		{
			if (callback && typeof(callback) === 'function')
			{ callback(err,result);}

		});
	}

	function findItems(db, callback)
	{
		db.collection('inventory').find({}).toArray(function(err, result)
		{
			if (callback && typeof(callback) === 'function')
			{ callback(err,result);}

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
//user list route
	app.get('/user', function(req,res){
		findUsers(db,function(err,result){
			console.log(result);
			if(err||!result)
			{console.log("Could not find any users");}
			else{ 
				res.send(result);

			}
		});
	});
//inventory list route
	app.get('/inventory', function(req,res){
		findItems(db,function(err,result){
			console.log(result);
			if(err||!result)
			{console.log("Could not find any itemss");}
			else{ 
				res.send(result);

			}
		});
	});
//login route
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
	
	app.get('/user/create/:username/:password/:phone/:perm/:flname/:email', function(req, res)
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
							//refactor this later 
							db.collection("users").insertOne(
								{_id: sres.value.seq,
									username: strUsername, 
									password: String(bcrypt.hashSync(strPassword, config.Hash.saltround)),
									name: req.params.flname,
									number: req.params.phone,
									email: req.params.email,
									perm: req.params.perm
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
//edit user route
	app.get('/user/edit/:username/:nusername/:nname/:nnum/:nemail/:nperm', function(req, res){
console.log(req.params.nnum);
		db.collection("users").update(
			{"username": req.params.username },
			{$set: { "username": req.params.nusername,"name":req.params.nname,"number":req.params.nnum,"email":req.params.nemail,"perm":req.params.nperm}},
			function(err, result)
			{
				if(err) throw err;
				console.log(result);
			});
			console.log("updated user")
			var data = {};
			data['message'] = 'User updated';
			data['code'] = '015';
			
			var prettydata = JSON.stringify(data, null, 2);
			res.type('json').send(prettydata);
			return;

	});
	//delete user route
	app.get('/user/delete/:username', function(req, res){

		db.collection("users").deleteOne(
			{"username": req.params.username });
			console.log("deleted user")
			var data = {};
			data['message'] = 'User deleted';
			data['code'] = '555';
			
			var prettydata = JSON.stringify(data, null, 2);
			res.type('json').send(prettydata);
			return;
	});
	//delete user route
	app.get('/inventory/delete/:item', function(req, res){

		db.collection("inventory").deleteOne(
			{"description": req.params.item });
			console.log("deleted user")
			var data = {};
			data['message'] = 'Item deleted';
			data['code'] = '555';
			
			var prettydata = JSON.stringify(data, null, 2);
			res.type('json').send(prettydata);
			return;
	});
	//edit inventory route
	app.get('/inventory/edit/:desc/:ndesc/:nquant/:ncost', function(req, res){


		db.collection("inventory").update(
			{"description": req.params.desc },
			{$set: { "description": req.params.ndesc,"price":req.params.ncost,"quantity":req.params.ncost}});
			console.log("updated inventory item");
			var data = {};
			data['message'] = 'Item updated';
			data['code'] = '915';
			
			var prettydata = JSON.stringify(data, null, 2);
			res.type('json').send(prettydata);
			return;

	});
// create inventory route
	app.get('/inventory/create/:desc/:cost/:quant/:Upc', function(req, res)
	{
		//if auth is true or auth doesn't exist
		if(req.session.auth)
		{

			
			if((req.params.desc != undefined) && (req.params.cost != undefined) &&(req.params.quant)&&(req.params.Upc) )
			{
				db.collection('inventory').find({"desc":req.params.desc }).toArray(function(err, result){
					result = result[0];
					if(result == undefined)
					{
						
							//refactor this later 
							db.collection("inventory").insertOne(
								{
									description: req.params.desc , 
									price: req.params.cost,
									quantity: req.params.quant,
									upc:req.params.Upc
									
								}, function(werr, wres){
								
								//if error creating user
								if(werr)
								{
									//console.log("[WEB][CREATE_USER] %s failed to create a new user %s", GetIPAddress(req), strUsername);
									//console.log(werr);
									
									var data = {};
									data['message'] = 'Failed to create item';
									data['code'] = '104';
									
									var prettydata = JSON.stringify(data, null, 2);
									res.type('json').send(prettydata);
									return;
								}
								else
								{
									//console.log("[WEB][CREATE_USER] %s successfully created a new user %s", GetIPAddress(req), strUsername);
									
									var data = {};
									data['message'] = 'Successfully created item';
									data['code'] = '001';
									
									var prettydata = JSON.stringify(data, null, 2);
									res.type('json').send(prettydata);
									return;
								}
							});
						
					}
					else
					{
						var data = {};
						data['message'] = 'Item already exist';
						data['code'] = '101';
						
						var prettydata = JSON.stringify(data, null, 2);
						res.type('json').send(prettydata);
						return;
					}
				});
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

//  log out user route
	app.get('/user/logout', function(req, res){
		req.session.destroy();
		console.log('logged out')
		var data = {};
			data['message'] = 'Logged Out';
			data['code'] = '876';
			
			var prettydata = JSON.stringify(data, null, 2);
			res.type('json').send(prettydata);
			return;

	});



	//Set page 404
	app.use(function(req, res, next) {
		console.log("[WEB] %s connected to %s", GetIPAddress(req), req.originalUrl);
		res.status(404);
		return;
	});
	
}
