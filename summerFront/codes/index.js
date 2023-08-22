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
const { pid } = require('process');

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
	connection.query('SELECT * FROM DB1.Content', (error, result, fields) => {
	    if (error) throw error;
        res.send(result);
	});
});


///////////////
//// GET
///////////////

// app.get('/',(req,res) => {
// 	res.sendFile(path.join(__dirname,'./','front','main.html'));
    
//     console.log(`req.cookies.user 값 = ${req.cookies.user}`); 
//     // 세션 유저이름 ★
// });

app.get('/',(req,res) => {
    if (req.cookies.user == null) {
        res.render(`./views/main_logout`);
    }
    else {
        res.render(`./views/main_login`);
    }

    console.log(`req.cookies.user 값 = ${req.cookies.user}`); 
    // 세션 유저이름 ★
});


app.get('/login', (req, res) => {
    if (req.cookies.user == null){
        res.sendFile(path.join(__dirname,'./','front','login.html'));
    }
    else {
        res.redirect('/');
        console.log(`현재 로그인 상태이므로 로그인 불필요`);
    }

    
});

app.get('/signin', (req, res) => {
    res.sendFile(path.join(__dirname,'./','front','signin.html'));
});

app.get('/post', (req, res) => {
    res.sendFile(path.join(__dirname,'./','front','post.html'))
});

app.get('/post/:pid', (req, res) => {
    var page_params = req.params.pid;
    var regex = /[^0-9]/g;
    var page_id = page_params.replace(regex, "");
    console.log(`${page_id} 페이지 발견`);

    connection.query(`SELECT * FROM DB1.Content WHERE id_cont = ?;`, [page_id], function (error, result, fields) {
        if (error) throw error;
        var string = JSON.stringify(result);
        var res_string = JSON.parse(string);
        console.log(`res_string[0].id_cont 값 : ${res_string[0].id_cont}`);
        
        if (res_string.length != 0) {
            connection.query(`SELECT Category_id_category, Content_id_cont FROM DB1.Category_has_Content WHERE Content_id_cont = ?;`, [res_string[0].id_cont], function (error, result, fields) {
                if (error) throw error;
                var string = JSON.stringify(result);
                var res2_string = JSON.parse(string);
                var post_log;
                if (req.cookies.user = null){
                    post_log = 'post_logout';
                }
                else {
                    post_log = 'post_login';
                }

                console.log(`${post_log}`);
                if (res2_string.length != 0) {
                    connection.query(`SELECT * from Category`, [res2_string[0].Category_id_category], function (error, result, fields) {
                        if (error) throw error;
                        var string = JSON.stringify(result);
                        var res3_string = JSON.parse(string);
                    
                    res.render(`./front_ejs/${post_log}`, {title: res_string[0].cont_title , contents: res_string[0].cont_cont , category : res3_string[0].cate_name});
                    console.log(`페이지 발견, 카테고리 발견`);
                    });
                }
                else {
                    res.render(`./front_ejs/${post_log}`, {title: res_string[0].cont_title , contents: res_string[0].cont_cont, category : "없음"});
                    console.log(`페이지 발견, 카테고리 미발견`);
                }
            });
        }
        else {
            console.log(`존재하지 않는 페이지입니다.`);
            res.redirect('/');
        }
    });
});

app.get('/write', (req, res) => {

    if (req.cookies.user == null){
        res.redirect('/login');
        console.log(`로그인되어야 사용이 가능`);
    }
    else {
        res.sendFile(path.join(__dirname,'./','front','write.html'));
    }


    
});

app.get('/header', (req, res) => {

    if (req.cookies.user == null){
        res.sendFile(path.join(__dirname,'./','front','header_logout.html'));
        console.log(`현재 로그아웃 상태`);
    }
    else if (req.cookies.user == "test"){
        res.sendFile(path.join(__dirname,'./','front','fullheader.html'));
        console.log(`현재 test 로그인 상태`);
        console.log(`session값 ${req.session.user_id}`);
    }
    else {
        res.sendFile(path.join(__dirname,'./','front','header_login.html'));
        console.log(`현재 로그인 상태`);
    }
});

///////////////
//// 회원가입
///////////////

app.post('/signin', (req, res) => {
	//json 데이터 추출
    const { user_name, user_id, user_pwd } = req.body;

    console.log(`user_name : ${user_name}, user_id : ${user_id}, user_pwd: ${user_pwd}`);

    connection.query(`INSERT INTO DB1.User (user_name, user_id, user_pwd) VALUES (?,?,?)` , [user_name, user_id, user_pwd], function (error, data) {
        if (error) throw error;
    }); 

    console.log("회원가입이 완료되었습니다.");
    res.redirect('/login');

});

///////////////
//// 로그인
///////////////

app.post('/login', (req, res) => {
    const { user_id, user_pwd } = req.body;

    console.log(`user_id : ${user_id}, user_pwd: ${user_pwd}`);

    connection.query(`SELECT user_id, user_pwd FROM DB1.User WHERE user_id = ? AND user_pwd = ?;`, [user_id, user_pwd], function (error, result, fields) {
        console.log(result);
        console.log(result.length);
        var result_string = JSON.stringify(result);

        if (error) throw error;
        else if (result.length != 0) {
            req.session.user = {
                id: req.body.id,
            };
            if(req.body.user_id == 'test' && req.body.user_pwd == '1234') {
                console.log("아이디 test, 비밀번호 1234 통과");
                console.log(`임시 로그인 되셨습니다`);
            }
            else {
                console.log(`아이디 ${user_id}, 비밀번호 ${user_pwd} 통과`);
                console.log(`정상 로그인 되셨습니다`);
            }
            res.setHeader('Set-Cookie', ['user=' + req.body.user_id]);
            res.redirect('/');
        }
        else {
            console.log("잘못된 아이디, 비밀번호");
            return res.redirect('/login');
        }

    });
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

//////////////////////
// 게시글 보기 (+라우팅)
//////////////////////


// app.get('/post/:pid', (req, res) => {
//     var page_params = req.params.pid;
//     var regex = /[^0-9]/g;
//     var page_id = page_params.replace(regex, "");
//     console.log(`${page_id} 페이지 발견`);

//     connection.query(`SELECT * FROM DB1.Content WHERE id_cont = ?;`, [page_id], function (error, result, fields) {
//         if (error) throw error;
//         var string = JSON.stringify(result);
//         var res_string = JSON.parse(string);
//         console.log(`res_string[0].id_cont 값 : ${res_string[0].id_cont}`);
        
//         if (res_string.length != 0) {
//             connection.query(`SELECT Category_id_category, Content_id_cont FROM DB1.Category_has_Content WHERE Content_id_cont = ?;`, [res_string[0].id_cont], function (error, result, fields) {
//                 if (error) throw error;
//                 var string = JSON.stringify(result);
//                 var res2_string = JSON.parse(string);

                
//                 if (req.cookies.user = null){
//                     post_log = 'post_logout';
//                 }
//                 else {
//                     post_log = 'post_login';
//                 }

//                 console.log(`${post_log}`);
//                 if (res2_string.length != 0) {
//                     res.render(`./front_ejs/${post_log}`, {title: res_string[0].cont_title , contents: res_string[0].cont_cont , category : res2_string[0].Category_id_category});
//                     console.log(`페이지 발견, 카테고리 발견`);
//                 }
//                 else {
//                     res.render(`./front_ejs/${post_log}`, {title: res_string[0].cont_title , contents: res_string[0].cont_cont, category : 'X'});
//                     console.log(`페이지 발견, 카테고리 미발견`);
//                 }
//             });
//         }
//         else {
//             console.log(`존재하지 않는 페이지입니다.`);
//         }
//     });


// });


app.post('/', (req, res) => {
    
});

/////////////
// 페이지 이동
/////////////

// var para = document.location.href.split(":");
// console.log(para);

///////////
// 글 쓰기
///////////

app.get('/testzone', (req, res) => {
    res.setHeader('Set-Cookie', ['user=' + 'HelloWorld']);

    console.log(req.header.cookie);
});

app.post('/write', (req, res) => {
    const {post_title, post_content, ctgr} = req.body;  

    console.log(`post title = ${post_title}`);
    console.log(`post_content = ${post_content}`);
    console.log(`ctgr = ${ctgr}`);

    if (post_title || post_content == ""){

        // 현재 작성중인 user의 uid 가져오기
        connection.query(`SELECT uid FROM DB1.User WHERE user_id = ?`,[req.cookies.user], function(error, result) {
            if (error) throw error;
            else {
                var string = JSON.stringify(result);
                var uid_string = JSON.parse(string);
                const uid = uid_string[0].uid;
                console.log(`현재 user = ${req.cookies.user} 의 uid는 ${uid}`);
        
                // DB Content에 현재 작성한 게시글 insert
                console.log(`INSERT INTO DB1.Content (cont_title, cont_cont, Main_id_main, User_uid) VALUES (${post_title}, ${post_content},1,${uid})`);
                connection.query(`INSERT INTO DB1.Content (cont_title, cont_cont, Main_id_main, User_uid) VALUES (?,?,?,?)` , [post_title, post_content,'1',uid], function (error, data) {
                    if (error) throw error;
                });
            }   
        });

        
        // DB Content에 카테고리 추가
        if (ctgr != ""){
            console.log("카테고리 값 감지됨, 카테고리 생성 실행");
            connection.query(`SELECT * FROM DB1.Category WHERE cate_name = ?` , [ctgr], function (error, result) {
                if (error) throw error;
                var string = JSON.stringify(result);
                var parsed_res = JSON.parse(string);   
                console.log(`최초 카테고리 검색 결과 : ${parsed_res}`);             

                if (parsed_res.length != 0){
                    console.log("기존 카테고리 발견");
                    var ctgr_id = parsed_res[0].id_category;
    
                    console.log(`기존 카테고리 : ${ctgr} , ctgr_id : ${ctgr_id} 생성 완료`);
                }
                else {
                    console.log("신규 카테고리 생성");
                    connection.query(`INSERT INTO DB1.Category (cate_name) VALUES (?)` , [ctgr], function (error, data) {
                        if (error) throw error;
                    });
                    connection.query(`SELECT * FROM DB1.Category WHERE cate_name = ?` , [ctgr], function (error, result) {
                        if (error) throw error;
        
                        var string = JSON.stringify(result);
                        var parsed_res = JSON.parse(string);

                        console.log(`카테고리 생성 후 parsed_res 결과 : ${parsed_res}`);
            
                        var ctgr_id = parsed_res[0].id_category;
                        console.log(`신규 카테고리 : ${ctgr} , ctgr_id : ${ctgr_id} 생성 완료`);
                    });
                }
            });

            // 현재 게시글 - 카테고리 연결
            // Category - Content 테이블에 Content값을 추가
            // Category - Content 테이블에 Category값을 추가
            connection.query(`SELECT id_cont FROM DB1.Content;`, function (error, result) {
                if (error) throw error;
                else {
                    var string = JSON.stringify(result);
                    var json = JSON.parse(string);
    
                    var pid = json[json.length-1].id_cont;
                    pid++;
                    

                    connection.query(`SELECT * FROM DB1.Category WHERE cate_name = ?`, [ctgr], function (error, result) {
                        var string = JSON.stringify(result);
                        var parsed_res = JSON.parse(string);
                        var ctgr_id = parsed_res[0].id_category;
                        
                        connection.query(`INSERT INTO DB1.Category_has_Content (Category_id_category, Content_id_cont) VALUES (?, ?)`, [ctgr_id, pid], function (error, data) {  //Category INSERT
                            if (error) throw error;
                        });
                        console.log(`Category-Content 테이블에 추가된 ctgr_id : ${ctgr_id}, pid : ${pid}`);
                    });
                }
                });
        }
        else {
            console.log("카테고리 값 = null");
        }
        console.log("게시글 작성이 완료되었습니다.");
        res.redirect('/');
    }
    else {
        console.log("제목, 내용을 입력하세요.");
        res.redirect('/write');
    }








});