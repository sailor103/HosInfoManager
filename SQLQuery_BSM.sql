
--*********建立数据库**************
create database BookStoreManager

--**********建立各种表*************


use BookStoreManager
--建立书店表
create table BookStore
(
BSNo char(5) primary key,--书店编号BSNo
BSName char(30) not null, --书店名 这里不允许书店没有名字
BSAddress char(50),      --书店地址
BSTel char(12)           --书店电话
);

use BookStoreManager
--建立图书表
create table Book
(
BKISBN char(13) primary key,--图书ISBN号码，国际规定13位
BKName char(40) not null,   --书名，不能为空
BKAuthor char(20),          --作者
BKPrise  money,             --售价
);


use BookStoreManager
--建立优惠卡表
create table BookCard
(
BCNo char(11) primary key,--优惠卡号，11位
BCName char(20) not null, --持卡人姓名
BCCompany char(30),       --持卡人工作单位
);

use BookStoreManager
--建立HorN表
create table HorN
(
BSNo char(5),   --书店号
BKISBN char(13),--ISBN号
HNAmount int,   --数量
primary key(BSNo,BKISBN),--两个主码
foreign key(BSNo)references BookStore(BSNo),
foreign key(BKISBN)references BooK(BKISBN)
);

use BookStoreManager
--建立使用表
create table UseBc
(
BSNo char(5),   --书店号
BCNo char(11),  --优惠卡号
UBAmount float check (UBAmount>=0 and UBAmount<=500),
primary key(BSNo,BCNo),
foreign key(BSNo)references BookStore(BSNo),
foreign key(BCNo)references BookCard(BCNo)
);

use BookStoreManager
--建立打折表
create table Discount
(
BCNo char(11),  --优惠卡号
BKISBN char(13),--图书ISBN号码
DAmount int,
primary key(BCNo,BKISBN),
foreign key(BCNo)references BookCard(BCNo),
foreign key(BKISBN)references Book(BKISBN)
);

/*
由于用代码更新数据比较缓慢，所以在这里采用的是在SQL2008提供的界面下添加各种数据
当然为了熟练代码的使用，这里还是使用了一点的代码
*/


--**********下面开始更新数据******************

use BookStoreManager
--插入元组
insert into BookStore(BSNo,BSName,BSAddress,BSTel)
values('00001','三元书店','莱西市威海中路','053288525272');

/*use BookStoreManager
drop table HorN;
drop table Discount;

drop table Book;*/