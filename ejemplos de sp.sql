--a)
SELECT MAX(OrderDate) AS UltimaFechaOrden
FROM Sales.SalesOrderHeader;
--b)
SELECT *
FROM Sales.SalesOrderHeader
WHERE OrderDate = (SELECT MAX(OrderDate) FROM Sales.SalesOrderHeader);
---c)
SELECT o.SalesOrderID, o.CustomerID, o.SalesPersonID, o.OrderDate
FROM Sales.SalesOrderHeader o
JOIN Sales.Customer c ON o.CustomerID = c.CustomerID
JOIN Person.Person p ON c.PersonID = p.BusinessEntityID
WHERE p.LastName LIKE 'L%';
--d)
SELECT o.SalesOrderID, o.CustomerID, o.SalesPersonID, o.OrderDate
FROM Sales.SalesOrderHeader o
JOIN Sales.Customer c ON o.CustomerID = c.CustomerID
JOIN Person.Person p ON c.PersonID = p.BusinessEntityID
WHERE p.LastName LIKE 'M%';

---A) Trono bien feo
--B) Subquery returned more than 1 value. This is not permitted when the
--subquery follows =, !=, <, <= , >, >= or when the subquery is used as an
--expression.
--C) Porque no permite múltiples valores porque se puso el =

--parte 2 

WITH OrderRows AS (
    SELECT 
        SalesOrderID, 
        OrderDate, 
        TotalDue,
        ROW_NUMBER() OVER (ORDER BY OrderDate) AS fila_no
    FROM 
        Sales.SalesOrderHeader
)
SELECT * FROM OrderRows;

--PARTE 3 
WITH OrderRows AS (
    SELECT 
        SalesOrderID, 
        OrderDate, 
        TotalDue,
        ROW_NUMBER() OVER (ORDER BY OrderDate) AS fila_no
    FROM 
        Sales.SalesOrderHeader
)
SELECT 
    a.SalesOrderID,
    a.OrderDate,
    a.TotalDue,
    a.fila_no,
    a.TotalDue - b.TotalDue AS Diferencia
FROM 
    OrderRows a
LEFT JOIN 
    OrderRows b
ON 
    a.fila_no = b.fila_no + 1
ORDER BY 
    a.fila_no;




	