#!/usr/bin/node
const express = require('express');
const mysql = require('mysql');
const dbconfig = require('./config/dbinfo.js');
const connection = mysql.createConnection(dbconfig);

const path = require('path');
const cors = require('cors');
const app = express();
const port = 3000;

/*
app.get('/', (req, res) => {
	connection.query('SELECT * FROM TB1', (error, rows) => {
		if (error) throw error;
		res.send(rows);
	});
});
*/


//DB를 80포트로  아래 코드 활성화
app.get('/api',(req,res) => {
	connection.query('SELECT * FROM TB1', (error, rows) => {
	if (error) throw error;
	res.send(rows);
	});
});

app.get('/',(req,res) => {
	res.sendFile(path.join(__dirname,'..','html','main.html'));
});

app.listen(port, () => {
	console.log(`Example app listening on port ${port}`);
});


//express.js에서 SQL 작성 위한 코드
/*
app.get('/api', (req, res) => {
	connection.query('SELECT * FROM Test1', (error, rows) => {
		if (error) throw error;
		res.send(rows);
	});
});

app.post('/api', (req, res) => {
	//json 데이터 추출
	const { name, age, address } = req.body;
	
	const sql = 'INSERT INTO Test1 (name, age, address) VALUES '(${name}, ${age}, ${address})'';
	connection.query(sql);

	res.redirect('http://ubserver/');
});

app.put('/api', (req, res) => {
	const { name, age, address } = req.body;

	const sql = 'UPDATE Test1 SET age = '${age}', address = '${address}' WHERE name = '${name}'';
	connection.query(sql);

	res.redirect('http://ubserver/');
});

app.delete('/api', (req, res) => {
	const { name } = req.body;

	const sql = 'DELETE FROM Test1 WHERE name = '${name}'';
	connection.query(sql);

	res.redirect('http://ubserver/');
});
*/
