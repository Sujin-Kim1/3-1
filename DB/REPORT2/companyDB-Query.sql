-- Queries for companyDB-SchemaData
-- Version 1.0

USE company;

-- Q1 : 이름(Fname,Minit,Lname)이 ‘JohnB.Smith’인사원의 생년월일과 주소를 검색하시오.
SELECT Bdate 생년월일, Address 주소
FROM k_employee
WHERE CONCAT(Fname,' ', Minit,'. ', Lname) = 'John B. Smith';

-- Q2:부서번호가 5인 부서에 근무하는 모든 사원의 모든 컬럼을 검색하시오.
SELECT *
FROM k_employee
WHERE Dno = 5;

-- Q3:‘Research’ 부서에 근무하는 모든 사원의 이름, 그리고 주소를 검색하시오.
SELECT Fname, Minit, Lname 사원이름, E.Address 주소
FROM k_employee E INNER JOIN k_department D ON E.Dno = D.Dnumber
WHERE D.Dname = 'Research';

-- Q4:‘Stafford’에 위치한 모든 프로젝트에 대해서, 프로젝트번호, 담당부서 번호, 부서관리자의 이름을 검색하시오.
SELECT P.Pnumber '프로젝트 번호', D.Dnumber '담당부서 번호', Fname, Minit, Lname '부서관리자의 이름'
FROM k_project P INNER JOIN k_department D ON P.Dnum = D.Dnumber
	 INNER JOIN k_employee E ON D.Mgr_ssn = E.Ssn
WHERE P.Plocation = 'Stafford';

-- Q5:각 사원에 대해 사원의 이름과 성별, 그리고 직속 상사의 이름과 성별을 검색하시오. 
-- 단, 직속 상사가 없는 직원도 검색하시오. 
-- 출력 컬럼은 사원의 이름과 성별, 그리고 직속 상사의 이름과 성별 순으로 하며, 테이블 데이터는 사원 이름 중 Fname의 오름차순으로 나타내시오.
SELECT E.Fname, E.Minit, E.Lname, E.Sex '사원 성별',
	   S.Fname, S.Minit, S.Lname, S.Sex '상사 성별'
FROM k_employee E LEFT JOIN k_employee S ON E.Super_ssn = S.Ssn
ORDER BY E.Fname, E.Sex, S.Fname, S.Sex;

-- Q6:사원 ‘FranklinWong’ 이 직접 관리하는 사원의 이름을 검색하시오. 테이블 데이터는 사원 이름 중 Fname의 오름차순으로 나타내시오.
SELECT E.Fname, E.Minit, E.Lname '사원 이름'
FROM k_employee E INNER JOIN k_employee S ON E.Super_ssn = S.Ssn
WHERE CONCAT(S.Fname, S.Lname) = 'FranklinWong'
ORDER BY E.Fname;

-- Q7:사원의 Ssn과 부서의 Dname에 대한 모든 조합을 생성하시오. 
-- 출력 컬럼은 Ssn, Dname 순으로 나열하며, 테이블 데이터는 Ssn과 Dname의 오름차순으로 출력하시오.
SELECT Ssn, Dname
FROM k_employee CROSS JOIN k_department
ORDER BY 1, 2;

-- Q8:성이 ‘Wong’ 인사원이 일하는 프로젝트, 혹은 성이 ‘Wong’인 사원이 관리하는 부서에서 진행하는 프로젝트의 번호를 검색하시오. 
-- 테이블 데이터는 프로젝트 번호의 오름차순으로 나타내시오.
SELECT Pno 
FROM k_employee E JOIN k_works_on W ON E.Ssn = W.Essn
WHERE Lname = 'Wong'
UNION
SELECT P.Pnumber
FROM k_employee E JOIN k_department D ON E.Ssn = D.Mgr_ssn
	 JOIN k_project P ON D.Dnumber = P.Dnum
WHERE Lname = 'Wong'
ORDER BY Pno;
     
-- Q9:주소에 ‘Houston,TX’이 들어있는 모든 사원의 이름을 검색하시오. 
-- 출력 컬럼은 사원의 이름, 주소 순으로 하며, 테이블 데이터는 이름 중 Fname의 오름차순으로 나타내시오.
SELECT Fname, Minit, Lname, Address
FROM k_employee
WHERE Address LIKE '%Houston, TX%'
ORDER BY Fname, Address;

-- Q10:‘ProductX’ 프로젝트에 참여하는 모든 사원의 이름, 그리고 그들의 급여를 10% 올린 경우의 급여를 구하시오.
SELECT Fname, Minit, Lname '사원 이름', Salary * 1.1 
FROM k_project P JOIN k_works_on W ON P.Pnumber = W.Pno
	 JOIN k_employee E ON W.Essn = E.Ssn
WHERE Pname = 'ProductX';

-- Q11:모든 부서 이름, 부서에 소속한 사원의 이름, 그리고 각 사원이 진행하는 프로젝트 이름의 리스트를 검색하시오. 
-- 테이블 데이타는 부서 이름의 내림차순, 그리고 각 부서 내에서 사원 이름의 오름차순, 프로젝트 이름의 오름차순으로 나타내시오.
SELECT Dname, Fname, Minit, Lname, Pname
FROM k_department D JOIN k_employee E ON D.Dnumber = E.Dno
     JOIN k_works_on W ON E.Ssn = W.Essn
     JOIN k_project P ON W.Pno = P.Pnumber
ORDER BY 1 DESC, 2, 3, 4, 5;

-- Q12:5번 부서에 근무하는 사원 중에서, ProjectX 프로젝트에 주당 10시간 이상 일하는 사원의 이름과 주당 근무시간을 검색하시오.
SELECT Fname, Minit, Lname, Hours
FROM k_employee JOIN k_works_on ON Ssn = Essn
     JOIN k_project ON Pno = Pnumber
WHERE Dno = 5 AND Hours >= 10 AND Pname = 'ProductX';

-- Q13:배우자가 있는 사원수를 검색하시오.
SELECT COUNT(Essn)
FROM k_dependent
WHERE Relationship IN ('Spouse');

-- Q14:부양가족이 있는 사원에 대해, 부양가족 수를 구하시오. 출력으로 사원의 이름과 부양가족 수(컬럼 이름은 NumOfDependents로 할 것)를 나열하시오.
SELECT Fname, Minit, Lname, COUNT(Relationship) NumOfDependents
FROM k_employee E JOIN k_dependent D ON E.Ssn = D.Essn
GROUP BY Ssn
ORDER BY Fname, Minit, Lname, NumOfDependents;

-- Q15:모든 사원에 대해, 부양가족의 이름과 관계를구하시오. 이 때 부양가족이 없는 사원도 포함합니다. 
-- 출력 컬럼은 사원의 이름, 부양가족과의 관계, 부양가족의 이름 순으로 나열하시오. 
-- 테이블 데이타는 사원 이름 중 Fname, Minit, Lname의 오름차순으로 나타내시오.
SELECT Fname, Minit, Lname, 
	   Relationship, Dependent_name
FROM k_employee E LEFT JOIN k_dependent D ON E.Ssn = D.Essn
ORDER BY 1, 2, 3;

-- Q16:모든 사원에 대해, 부양가족 수를 구하고, 이때 부양가족이 없는 사원은 부양가족수를 0으로 표시하시오. 
-- 출력 컬럼은 사원의 이름과 부양가족 수(NumOfDependents) 순으로 나열하시오. 
-- 테이블 데이터는 부양가족수의 내림차순, 이름 중 Fname의 오름차순으로 나타내시오.
SELECT Fname, Minit, Lname, COALESCE(COUNT(Relationship), 0) NumOfDependents
FROM k_employee E LEFT JOIN k_dependent D ON E.Ssn = D.Essn
GROUP BY Ssn
ORDER BY NumOfDependents DESC, Fname;

-- Q17:부양가족이 없는 사원의 이름을 구하시오. 테이블데이터는 이름 중 Fname의 오름차순으로 나타내시오.
SELECT Fname, Minit, Lname
FROM k_employee E LEFT JOIN k_dependent D ON E.Ssn = D.Essn
GROUP BY Ssn HAVING COUNT(Relationship) = 0
ORDER BY Fname;

-- Q18:자녀가 있는 사원에 대해, 부양가족 수를 구하시오.
-- 출력 컬럼으로 사원의 이름과 부양가족수(NumOfDependents) 순으로 나열하시오. 
-- 테이블 데이터는 이름 중 Fname의 오름차순으로 나타내시오.
SELECT Fname, Minit, Lname, COUNT(Relationship) NumOfDependents
FROM k_dependent D JOIN k_employee E 
     ON D.Essn = E.Ssn 
WHERE Essn IN (SELECT Essn
               FROM k_dependent
               WHERE Relationship IN ('Son', 'Daughter'))
GROUP BY Essn 
ORDER BY Fname;

-- Q19:각 부서에 대해, 부서의 위치와 같은 곳에서 진행되는 프로젝트를 검색하시오. 
-- 출력 컬럼은 부서 명칭, 부서 위치, 프로젝트 명칭, 프로젝트 위치 순으로 나열하시오. 
-- 테이블 데이터는 부서 명칭과 프로젝트 명칭은 오름차순으로 나타내시오.
SELECT Dname, Dlocation, Pname, Plocation
FROM k_department D JOIN k_dept_locations DL ON D.Dnumber = DL.Dnumber
     JOIN k_project P ON DL.Dnumber = P.Dnum AND DL.Dlocation = P.Plocation 
ORDER BY Dname, Pname;