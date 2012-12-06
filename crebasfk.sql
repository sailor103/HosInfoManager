

create database BingFangInfoManager



use BingFangInfoManager


/*==============================================================*/
/* DBMS name:      Microsoft SQL Server 2008                    */
/* Created on:     2011/3/1 16:53:45                            */
/*==============================================================*/


if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('BingFang') and o.name = 'FK_BINGFANG_HAVEBINGC_KE')
alter table BingFang
   drop constraint FK_BINGFANG_HAVEBINGC_KE
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('BingLi') and o.name = 'FK_BINGLI_DOCOF_PEOPLE')
alter table BingLi
   drop constraint FK_BINGLI_DOCOF_PEOPLE
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('BingLi') and o.name = 'FK_BINGLI_WHICHBING_BINGFANG')
alter table BingLi
   drop constraint FK_BINGLI_WHICHBING_BINGFANG
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('BingLi') and o.name = 'FK_BINGLI_WHICHJIBI_KE')
alter table BingLi
   drop constraint FK_BINGLI_WHICHJIBI_KE
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('KE') and o.name = 'FK_KE_HAVEPEOPL_PEOPLE_Zhuren')
alter table KE
   drop constraint FK_KE_HAVEPEOPL_PEOPLE_Zhuren
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('KE') and o.name = 'FK_KE_HAVEPEOPL_PEOPLE_Hushizhang')
alter table KE
   drop constraint FK_KE_HAVEPEOPL_PEOPLE_Hushizhang
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('People') and o.name = 'FK_PEOPLE_KE_OF_KE')
alter table People
   drop constraint FK_PEOPLE_KE_OF_KE
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('BingFang')
            and   name  = 'HaveBingfang_FK'
            and   indid > 0
            and   indid < 255)
   drop index BingFang.HaveBingfang_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('BingFang')
            and   type = 'U')
   drop table BingFang
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('BingLi')
            and   name  = 'Deal_FK'
            and   indid > 0
            and   indid < 255)
   drop index BingLi.Deal_FK
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('BingLi')
            and   name  = 'HavePo_FK'
            and   indid > 0
            and   indid < 255)
   drop index BingLi.HavePo_FK
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('BingLi')
            and   name  = 'TreatPa_FK'
            and   indid > 0
            and   indid < 255)
   drop index BingLi.TreatPa_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('BingLi')
            and   type = 'U')
   drop table BingLi
go

if exists (select 1
            from  sysobjects
           where  id = object_id('KE')
            and   type = 'U')
   drop table KE
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('People')
            and   name  = 'HavePeople_FK'
            and   indid > 0
            and   indid < 255)
   drop index People.HavePeople_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('People')
            and   type = 'U')
   drop table People
go

/*==============================================================*/
/* Table: BingFang                                              */
/*==============================================================*/
create table BingFang (
   BFNo                 char(3)              not null,
   KNo                  char(5)              null,
   BFAccount            int                  null,
   constraint PK_BINGFANG primary key nonclustered (BFNo)
)
go

/*==============================================================*/
/* Index: HaveBingfang_FK                                       */
/*==============================================================*/
create index HaveBingfang_FK on BingFang (
KNo ASC
)
go

/*==============================================================*/
/* Table: BingLi                                                */
/*==============================================================*/
create table BingLi (
   BFNo                 char(3)              not null,
   BL_BCNo              char(2)              not null,
   BL_Name              char(20)             not null,
   KNo                  char(5)              null,
   PNo                  char(11)             null,
   BL_Info              char(50)             null,
   constraint PK_BINGLI primary key nonclustered (BL_BCNo, BFNo)
)
go

/*==============================================================*/
/* Index: TreatPa_FK                                            */
/*==============================================================*/
create index TreatPa_FK on BingLi (
KNo ASC
)
go

/*==============================================================*/
/* Index: HavePo_FK                                             */
/*==============================================================*/
create index HavePo_FK on BingLi (
BFNo ASC
)
go

/*==============================================================*/
/* Index: Deal_FK                                               */
/*==============================================================*/
create index Deal_FK on BingLi (
PNo ASC
)
go

/*==============================================================*/
/* Table: KE                                                    */
/*==============================================================*/
create table KE (
   KNo                  char(5)              not null,
   KName                char(20)             not null,
   KTel                 char(8)              null,
   KZhuren              char(11)             null,
   KHushizhang          char(11)             null,
   constraint PK_KE primary key nonclustered (KNo)
)
go

/*==============================================================*/
/* Table: People                                                */
/*==============================================================*/
create table People (
   PNo                  char(11)             not null,
   KNo                  char(5)              null,
   PName                char(20)             not null,
   PLel                 char(20)             null,
   constraint PK_PEOPLE primary key nonclustered (PNo)
)
go

/*==============================================================*/
/* Index: HavePeople_FK                                         */
/*==============================================================*/
create index HavePeople_FK on People (
KNo ASC
)
go

alter table BingFang
   add constraint FK_BINGFANG_HAVEBINGC_KE foreign key (KNo)
      references KE (KNo)
go

alter table BingLi
   add constraint FK_BINGLI_DOCOF_PEOPLE foreign key (PNo)
      references People (PNo)
go

alter table BingLi
   add constraint FK_BINGLI_WHICHBING_BINGFANG foreign key (BFNo)
      references BingFang (BFNo)
go

alter table BingLi
   add constraint FK_BINGLI_WHICHJIBI_KE foreign key (KNo)
      references KE (KNo)
go

alter table KE
   add constraint FK_KE_HAVEPEOPL_PEOPLE_Zhuren foreign key (KZhuren)
      references People (PNo)
go

alter table KE
   add constraint FK_KE_HAVEPEOPL_PEOPLE_Hushizhang foreign key (KHushizhang)
      references People (PNo)
go

alter table People
   add constraint FK_PEOPLE_KE_OF_KE foreign key (KNo)
      references KE (KNo)
go



--科查询（主任、护士长是谁，是否有空病床等）

--查询主任护士长是否有空床

--查询主任护士长是谁

select KE.KName 科目,first.PName 主任,second.PName 护士长 from KE,People first,People second where KE.KZhuren=first.PNo and KE.KHushizhang=second.PNo;

--查询是否有空床

select 24-COUNT(*)剩余病床
from BingLi
where BingLi.KNo='00001';--这里查询了内科剩余的病床


--医护员有关信息查询（所属科，职称，主治哪几个病人等）



--住院病人查询（住在哪个科，几病房几床，主治大夫是谁等）
select * from KE

insert into  KE (KNo,KName,KTel,KZhuren,KHushizhang)
values ('00006','肿瘤科','88425006','20081000745','20091000745');

select distinct (PName),KName,PLel from KE,People where People.KNo=KE.KNo

select BL_Name from BingLi,People where People.PNo=BingLi.PNo and People.PName='王立超'


select BL_Name,KName,BFNo,BL_BCNo,PName,BL_Info 
from BingLi,KE,People
where BingLi.KNo=KE.KNo and BingLi.PNo=People.PNo



