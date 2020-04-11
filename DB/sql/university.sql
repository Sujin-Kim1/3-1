SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;					/* Default : 1 (ON) */	
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;		/* Default : 1 (ON) */
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';

DROP SCHEMA IF EXISTS university;

CREATE SCHEMA university;
use university;

DROP TABLE IF EXISTS STUDENT;
DROP TABLE IF EXISTS COURSE;
DROP TABLE IF EXISTS ENROLL;

CREATE TABLE STUDENT (
	SNO int NOT NULL,
    SNAME VARCHAR(40),
	SYEAR int,
    DEPT VARCHAR(40),
    CONSTRAINT PK_STUDENT PRIMARY KEY (SNO)
);

CREATE TABLE COURSE (
	CNO VARCHAR(40) NOT NULL,
    CNAME VARCHAR(40),
    CREDIT int,
    DEPT VARCHAR(40),
    PRNAME VARCHAR(40),
    CONSTRAINT PK_COURSE PRIMARY KEY(CNO)
);

CREATE TABLE ENROLL(
	SNO int NOT NULL,
    CNO VARCHAR(40) NOT NULL,
    GRADE CHAR(1),
    MIDTERM int,
    FINAL int,
	-- CONSTRAINT PK_ENROLL PRIMARY KEY(SNO),
--     CONSTRAINT PK_ENROLL PRIMARY KEY(CNO),
    CONSTRAINT 	FK_STUDENT_ENROLL  FOREIGN KEY (SNO) REFERENCES STUDENT(SNO)
       										ON DELETE RESTRICT
                                            ON UPDATE CASCADE,

	CONSTRAINT FK_COURSE_ENROLL FOREIGN KEY (CNO) REFERENCES COURSE(CNO)
											ON DELETE RESTRICT
                                            ON UPDATE CASCADE
);

INSERT INTO student VALUES
	(100, '나연묵', 4, '컴퓨터'),
    (200, '이찬영', 3, '전기'),
    (300, '정기태', 1, '컴퓨터'),
    (400, '송병호', 4, '컴퓨터'),
    (500, '박종화', 2, '산공');
    
INSERT INTO course VALUES
	('C123', '프로그래밍', 3, '컴퓨터', '김성기'),
    ('C312', '자료구조', 3, '컴퓨터', '황수찬'),
    ('C324', '화일 처리', 3, '컴퓨터', '이규철'),
    ('C413', '데이타 베이스', 3, '컴퓨터', '이석호'),
    ('C412', '반도체', 3, '전자', '홍봉희');
    
INSERT INTO enroll VALUES
	(100, 'C413', 'A', 90, 95),
    (100, 'E412', 'A', 95, 95),
    (200, 'C123', 'B', 85, 80),
    (300, 'C312', 'A', 90, 95),
    (300, 'C324', 'C', 75, 75),
    (300, 'C413', 'A', 95, 90),
    (400, 'C312', 'A', 90, 95),
    (400, 'C324', 'A', 95, 90),
    (400, 'C413', 'B', 80, 85),
    (400, 'E412', 'C', 65, 75),
    (500, 'C312', 'B', 85, 80);
    