#!/usr/bin/node
const express = require('express');
const mysql = require('mysql');
const dbconfig = require('./config/dbinfo.js');
const connection = mysql.createConnection(dbconfig);

const bodyParser = require('body-parser');
const cookieParser = require('cookie-parser');
const session = require('express-session');

const path = require('path');
const cors = require('cors');
const app = express();
const port = 3000;

app.use(express.static('front'));

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(
    session({
        //secret은 임의의 난수값
        secret: 'fjh!8ko29*@9akwmdl@&',
        resave: true,
        saveUninitialized: true
    })
);


app.listen(port, () => {
	console.log(`Example app listening on port ${port}`);
});

// app.get('/api',(req,res) => {
// 	connection.query('SELECT * FROM TB1', (error, rows) => {
// 	if (error) throw error;
// 	res.send(rows);
// 	});
// });

app.get('/',(req,res) => {
	res.sendFile(path.join(__dirname,'./','front','main.html'));
});



///////////////
//// 회원가입, 로그인, 로그아웃
///////////////

app.get('/login', (req, res) => {
    res.sendFile(path.join(__dirname,'./','front','login.html'));
});

app.post('/login', (req, res) => {
    if (req.session.user ? req.session.user.id == 'test' : false) {
        res.redirect('/');
    }
    else if(req.body.id == 'covi' && req.body.pw == '8611') {
        req.session.user = {
            id: req.body.id,
        };

        res.setHeader('Set-Cookie', ['user=' + req.body.id]);
        res.redirect('/');
    }
    else {
        res.redirect('/login');
    }
});


app.get('/signin', (req, res) => {
    res.sendFile(path.join(__dirname,'./','front','signin.html'));
});

app.post('/signin', (req, res) => {
	//json 데이터 추출
	const { user_name, user_id, user_pwd } = req.body;
	
	const sql = 'INSERT INTO DB1.User (user_name, user_id, user_pwd) VALUES (${user_name}, ${user_id}, ${user_pwd})';
	connection.query(sql);
});

app.get('/logout', (req, res) => {
    req.session.destroy((err) => {
        if (err) {
            console.log(err);
        }
        else {
            res.clearCookie('user');
            res.redirect('/');
        }
    });
});

///////////
// 라우팅
///////////

app.get('/posts/:pid' ,(req, res) => {
	const pageid = req.params.pid;
	//page id로 쿼리 실행
	//이후 , SSR 방식에 따라 작성?
	res.render('posts', { title: req.params.pid , contents: 'this is SSR page' + req.params.pid });
})


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
