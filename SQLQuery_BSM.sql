
--*********�������ݿ�**************
create database BookStoreManager

--**********�������ֱ�*************


use BookStoreManager
--��������
create table BookStore
(
BSNo char(5) primary key,--�����BSNo
BSName char(30) not null, --����� ���ﲻ�������û������
BSAddress char(50),      --����ַ
BSTel char(12)           --���绰
);

use BookStoreManager
--����ͼ���
create table Book
(
BKISBN char(13) primary key,--ͼ��ISBN���룬���ʹ涨13λ
BKName char(40) not null,   --����������Ϊ��
BKAuthor char(20),          --����
BKPrise  money,             --�ۼ�
);


use BookStoreManager
--�����Żݿ���
create table BookCard
(
BCNo char(11) primary key,--�Żݿ��ţ�11λ
BCName char(20) not null, --�ֿ�������
BCCompany char(30),       --�ֿ��˹�����λ
);

use BookStoreManager
--����HorN��
create table HorN
(
BSNo char(5),   --����
BKISBN char(13),--ISBN��
HNAmount int,   --����
primary key(BSNo,BKISBN),--��������
foreign key(BSNo)references BookStore(BSNo),
foreign key(BKISBN)references BooK(BKISBN)
);

use BookStoreManager
--����ʹ�ñ�
create table UseBc
(
BSNo char(5),   --����
BCNo char(11),  --�Żݿ���
UBAmount float check (UBAmount>=0 and UBAmount<=500),
primary key(BSNo,BCNo),
foreign key(BSNo)references BookStore(BSNo),
foreign key(BCNo)references BookCard(BCNo)
);

use BookStoreManager
--�������۱�
create table Discount
(
BCNo char(11),  --�Żݿ���
BKISBN char(13),--ͼ��ISBN����
DAmount int,
primary key(BCNo,BKISBN),
foreign key(BCNo)references BookCard(BCNo),
foreign key(BKISBN)references Book(BKISBN)
);

/*
�����ô���������ݱȽϻ�����������������õ�����SQL2008�ṩ�Ľ�������Ӹ�������
��ȻΪ�����������ʹ�ã����ﻹ��ʹ����һ��Ĵ���
*/


--**********���濪ʼ��������******************

use BookStoreManager
--����Ԫ��
insert into BookStore(BSNo,BSName,BSAddress,BSTel)
values('00001','��Ԫ���','������������·','053288525272');

/*use BookStoreManager
drop table HorN;
drop table Discount;

drop table Book;*/