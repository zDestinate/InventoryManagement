const express = require('express'),
	app = express(),
	serv = require('http').Server(app);
const ejs = require('ejs');
const session = require('express-session');
const path = require('path');
const bodyParser = require("body-parser");
const MongoClient = require('mongodb').MongoClient;
const bcrypt = require('bcrypt');

const config = require('../config.json');
	
//Server start
console.log("[SERVER] Server started");


app.set('trust proxy', 1) // trust first proxy
app.use(session({
	name: '370',
	secret: config.Cookie.secret_key,
	resave: false,
	saveUninitialized: true,
	cookie:
	{ 
		sameSite: true,
		secure: false,
		maxAge: config.Cookie.expire_time
	}
}))


//Set server default path
app.use(express.static( __dirname + '/../client'));
app.engine('html', ejs.renderFile);
app.set("views", path.join(__dirname, '../views'));
app.set("view engine", "html");

//bodyParser
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

//Mongo inc++ seq
function getNextSequenceValue(db, strCounter, callback){
	var sequenceDocument = db.collection('counters').findOneAndUpdate(
		{_id: strCounter},
		{$inc:{seq:1}},
		{new:true},
		callback
	);
}

//init mongo
MongoClient.connect(config.Mongo.url, {useNewUrlParser: true, useUnifiedTopology: true}, function(err, database)
{
	if(err) throw err;
	
	console.log("Connection to database server successful");
	var db = database.db(config.Mongo.database);
	
 	//Creating counter
	db.listCollections({name: 'counters'}).next(function(err, collinfo){
		//if collinfo is column
		if(collinfo == null)
		{
			console.log("Unable to find collection name counters");

			//create this collection
			db.createCollection("counters", function(cerr, res)
			{
				if(cerr)
				{
					console.log("Failed to create collection name counters");
					throw cerr;
				}
				else
				{
					console.log("Created a collection name counters");
					db.collection("counters").insertOne({_id: "userid", seq: 0}, function(uerr, ures) {
						if(uerr)
						{
							console.log("Failed to create userid in counters collection");
							throw uerr;
						}
						else
						{
							console.log("Created userid counter");
						}
					});
				}
			});
		}
	});
	//create an intialize users db 
	db.listCollections({name: 'users'}).next(function(err, collinfo){
		if(collinfo == null)
		{
			console.log("Unable to find collection name users");
			db.createCollection("users", function(cerr, res)
			{
				if(cerr)
				{
					console.log("Failed to create collection name users");
					throw cerr;
				}
				else
				{					
					getNextSequenceValue(db, 'userid', function(nerr, nres)
					{
						var hashpass = bcrypt.hashSync("123QWEasd", config.Hash.saltround);
						db.collection("users").insertOne({_id: nres.value.seq, username: "admin", password: String(hashpass), rank: 0}, function(uerr, ures) {
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

	//create inventory
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
				{					//refactor into insert inventory function
						db.collection("inventory").insertOne(
							{
								description: "sand",
								price: "0",
								quantity:"0",
								function(uerr, ures) {
							   if(uerr)
							   {
								   console.log("Failed to create item sand. Please make sure your database is clean");
								   throw uerr;
							   }
							   else
							   {
								   console.log("Created item sand");
							   }}

						});
				}
			});
		}
	}); 

	db.listCollections({name: 'sales'}).next(function(err, collinfo){
		if(collinfo == null)
		{
			console.log("Unable to find collection name sales");
			db.createCollection("sales", function(cerr, res)
			{
				if(cerr)
				{
					console.log("Failed to create collection name sales");
					throw cerr;
				}
				else
				{console.log("Created item sales");
				}
			});
		}
	}); 

	//
	//Pages
	require('./pages')(app, express, db);
});

//Server listen port and IP
serv.listen(config.Server.port, config.Server.address, function()
{
	console.log("[SERVER] Server listening on port 80...");
});

