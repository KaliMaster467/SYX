show Databases;

create Database Sybil;
use Sybil;
create table Usuarios(
	IdUsuario int(20) not null Primary Key,
    Nombre varchar(25)not null,
    SegundoNombre varchar(15),
    ApellidoPaterno varchar(15) not null,
    ApellidoMaterno varchar(15),
    Correo varchar(30) not null,
    Contraseña varchar(30) not null,
    Telefono int(15) not null,
    NombreUsuario varchar(10) not null,
    Estado varchar (25) not null
);
create table  Paquetes(idPaquete int(5) not null Primary Key auto_increment, 
						NombrePaquete varchar (20) ,
                        Camaras int (5),
                        Sensores int (5),
                        Precio int (15),
                        Descripcion varchar (80));
                        
create table PaquetaxoUsuario(idPaqueteUsuario int (5),
								idPaquete int (5), 
                                foreign key (idPaquete) references Paquetes (idPaquete),
                                idUsuario int (5),
                                foreign key (idUsuario) references Usuarios (idUsuario));

select* from Usuarios ;
select * from Paquetes;

DELIMITER //
create procedure pr_activar_usuario(_NombreUsuario varchar(25))
begin
	UPDATE Usuarios set Estado ='Activo' where NombreUsuario=_NombreUsuario; 
end
//
DELIMITER ;
DELIMITER //
create procedure pr_desactivar_usuario(_NombreUsuario varchar(25))
begin
	UPDATE Usuarios set Estado ='Fuera_De_Servicio' where NombreUsuario=_NombreUsuario; 
end
//
DELIMITER ;
/*
drop procedure pr_select_all_ID;
DELIMITER //
create procedure pr_select_all_nUs(_NombreUsuario varchar(10))
begin
	SELECT * FROM Usuarios WHERE NombreUsuario = _NombreUsuario;
end
//
DELIMITER ;
DELIMITER //
create procedure pr_select_all_ID(_IDUsuario int(20))
begin
	SELECT * FROM Usuarios WHERE IdUsuario = _IDUsuario;
end
//
DELIMITER ;*/