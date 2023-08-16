#!/usr/bin/node

const express = require('express');
const app = express();
const port = 3000;

const bodyParser = require('body-parser');
const cookieParser = require('cookie-parser');
const session = require('express-session');

const mysql = require('mysql');
const dbconfig = require('./config/dbinfo.js');
const connection = mysql.createConnection(dbconfig);

const path = require('path');



app.set('view engine', 'ejs');
app.set('views', path.join(__dirname));

app.use(express.static('public'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(
    session({
        //secret은 임의의 난수값
        secret: 'WIh!8kO29*@9akwMdl@&',
        resave: true,
        saveUninitialized: true
    })
);

app.listen(port, () => {
	console.log(`Example app listening on port ${port}`);
});

app.get('/api',(req,res) => {
	connection.query('SELECT * FROM DB1.User', (error, result) => {
	    if (error) throw error;
        res.send(result);
	});
});


///////////////
//// GET
///////////////

app.get('/',(req,res) => {
	res.sendFile(path.join(__dirname,'./','front','main.html'));
});

app.get('/login', (req, res) => {
    res.sendFile(path.join(__dirname,'./','front','login.html'));
});

app.get('/signin', (req, res) => {
    res.sendFile(path.join(__dirname,'./','front','signin.html'));
});

app.get('/post', (req, res) => {
    res.sendFile(path.join(__dirname,'./','front','post.html'));
});

app.get('/header', (req, res) => {
    res.sendFile(path.join(__dirname,'./','front','fullheader.html'));
    // if (req.session.user != true){
    //     res.sendFile(path.join(__dirname,'./','front','header_logout.html'));
    // }
    // else {
    //     res.sendFile(path.join(__dirname,'./','front','header_login.html'));
    // }
});

///////////////
//// 회원가입
///////////////

app.post('/signin', (req, res) => {
	//json 데이터 추출
    const { user_name, user_id, user_pwd } = req.body;
    console.log(`user name : ${user_name}, user id : ${user_is}, user pwd: ${user_pwd}`)
	
	const sql = 'INSERT INTO DB1.User (user_name, user_id, user_pwd) VALUES (${user_name}, ${user_id}, ${user_pwd})';
	connection.query(sql);

    console.log("회원가입이 완료되었습니다.");
    res.redirect('/login');
});

///////////////
//// 로그인
///////////////

app.post('/login', (req, res) => {
    console.log(`${req.session.user} ? ${req.session.user_id} == 'test' : false`);
    if (req.session.user ? req.session.user.id == 'test' : false) {
        console.log("로그인 유지");
        res.redirect('/');
    }

    else if(req.body.user_id == 'test' && req.body.user_pwd == '1234') {
        req.session.user = {
            id: req.body.id,
        };
        
        res.setHeader('Set-Cookie', ['user=' + req.body.user_id]);
        console.log("아이디 test, 비밀번호 1234 통과");
        res.redirect('/');
    }


    else if(req.body.user_id == '12' && req.body.user_pwd == '12') {
        req.session.user = {
            id: req.body.id,
        };
        
        res.setHeader('Set-Cookie', ['user=' + req.body.user_id]);
        console.log(`아이디 ${user_id}, 비밀번호 ${user_pwd} 통과`);
        res.redirect('/');
    }
    else {
        console.log("잘못된 아이디, 비밀번호");
        res.redirect('/login');
    }
});

///////////////
//// 로그아웃
///////////////

app.get('/logout', (req, res) => {
    req.session.destroy((err) => {
        if (err) {
            console.log(err);
        }
        else {
            res.clearCookie('user');
            res.redirect('/');
            console.log("로그아웃되었습니다.");
        }
    });
});

///////////
// 라우팅
///////////

// app.get('/board/ssr/:bid', (req, res) => {
//     res.render('board', { title: req.params.bid , contents: 'this is SSR page' + req.params.bid });
// });

//express.js에서 SQL 작성 위한 코드

// app.get('/api', (req, res) => {
// 	connection.query('SELECT * FROM Test1', (error, rows) => {
// 		if (error) throw error;
// 		res.send(rows);
// 	});
// });

// app.post('/api', (req, res) => {
// 	//json 데이터 추출
// 	const { name, age, address } = req.body;
	
// 	const sql = 'INSERT INTO Test1 (name, age, address) VALUES '(${name}, ${age}, ${address})'';
// 	connection.query(sql);

// 	res.redirect('http://ubserver/');
// });

// app.put('/api', (req, res) => {
// 	const { name, age, address } = req.body;

// 	const sql = 'UPDATE Test1 SET age = '${age}', address = '${address}' WHERE name = '${name}'';
// 	connection.query(sql);

// 	res.redirect('http://ubserver/');
// });

// app.delete('/api', (req, res) => {
// 	const { name } = req.body;

// 	const sql = 'DELETE FROM Test1 WHERE name = '${name}'';
// 	connection.query(sql);

// 	res.redirect('http://ubserver/');
// });
