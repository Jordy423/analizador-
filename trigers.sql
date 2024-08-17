select * from empleados
select * from empleados_Copia
select * from Empleados_Cancelados
--trigger
create trigger trg_InsertarEmpleados on empleados
for insert
as
declare @id int
declare @nombre varchar(30)
declare @apellido varchar(30)
declare @estado varchar(20)
declare @fecha_contrato date
declare @accion_trigger varchar(30)
select @id = i.id from inserted i
select @nombre = i.nombre from inserted i
select @apellido = i.apellido from inserted i
select @estado = i.estado from inserted i
select @fecha_contrato = i.fecha_contrato from inserted i
select @accion_trigger = i.accion_trigger from inserted i
Insert into empleados_copia
(nombre,apellido,estado,estado,fecha_contrato,accion_trigger)
values (@nombre,@apellido,@estado,@fecha_contrato,@accion_trigger)
Go
Alter trigger trg_insertarEmpleados on empleados
for insert
as
set nocount on
declare @id int
declare @nombre varchar(30)
declare @apellido varchar(30)
declare @estado varchar(20)
declare @fecha_contrato date
declare @accion_trigger varchar(30)
select @id = i.id from inserted i
select @nombre = i.nombre from inserted i
select @apellido = i.apellido from inserted i
select @estado = i.estado from inserted i
select @fecha_contrato = i.fecha_contrato from inserted i
select @accion_trigger = i.accion_trigger from inserted i
insert into empleados_Copia (nombre, apellido, estado, fecha_contrato,
accion_trigger) values (@nombre, @apellido, @estado, @fecha_contrato,
@accion_trigger)
delete from empleados where id= @id
Go
set nocount on
insert into empleados (nombre,apellido,estado,fecha_contrato,accion_trigger)
values ( 'Jose', 'Chuga', 'ACTIVO', GETDATE(), 'Duplicar')
create trigger trg_EmpleadosCancelados on empleados
after delete
as
declare @id int
declare @nombre varchar(30)
declare @apellido varchar(30)
declare @estado varchar(20)
declare @fecha_contrato date
declare @accion_trigger varchar(30)
select @nombre = D.nombre from deleted d
select @apellido = d.apellido from deleted d
select @estado = 'CANCELADO'
select @fecha_Cancelacion = GETDATE()
select @accion_trigger = 'Trigger de Delete'
insert into Empleados_Cancelados (
nombre,apellido,estado,fecha_cacenlacion,accion_trigger)
values (@nombre,@apellido,@estado,@fecha_contrato,@accion_trigger)
Go
--trigger borrar
create trigger trg_empleadosCancelados on empleados
after delete
as
declare @id int
declare @nombre varchar(30)
declare @apellido varchar(30)
declare @estado varchar(20)
declare @fecha_Cancelado date
declare @accion_trigger varchar(30)
select @nombre = d.nombre from deleted d
select @apellido = d.apellido from deleted d
select @estado = 'CANCELADO'
select @fecha_Cancelado = GETDATE()
select @accion_trigger = 'Trigger de Delete'
insert into Empleados_Cancelados(nombre, apellido, estado, fecha_cacenlacion,
accion_trigger)
values (@nombre, @apellido, @estado, @fecha_Cancelado, @accion_trigger)
Go
delete from empleados where id= 3
-- Trigger Actualizar
CREATE TRIGGER trg_EmpleadosActualizados
ON empleados
AFTER UPDATE
AS
BEGIN
DECLARE @id INT,
@nombre VARCHAR(30),
@apellido VARCHAR(30),
@estado VARCHAR(20),
@fecha_contrato DATE,
@accion_trigger VARCHAR(30)
SELECT @nombre = i.nombre,
@apellido = i.apellido,
@estado = 'ACTUALIZADO',
@fecha_contrato = GETDATE(),
@accion_trigger = 'Trigger de Actualización'
FROM inserted i;
INSERT INTO Empleados_Actualizados (nombre, apellido, estado,
fecha_actualizacion, accion_trigger)
VALUES (@nombre, @apellido, @estado, @fecha_contrato, @accion_trigger);
END;
GO